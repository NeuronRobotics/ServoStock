/*
 * SPIClient.c
 *
 *  Created on: Dec 9, 2010
 *      Author: hephaestus
 */
#include "EthernetController.h"
#include "boards.h" // Kevin, i added IO mappings in this header file. -AC

// see boards.h for updated mappings
//#define configure_CS_pins() {(_TRISE7)=OUTPUT; (_TRISE6)=OUTPUT; (_TRISE5)=OUTPUT; (_TRISE4)=OUTPUT; (_TRISE3)=OUTPUT;}



static BOOL init=FALSE;
static BowlerPacket packetTemp;
static BOOL boardOK[]={1,1,1,1,1};
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));
#define JUNK_DATA 0xAA

void BowlerSPIInit(){
	ConfigureCardIO();
	CardCSSelectNone();
	OpenSPI1(SPI_MODE8_ON|ENABLE_SDO_PIN|SLAVE_ENABLE_OFF|SPI_CKE_ON|MASTER_ENABLE_ON|SEC_PRESCAL_8_1|PRI_PRESCAL_64_1, SPI_ENABLE);
	if(init==FALSE){
		init=TRUE;
		return;
	}
}
BYTE SPITransceve(BYTE b){
    SpiChnPutC(1, b);		// send data on the master channel, SPI1
    return SpiChnGetC(1);	// get the received data
}
BYTE get(BYTE b){
	BYTE back = SPITransceve(b);
        //Delay10us(60);
	return back;
}
void setSS(BYTE chan,BYTE state){
	switch(chan){
	case 0:
		BoardA_CS=state;
		break;
	case 1:
		BoardB_CS=state;
		break;
	case 2:
		BoardC_CS=state;
		break;
	case 3:
		BoardD_CS=state;
		break;
	case 4:
		BoardE_CS=state;
		break;
        case 5:
		BoardF_CS=state;
		break ;
        case 6:
		BoardG_CS=state;
		break ;
        case 7:
		BoardH_CS=state;
		break;
	}
}
BOOL BowlerSPITranceiveLocal(BowlerPacket * Packet, BOOL force,int board){
	int i=0;
	// select the board
	//enableDebug();
	println_I("Selecting ");p_sl_I(board);
	setSS(board,ASSERTED);

	Delay1us(10);
	SetCRC(Packet);
	// send the packet
	int end = 11+Packet->use.head.DataLegnth;
	for(i=0;i<end;i++){
		Packet->stream[i]=get(Packet->stream[i]);
		//DelayMs(2);
	}
	// wait until we stop getting FF
	unsigned int num=0;
        BYTE b;
        do{
            b = get(JUNK_DATA);
            num++;
            if(num==500){
                    ERR(Packet,99,board);
                    setSS(board,NOT_ASSERTED);
                    boardOK[board]=FALSE;
                    //enableDebug();
                    println_I("Failed to access board: ");p_sl_I(board);
                    return FALSE;
            }
            DelayMs(5);
	}while(b != BOWLER_VERSION );

	Packet->stream[0]=b;
	for(i=1;i<11;i++){
		Packet->stream[i]= SPITransceve(JUNK_DATA);
	}
	for(i=11;i<(11+Packet->use.head.DataLegnth);i++){
		Packet->stream[i]= SPITransceve(JUNK_DATA);
	}
	setSS(board,NOT_ASSERTED);
}
/**
 * Send one synchronus packet over the SPI bus.
 */
