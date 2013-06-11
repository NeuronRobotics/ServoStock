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

#include "Bowler/Bowler_Struct_Def.h"
#include "main.h"

#ifdef USB_A0_SILICON_WORK_AROUND
	#pragma config UPLLEN   = OFF       // USB PLL Enabled (A0 bit inverted)
#else
	#pragma config UPLLEN   = ON        // USB PLL Enabled
#endif

#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor

#pragma config FWDTEN   = OFF           // Watchdog Timer
//#pragma config FWDTEN   = ON          // Watchdog Timer

#pragma config WDTPS    = PS2048           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = HS            // Primary Oscillator
#pragma config IESO     = ON            // Internal/External Switch-over
#pragma config FSOSCEN  = OFF            // Secondary Oscillator Enable (KLO was off)
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
#pragma config DEBUG    = OFF            // Background Debugger Enable

#if defined(__32MX795F512L__)
    #pragma config FVBUSONIO = OFF //Shuts off control of VBUSON pin on RB5
#endif

#define SYS_FREQ 			(80000000L)

#define NO_ETHERNET
#define CALIBRATE_SERVO
//#define CALIBRATE
//#define NO_PID
//#define TEST_MOTION
//#define EXTRUDER_TEST

///////////////////////////////////////////////////////
const BYTE MY_MAC_ADDRESS[]={0x74,0xf7,0x26,0x01,0x01,0x01};
extern const MAC_ADDR Broadcast __attribute__ ((section (".scs_global_var")));
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));


//static const unsigned char deltaNSName[] = "bcs.delta.*;0.3;;";
//static const unsigned char printNSName[]  = "bcs.printer.*;0.3;;";

static BowlerPacket Packet;
static int homingAllLinks = TRUE;
static BowlerPacket MyPacket;
static RunEveryData pid ={0,40};
static RunEveryData calibrationTest ={0,1000};

static RunEveryData pos ={0,5000};

static int linkValue[3];


float height = 0;
int j=0,i=0;

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

        //setLed(1,0,0);
        setPrintLevelInfoPrint();
        
        print_I("\r\n\r\n\r\nException handeler!! cause=");
        prHEX32(cause,INFO_PRINT);print_I(" status=");
        prHEX32(status,INFO_PRINT);
        print_I(" exec code=");
        p_int_I(u.EXCCODE);
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
//		if(isPressed()	)
//			Reset();
//		setLed(1,0,0);
//		DelayMs(1000);
//		setLed(0,1,0);
//		DelayMs(1000);
	}
}


BYTE Bowler_Server_Local(BowlerPacket * Packet){
  
        Print_Level l = getPrintLevel();
        //setPrintLevelNoPrint();
	if (GetBowlerPacket_arch(Packet)){
		//setLed(1,1,1);
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
		//setLed(0,0,1);
                setPrintLevel(l);
		return TRUE;
	}//Have a packet
        setPrintLevel(l);
	return FALSE;
}


