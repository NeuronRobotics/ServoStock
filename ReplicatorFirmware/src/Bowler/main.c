/*********************************************************************
 *
 *                  Example application for the Microchip BSD stack HTTP Server
 *
 *********************************************************************
 * FileName:        main.c
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement:
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the ?Company?) for its dsPIC30F and PICmicro? Microcontroller is intended 
 * and supplied to you, the Company?s customer, for use solely and
 * exclusively on Microchip's dsPIC30F and PICmicro Microcontroller products. 
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 ********************************************************************/
#include "EthernetController.h"
#include "Bowler/Bowler_Struct_Def.h"
#include "boards.h"
#include "main.h"

#define NO_ETHERNET

typedef enum {
    EXCEP_IRQ = 0,          // interrupt
    EXCEP_AdEL = 4,         // address error exception (load or ifetch)
    EXCEP_AdES=5,             // address error exception (store)
    EXCEP_IBE=6,              // bus error (ifetch)
    EXCEP_DBE=7,              // bus error (load/store)
    EXCEP_Sys=8,              // syscall
    EXCEP_Bp=9,               // breakpoint
    EXCEP_RI=10,               // reserved instruction
    EXCEP_CpU=11,              // coprocessor unusable
    EXCEP_Overflow=12,         // arithmetic overflow
    EXCEP_Trap=13,             // trap (possible divide by zero)
    EXCEP_IS1 = 16,         // implementation specfic 1
    EXCEP_CEU=17,              // CorExtend Unuseable
    EXCEP_C2E=18               // coprocessor 2
} excep_code;

