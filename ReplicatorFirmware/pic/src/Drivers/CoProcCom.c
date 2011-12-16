/*
 * CoProcCom.c
 *
 *  Created on: Nov 21, 2009
 *      Author: hephaestus
 */
#include "UserApp.h"

#define MAX_RETRY 5
#define DELAY_TIMEOUT 150
BOOL valadateRPC(int response,int sent);

BYTE sendPacket(BowlerPacket * Packet);
BYTE GetCoProcSingleByte(void);

DWORD CalcBaud(DWORD Baud);
BOOL clearToSend(void);

extern DATA_STRUCT DATA;
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));

static BYTE privateRX[BOWLER_PacketSize*10];
static BYTE_FIFO_STORAGE store;
static BOOL lastWasError = FALSE;
static BOOL init=FALSE;
static BOOL processing=FALSE;
//static BOOL addJunk = FALSE;



static BowlerPacket downstream;
void dealWithAsyncPacket(BowlerPacket * Packet);
void uartErrorCheck();


BOOL getPacket(BowlerPacket * packet){
#if defined(USE_DMA)
	updateUartRx();
#endif
	disableDebug();
	BOOL b = GetBowlerPacket(packet,& store);
	enableDebug();
//	if(b){
//		println("ASYN rx<<\n");printPacket(packet);
//	}
	return b;
}

void addCoProcByte(BYTE b){
	//print("[");p_ul(b);print("]");
	BYTE err;
	FifoAddByte(&store,b,&err);
}



void PushCoProcAsync(void){
	BowlerPacket * Packet=&downstream;
	FLAG_ASYNC=FLAG_BLOCK;
	while (getPacket(Packet)==TRUE){
		buttonCheck(6);
		if(Packet->use.head.MessageID!=0){
			dealWithAsyncPacket(Packet);
		}else{
			enableDebug();
			println("###########Stray sync packet..");
			printPacket(Packet);
		}
	}
	FLAG_ASYNC=FLAG_OK;
}

BOOL isProcessing(){
	return processing;
}

void initCoProcUART(){
//	OpenUART2(UART_EN|UART_NO_PAR_8BIT|UART_1STOPBIT|UART_DIS_BCLK_CTS_RTS,UART_TX_ENABLE|UART_RX_ENABLE,CalcBaud(BAUD));
//	ConfigIntUART2(UART_INT_PR7 | UART_RX_INT_EN);
#if !defined(USE_DMA)
	//Disable first to clear
	INTEnable(INT_SOURCE_UART(UART2)		, INT_DISABLED);
	INTEnable(INT_SOURCE_UART_TX(UART2)		, INT_DISABLED);
	INTEnable(INT_SOURCE_UART_ERROR(UART2)	, INT_DISABLED);
	INTEnable(INT_SOURCE_UART_RX(UART2)		, INT_DISABLED);

	INTClearFlag(INT_SOURCE_UART_ERROR(UART2));
	INTClearFlag(INT_SOURCE_UART_TX(UART2));
	INTClearFlag(INT_SOURCE_UART_RX(UART2));
	INTClearFlag(INT_SOURCE_UART(UART2));

	uartErrorCheck();
	CloseUART2();


	//Start configuration
	UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY);
	UARTSetFifoMode(UART2, UART_INTERRUPT_ON_RX_NOT_EMPTY);
	UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_EVEN | UART_STOP_BITS_1);
	UARTSetDataRate(UART2, GetPeripheralClock(), INTERNAL_BAUD );
	UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

//	// Configure UART2 RX Interrupt
	INTEnable(INT_SOURCE_UART_RX(UART2)		, INT_ENABLED);
	INTEnable(INT_SOURCE_UART_ERROR(UART2)	, INT_ENABLED);

	INTSetVectorPriority(INT_VECTOR_UART(UART2), INT_PRIORITY_LEVEL_7);
	INTSetVectorSubPriority(INT_VECTOR_UART(UART2), INT_SUB_PRIORITY_LEVEL_0);

#endif

}