BOOL BowlerSPITranceive(BowlerPacket * Packet, BOOL force){
	BowlerSPIInit();
	BYTE board = (BYTE)((Packet->use.data[0]));
	if(board>=NUM_PID_GROUPS)
		return;
	if(force)
		boardOK[board] = TRUE;

	//Adjust for 0 index of local board
	Packet->use.data[0] = 0;

	BowlerSPITranceiveLocal(Packet, force, board);

	Packet->use.data[0] = board;
	println_I("SPI RX<<\n");printPacket(Packet,INFO_PRINT);
	return TRUE;
}
void LoadCorePacket(BowlerPacket * Packet){
	//SetColor(0,1,0);
	BYTE i;
	Packet->use.head.ProtocolRevision=BOWLER_VERSION;
	for (i=0;i<6;i++){
		Packet->use.head.MAC.v[i]=MyMAC.v[i];
	}
	Packet->use.head.MessageID=1;
	Packet->use.head.ResponseFlag=1;
	Packet->use.head.Method=BOWLER_STATUS;
	Packet->use.head.RPC=GetRPCValue("****");
	Packet->use.head.DataLegnth=4;
}
void SetPIDCurrent(BYTE chan,INT32 value, INT32 ms){
	if(boardOK[chan]==FALSE){
		return;
	}
	INT32_UNION v;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_POST;
	packetTemp.use.head.RPC=GetRPCValue("_pid");
	packetTemp.use.data[0]=chan;
	packetTemp.use.head.DataLegnth=4+1+4+4;
	INT32_UNION tmp;
	tmp.Val=value;
	packetTemp.use.data[1]=tmp.byte.FB;
	packetTemp.use.data[2]=tmp.byte.TB;
	packetTemp.use.data[3]=tmp.byte.SB;
	packetTemp.use.data[4]=tmp.byte.LB;
        tmp.Val=ms;
	packetTemp.use.data[5]=tmp.byte.FB;
	packetTemp.use.data[6]=tmp.byte.TB;
	packetTemp.use.data[7]=tmp.byte.SB;
	packetTemp.use.data[8]=tmp.byte.LB;
	BowlerSPITranceive(& packetTemp, FALSE);
	if (packetTemp.use.head.RPC==_ERR){
		//enableDebug();
		//println_I("Failed to get Value on board: ");p_sl_I_I(chan);//print_I("\n");printPacket(& packetTemp);
		return ;
	}
}
INT32 UpdatePIDCurrent(BYTE chan){
	if(boardOK[chan]==FALSE){
		return 0;
	}
	INT32_UNION v;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_GET;
	packetTemp.use.head.RPC=GetRPCValue("_pid");
	packetTemp.use.data[0]=chan;
	packetTemp.use.head.DataLegnth=5;
	BowlerSPITranceive(& packetTemp, FALSE);
	if (packetTemp.use.head.RPC==_ERR){
		//enableDebug();
		//println_I("Failed to get Value on board: ");p_sl_I_I(chan);//print_I("\n");printPacket(& packetTemp);
		return 0;
	}
	v.byte.FB=packetTemp.use.data[1];
	v.byte.TB=packetTemp.use.data[2];
	v.byte.SB=packetTemp.use.data[3];
	v.byte.LB=packetTemp.use.data[4];
	return v.Val;
}

void killPid(int index){
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_CRIT;
	packetTemp.use.head.RPC=GetRPCValue("kpid");
	BowlerSPITranceiveLocal(& packetTemp, TRUE,index);
}

WORD GetADC(BYTE PIN){

}
INT32 currentEncoder[NUM_PID_GROUPS];

INT32 getCurrentEncoderValue(int index){
	return  currentEncoder[index];
}

BYTE checkSPIForAsyncPacket(BowlerPacket * Packet, BYTE board){
	setSS(board,ASSERTED);
	DelayMs(2);
	BYTE b = SPITransceve(JUNK_DATA);
        INT32_UNION v;
	if (b==BOWLER_VERSION){
                Packet->stream[0]=b;
                int i;
                for(i=1;i<11;i++){
                        Packet->stream[i]= SPITransceve(JUNK_DATA);
                }
                for(i=11;i<(11+Packet->use.head.DataLegnth);i++){
                        Packet->stream[i]= SPITransceve(JUNK_DATA);
                }
                setSS(board,NOT_ASSERTED);
                Packet->use.data[0] = board;
                if(Packet->use.head.RPC == _PID){
                    v.byte.FB=Packet->use.data[1];
                    v.byte.TB=Packet->use.data[2];
                    v.byte.SB=Packet->use.data[3];
                    v.byte.LB=Packet->use.data[4];
                    currentEncoder[board] =v.Val;
                    println_I("Got PID value event, board=");p_sl_I(board);print_I(" value=");p_sl_I(currentEncoder[board]);print_I("\n");
                }
                FixPacket( Packet);

		return TRUE;
	}else{
            setSS(board,NOT_ASSERTED);
            return FALSE;
        }
}