typedef union {
    UINT32 value;
    struct{
        unsigned :2;//reserved
        unsigned EXCCODE :5;//Exception code
        unsigned :1;//reserved
        unsigned IP:2;//Controls request for software interrupt
        unsigned RIPL :6;//Request Interupt Priority Level
        unsigned :6;//reserved
        unsigned R1 :1;//undocumented
        unsigned IV :1;//Interrupt Vector Bit
        unsigned :2;//reserved
        unsigned R2 :1;//undocumented
        unsigned DC :1;//Disable Count
        unsigned CE:2;// Coprocessor Exception Bits
        unsigned TI :1;// Timer Interrupt
        unsigned BD :1;// Branch Delay
    };

}cause_union;
void _general_exception_handler(unsigned cause, unsigned status){
        unsigned int x = 0;
        asm volatile ("move %0, $ra" : "=r" (x));
        asm volatile ("sw $ra, %0" : "=m" (x));
//        /register unsigned int cp0count asm ("c0r1");

        cause_union u;
        u.value=cause;

        setLed(1,0,0);

        print_I("\r\n\r\n\r\nException handeler!! cause=");
        prHEX32(cause,INFO_PRINT);print_I(" status=");
        prHEX32(status,INFO_PRINT);
        print_I(" exec code=");
        p_sl_I(u.EXCCODE);
        print_I(" return address=");
        prHEX32(x,INFO_PRINT);
        println_I("===    CAUSE val Parsed    ===\n\r");
        print_I("31:\t");prHEX32(u.BD,INFO_PRINT);print_I("\t Exception During Branch Delay\r\n");
        print_I("30:\t");prHEX32(u.TI,INFO_PRINT);print_I("\t Exception During Pending Timer Interupt\r\n");
        print_I("29:28:\t");prHEX32(u.CE,INFO_PRINT);print_I("\t Coproc Ref number fpr a coprpc unisable exception\r\n");
        print_I("27:\t");prHEX32(u.DC,INFO_PRINT);print_I("\t Disable Count Register\r\n");
        print_I("23:\t");prHEX32(u.IV,INFO_PRINT);print_I("\t Special Interrupt Vector used\r\n");
        print_I("15:10:\t");prHEX32(u.RIPL,INFO_PRINT);print_I("\t Pending Interrupt indicator or Requested Interrupt Priority Level\r\n");
        print_I("6:2:\t");prHEX32(u.EXCCODE,INFO_PRINT);print_I("\t Exception Code\r\n");
        switch(u.EXCCODE){
            case 0: print_I("\t\tInterrupt\r\n"); break;
            case 4: print_I("\t\tAddress Error Exception (Load or Instruction Fetch)\r\n"); break;
            case 5: print_I("\t\tAddress Error Exception (Store)\r\n"); break;
            case 6: print_I("\t\tBus Error Exception (Instruction Fetch)\r\n"); break;
            case 7: print_I("\t\tBus Error Exception (Data Reference: load or store)\r\n"); break;
            case 8: print_I("\t\tSyscall Exception\r\n"); break;
            case 9: print_I("\t\tBreakpoint Exception\r\n"); break;
            case 10: print_I("\t\tReversed Instruction Exception\r\n"); break;
            case 11: print_I("\t\tCoProcessor Unusable exception\r\n"); break;
            case 12: print_I("\t\tArithmatic Overflow Exception\r\n"); break;
            case 13: print_I("\t\tTrap Exception\r\n"); break;
            case 16: print_I("\t\tImplementation Specific Exception (COP2)\r\n"); break;
            case 17: print_I("\t\tCorExtend Unusable\r\n"); break;
            case 18: print_I("\t\tCoprocessor 2 Exceptions\r\n"); break;
            default: print_I("\t\treserved\r\n"); break;

        }

        println_I("=== CoProc 0 Register Dump ===");
        println_I(" BadVAddr=\t");
        prHEX32(_CP0_GET_BADVADDR(),INFO_PRINT);
        println_I(" Compare=\t");
        prHEX32(_CP0_GET_COMPARE(),INFO_PRINT);
        println_I(" Count=\t");
        prHEX32(_CP0_GET_COUNT(),INFO_PRINT);
        println_I(" Status=\t");
        prHEX32(_CP0_GET_STATUS(),INFO_PRINT);
        println_I(" EPC=\t");
        prHEX32(_CP0_GET_EPC(),INFO_PRINT);
        println_I(" PRID=\t");
        prHEX32(_CP0_GET_PRID(),INFO_PRINT);
        println_I(" EBASE=\t");
        prHEX32(_CP0_GET_EBASE(),INFO_PRINT);
        println_I(" CONFIG=\t");
        prHEX32(_CP0_GET_CONFIG(),INFO_PRINT);
        println_I(" ERROREPC=\t");
        prHEX32(_CP0_GET_DEPC(),INFO_PRINT);
        println_I(" ERROREPC=\t");
        prHEX32(_CP0_GET_DEPC(),INFO_PRINT);
        print_I(" \r\n\r\n\r\n");


        
        print_I("\n\r1");
        DelayMs(1000);

        print_I("\n\r2");
	while(1){
		if(isPressed()	)
			Reset();
		setLed(1,0,0);
		DelayMs(1000);
		setLed(0,1,0);
		DelayMs(1000);
	}
}

///////////////////////////////////////////////////////
const BYTE MY_MAC_ADDRESS[]={0x74,0xf7,0x26,0x01,0x01,0x01};
extern const MAC_ADDR Broadcast __attribute__ ((section (".scs_global_var")));
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));
const unsigned char pidNSName[] = "bcs.pid.*;0.3;;"; 
static RunEveryData pid = {0,1.0};
static RunEveryData async = {0,200.0};
static BowlerPacket Packet;

int j=0,i=0;
BYTE Bowler_Server_Local(BowlerPacket * Packet){
	if (GetBowlerPacket_arch(Packet)){
		setLed(1,1,1);
                if(Packet->use.head.RPC != _PNG){
                    println_I("Got:");printPacket(Packet,INFO_PRINT);
                }
		if ( (CheckAddress(MyMAC.v,Packet->use.head.MAC.v) == TRUE) || ((CheckAddress((BYTE *)Broadcast.v,(BYTE *)Packet->use.head.MAC.v) == TRUE) )) {
			Process_Self_Packet(Packet);
			for (i=0;i<6;i++){
				Packet->use.head.MAC.v[i]=MyMAC.v[i];
			}
			SetCRC(Packet);
			PutBowlerPacket(Packet);
                         if(Packet->use.head.RPC != _PNG){
                            println_I("Response:");printPacket(Packet,INFO_PRINT);
                         }
		}else{
			//println_I("Packet not addressed to me: ");printByteArray(Packet->use.head.MAC.v,6); print_I(" is not mine: ");printByteArray(MyMAC.v,6);
		}
		setLed(0,0,1);
		return TRUE;
	}//Have a packet

	return FALSE;
}