void uartErrorCheck(){
	if(UART2GetErrors() & _U2STA_FERR_MASK){
		 println("\n\n\nFraming error");
	}
	if(UART2GetErrors() & _U2STA_OERR_MASK){
		 println("\n\n\n\nOverflow error");
	}
	if(UART2GetErrors() & _U2STA_PERR_MASK){
		 println("\n\n\n\nPARITY error");
	}
	if(UART2GetErrors() )
		UART2ClearAllErrors();
}

void initCoProcCom(){
	//println("Initializing coproc upstream fifo");
	init = TRUE;
	StartCritical();
	InitByteFifo(&store,privateRX,sizeof(privateRX));
	initCoProcUART();
	EndCritical();
	Init_FLAG_BUSY_ASYNC();
	FLAG_ASYNC=FLAG_OK;
}


void SendPacketToCoProc(BowlerPacket * Packet){
	initCoProcUART();
	processing=TRUE;
	if(init == FALSE){
		println("Co-proc initializing..");
		initCoProcCom();
	}

	//
	BYTE i=0;
	BYTE ret;
	int rpc = Packet->use.head.RPC;
	do{
		ret=sendPacket(Packet);
		i++;
		buttonCheck(5);
		if(ret!=0){
			initCoProcCom();
		}
	}while ( (i!=MAX_RETRY) && (ret !=0 ) && valadateRPC(Packet->use.head.RPC,rpc));


	if (i==MAX_RETRY){
		enableDebug();
		printfDEBUG("############Five times failed, co-proc reset: ");printPacket(Packet);
		SetColor(1,0,0);
		initCoProcCom();
		PowerCycleAVR();
		DelayMs(200);
		ret = sendPacket(Packet);
		if(ret == 0){
			printfDEBUG("##SUCCESS! OK after AVR reset");
			return;
		}
		printfDEBUG("##Failed sending to co-proc after reset also!!:");
		printfDEBUG_UL(ret);
		ERR(Packet,0x55,ret);
		lastWasError = TRUE;

	}

	Packet->use.head.ResponseFlag = 1;
	processing=FALSE;
	FLAG_ASYNC=1;
}

BYTE sendPacket(BowlerPacket * Packet){
	//println("Sending to co processor");
	BYTE i;
	//int serIndex;
	float packStartTime=getMs();
	for(i=0;i<6;i++){
		Packet->use.head.MAC.v[i]=0;//Set the mac address to broadcast
	}
	Packet->use.head.ProtocolRevision=BOWLER_VERSION;
	SetCRC(Packet);
	//println(">>TX CoProc\n");printPacket(Packet);
	int packetSize = BowlerHeaderSize + Packet->use.head.DataLegnth;

	PushCoProcAsync();//clear out any packets before begining
	packStartTime=getMs();
	FLAG_ASYNC=FLAG_BLOCK;
	if (SendPacketUARTCoProc(Packet->stream,packetSize)){

		RunEveryData wait={getMs(),DELAY_TIMEOUT};
		//int dots=0;
		while (RunEvery(&wait)<=0){
			if(getPacket(&downstream)){
				if(downstream.use.head.MessageID!=0){
					dealWithAsyncPacket(&downstream);
					//wait.MsTime += 2;
				}else{
					if(!valadateRPC(downstream.use.head.RPC,Packet->use.head.RPC) ){
						enableDebug();
						println("@@#@#@@Valadation failed, junk TX>>");printPacket(Packet);print("\nRX<<\n");printPacket(&downstream);
						SendPacketUARTCoProc(Packet->stream,packetSize);
						SetColor(1,0,0);
						//wait.MsTime += 2;
					}else{
						FLAG_ASYNC=FLAG_OK;
						copyPacket(&downstream,Packet);
						//println("<<RX CoProc\n");printPacket(Packet);
						return 0;//Got a synchronus packet
					}
				}
			}
//			print("\nCurrent time=");p_fl(getMs()/1000);
//			print("\tCurrent ticks=");p_ul(TickGet());
//			print("\tCurrent Lower ticks=");p_ul(TickGetLower());
//			print("\tCurrent Upper ticks=");p_ul(TickGetUpper());
			buttonCheck(4);
		}
		enableDebug();
		initCoProcUART();
		printfDEBUG("############Response Timed Out, took: ");printfDEBUG_FL(getMs()-packStartTime);
		printfDEBUG_NNL(" ms to send:\n");printBowlerPacketDEBUG(Packet);
		printFiFoState(&store,downstream.stream);
		PushCoProcAsync();//clear out any packets
		FLAG_ASYNC=FLAG_OK;
		return 2;
	}else{
		enableDebug();
		printfDEBUG("@@@@@@@@@@@@Transmit Timed Out, took: ");printfDEBUG_FL(getMs()-packStartTime);printfDEBUG_NNL(" ms");
		FLAG_ASYNC=FLAG_OK;
		return 1;
	}
}