void hardwareInit(){
     // Configure the device for maximum performance but do not change the PBDIV
	// Given the options, this function will change the flash wait states, RAM
	// wait state and enable prefetch cache but will not change the PBDIV.
	// The PBDIV value is already set via the pragma FPBDIV option above..
	SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

        setPrintLevelInfoPrint();
        ATX_DISENABLE();

        Pic32_Bowler_HAL_Init();

	Bowler_Init();
        println_I("\n\n\nStarting PIC initialization");
        DelayMs(2000);//This si to prevent runaway during programming
	// enable driven to 3.3v on uart 1
	mPORTDOpenDrainClose(BIT_3); mPORTFOpenDrainClose(BIT_5);
	char macStr[13];

	for (i=0;i<6;i++){
		macStr[j++]=GetHighNib(MyMAC.v[i]);
		macStr[j++]=GetLowNib(MyMAC.v[i]);
	}
	macStr[12]=0;
	println_I("MAC address is =");
	print_I(macStr);
	char * dev = "ServoBoard";
        println_I(dev);
	//This Method calls INTEnableSystemMultiVectoredInt();
	usb_CDC_Serial_Init(dev,macStr,0x04D8,0x0001);

       
        addNamespaceToList((NAMESPACE_LIST *)getBcsCartesianNamespace());
        addNamespaceToList((NAMESPACE_LIST *)getBcsPidNamespace());



#if !defined(NO_ETHERNET)
	InitializeEthernet();
#endif

        ATX_ENABLE(); // Turn on ATX Supply, Must be called before talking to the Encoders!!

        Print_Level l = getPrintLevel();
        setPrintLevelNoPrint();
        initializeEncoders();// Power supply must be turned on first
        setPrintLevel(l);
        initializeHeater();

        initServos();
#if !defined(NO_PID)
        initPIDLocal();
#endif


#if defined(CALIBRATE)
        println_I("#Calibrating...");
        setServo(LINK0_INDEX, servoCalebrateValue,0);
        setServo(LINK1_INDEX, servoCalebrateValue,0);
        setServo(LINK2_INDEX, servoCalebrateValue,0);
        linkValue[0]=0;
        linkValue[1]=0;
        linkValue[2]=0;
#else
        homingAllLinks = FALSE;
        setPidIsr(TRUE);
        l = getPrintLevel();
        setPrintLevelNoPrint();
        pidReset(EXTRUDER0_INDEX,0);
        pidReset(LINK0_INDEX,0);
        pidReset(LINK1_INDEX,0);
        pidReset(LINK2_INDEX,0);
        setPrintLevel(l);
#endif
    SetPID(HEATER0_INDEX,0);
#if defined(CALIBRATE_SERVO)
    runServoCalibration(EXTRUDER0_INDEX);

#endif
        
}

void bowlerSystem(){
    Bowler_Server_Local(&MyPacket);
    float diff = RunEvery(&pid);
    if(diff>0){
        RunNamespaceAsync(&MyPacket,&asyncCallback);
        if(diff>pid.setPoint){
            println_E("Time diff ran over! ");p_fl_E(diff);
            pid.MsTime=getMs();
        }
    }
}

int main(){
    hardwareInit();
    while(1){
        if(homingAllLinks){
            HomeLinks();
        }
        bowlerSystem();
    }
}


void HomeLinks(){
#if defined(CALIBRATE)
    if(RunEvery(&calibrationTest)>0){
        float boundVal = 2.0;
        float l0=(float)readEncoder(LINK0_INDEX);
        float l1=(float)readEncoder(LINK1_INDEX);
        float l2=(float)readEncoder(LINK2_INDEX);
        if( bound((float)linkValue[0], l0, boundVal, boundVal)&&
            bound((float)linkValue[1], l1, boundVal, boundVal)&&
            bound((float)linkValue[2], l2, boundVal, boundVal)
          ){
            homingAllLinks = FALSE;
            println_E("\n\nStopped At:\n\r\tLink 0 value:");p_int_E(l0);
            println_E("\tLink 1 value:");p_int_E(l1);
            println_E("\tLink 2 value:");p_int_E(l2);
            println_E("Previous:\n\r\tLink 0 value:");p_int_E(linkValue[0]);
            println_E("\tLink 1 value:");p_int_E(linkValue[1]);
            println_E("\tLink 2 value:");p_int_E(linkValue[2]);
            pidReset(LINK0_INDEX,(INT32)servoHomeValue);
            pidReset(LINK1_INDEX,(INT32)servoHomeValue);
            pidReset(LINK2_INDEX,(INT32)servoHomeValue);
            pidReset(EXTRUDER0_INDEX,0);
            println_E("Calibration Done!");
            setServo(LINK0_INDEX, 128,0);
            setServo(LINK1_INDEX, 128,0);
            setServo(LINK2_INDEX, 128,0);
            setPidIsr(TRUE);
            pos.MsTime=getMs();
            initializeCartesianController();
            cancelPrint();
        }else{
            linkValue[0]=l0;
            linkValue[1]=l1;
            linkValue[2]=l2;
        }
    }
#endif
}