void encoderTest(){
    println_I("\tStarting test");
    BYTE i;
    AS5055ReadPacket read;
    AS5055CommandPacket cmd;
    OpenSPI1(CLK_POL_ACTIVE_LOW\
            |SPI_MODE8_ON|ENABLE_SDO_PIN|SLAVE_ENABLE_OFF|SPI_CKE_ON\
            |MASTER_ENABLE_ON|SEC_PRESCAL_8_1|PRI_PRESCAL_64_1, SPI_ENABLE);

    ENC2_CSN=CSN_Enabled;
    ENC3_CSN=CSN_Enabled;


    cmd.regs.Address=AS5055REG_AutomaticGainControl;
    cmd.regs.RWn=1; // Read
    cmd.regs.PAR=AS5055CalculateParity(cmd.uint0_15);

    read.bytes.ubyte8_15=SPITransceve(cmd.bytes.ubyte8_15);
    read.bytes.ubyte0_7=SPITransceve(cmd.bytes.ubyte0_7);

    println_I("Encoder data: ");p_ul_I(read.regs.Data);
    ENC2_CSN=CSN_Disabled;
    ENC3_CSN=CSN_Disabled;
    while(SpiChnIsBusy(1)); // chill
}

int main()
{
        setPrintLevelInfoPrint();
	initLed();
        setLed(1,1,1);
	initButton();
        initBackplaneHardware();
        int i;
        
	Bowler_Init();
	// enable driven to 3.3v on uart 1
	mPORTDOpenDrainClose(BIT_3); mPORTFOpenDrainClose(BIT_5);
	println_I("Starting PIC initialization");
	char macStr[13];
	
	for (i=0;i<6;i++){
		macStr[j++]=GetHighNib(MyMAC.v[i]);
		macStr[j++]=GetLowNib(MyMAC.v[i]);
	}
	macStr[12]=0;
	println_I("MAC address is =");
	print_I(macStr);
	char * dev = "Ethernet Test";
	//This Method calls INTEnableSystemMultiVectoredInt();
	usb_CDC_Serial_Init(dev,macStr,0x04D8,0x0001);
	AddNamespace(sizeof(pidNSName), pidNSName);
	setMethodCallback(BOWLER_GET,UserGetRPCs);
	setMethodCallback(BOWLER_POST,UserPostRPCs);
	setMethodCallback(BOWLER_CRIT,UserCriticalRPCs);
	BowlerSPIInit();
#if !defined(NO_ETHERNET)
	InitializeEthernet();
#endif

	BowlerPacket MyPacket;

	println_I("#Ready...");
        while(1){
            encoderTest();
            DelayMs(100);
        }
        setPrintLevelInfoPrint();
	while(1){
            //println_I("Loop");
            setLed(1,0,0);
            if(isPressed()	){
                    U1CON = 0x0000;
                    while(isPressed()){
                            setLed(1,1,1);
                    }
                    DelayMs(100);
                    SoftReset();
            }
            Bowler_Server_Local(&MyPacket);
            #if !defined(NO_ETHERNET)
                RunEthernetServices(&MyPacket);
            #endif
            BOOL async = FALSE;
            for(i=0;i<NUM_PID_GROUPS;i++){
            	if(checkSPIForAsyncPacket(&MyPacket, i)){
                    print_I("\nGot Async for board: ");p_sl_I(i);print_I("\n");printPacket(&MyPacket,INFO_PRINT);
                    //push(&MyPacket);
                    async = TRUE;
                }
            }
            if(async){
            	pushEncoders();
            }

	}
}