BOOL valadateRPC(int response,int sent){
	switch(sent){
	case GACM:
		switch(response){
		case GACM:
			return TRUE;
		default:
			return FALSE;
		}
	case GCHM:
		switch(response){
		case GCHM:
			return TRUE;
		default:
			return FALSE;
		}
	case GCHV:
		switch(response){
		case GCHV:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case EEPD:
		switch(response){
		case EEPD:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case _REV:
		switch(response){
		case _REV:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case SAVE:
		switch(response){
		case SAVE:
			return TRUE;
		default:
			return FALSE;
		}
	case SCHM:
		switch(response){
		case SCHM:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case SACM:
		switch(response){
		case SACM:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case SCHV:
		switch(response){
		case _RDY:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case SACV:
		switch(response){
		case _RDY:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case _PWR:
		switch(response){
		case _PWR:
			return TRUE;
		default:
			return FALSE;
		}
	case CCHN:
		switch(response){
		case _RDY:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case _MAC:
		switch(response){
		case _RDY:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	default:
		println("Method unknown");
		return TRUE;
	}
}


BOOL SendPacketUARTCoProc(BYTE * packet,WORD size){
	WORD i;
	RunEveryData wait={getMs(),DELAY_TIMEOUT*2};
	//println("Sending to co proc: ");p_ul(size);print(" Bytes");
	for (i=0;i<size;i++){
		do{
			//print("_");
			if(RunEvery(&wait) > 0){
				//print("X");
				return FALSE;
			}
			buttonCheck(3);
		}while ( clearToSend() == FALSE);
		//print("!");
		Write32UART2(packet[i]);
	}
	//println("Sending to co proc Done ");
	return TRUE;
}

BOOL clearToSend(void){
	if (FLAG_BUSY!=0)
		return FALSE;
	return TRUE;
}
#define SHORTISR
void newByte(){
#if !defined(SHORTISR)
	int timeout =0;
	while(DataRdyUART2()){

		addCoProcByte(UARTGetDataByte(UART2));

		//buttonCheck(17);
		timeout++;
		if(timeout>8){// size of the built in FIFo
			return;
		}
	}
#else
	if(DataRdyUART2()){
		addCoProcByte(UARTGetDataByte(UART2));
	}
#endif
}
#if !defined(USE_DMA)
void __ISR(_UART_2_VECTOR, ipl7) My_U2_ISR(void){
	StartCritical();
	//uartErrorCheck();
	if (INTGetFlag(INT_SOURCE_UART_RX(UART2))){
		newByte();
		INTClearFlag(INT_SOURCE_UART_RX(UART2));
	}
	else if(INTGetFlag(INT_SOURCE_UART_ERROR(UART2))){
		newByte();
		UART2ClearAllErrors();
		INTClearFlag(INT_SOURCE_UART_ERROR(UART2));
	}else{
		if ( INTGetFlag(INT_SOURCE_UART_TX(UART2)) ) {
			INTClearFlag(INT_SOURCE_UART_TX(UART2));
			//println("&@&@&&@&@&@ wtf tx");
		}
		if(INTGetFlag(INT_SOURCE_UART(UART2))){
			INTClearFlag(INT_SOURCE_UART(UART2));
			//println("&@&@&&@&@&@ generic uart");
		}
	}
	//mU2ClearAllIntFlags();
	EndCritical();
}
#endif

