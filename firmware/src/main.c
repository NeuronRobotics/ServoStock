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

//#define CALIBRATE_SERVO
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

static BowlerPacket MyPacket;
static RunEveryData pid ={0,40};

static RunEveryData pos ={0,50};


float height = 0;
int j=0,i=0;


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
        SYSTEMConfigPerformance(80000000);

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
	char * dev = "DeltaDoodle";
        println_I(dev);
	//This Method calls INTEnableSystemMultiVectoredInt();
	usb_CDC_Serial_Init(dev,macStr,0x04D8,0x3742);

       
        addNamespaceToList((NAMESPACE_LIST *)getBcsCartesianNamespace());
        addNamespaceToList((NAMESPACE_LIST *)getBcsPidNamespace());


        ATX_ENABLE(); // Turn on ATX Supply, Must be called before talking to the Encoders!!

        Print_Level l = getPrintLevel();
        println_I("Starting Encoders");
        initializeEncoders();// Power supply must be turned on first
        setPrintLevel(l);
        println_I("Starting Heater");
        initializeHeater();
        println_I("Starting Servos");
        initServos();
#if !defined(NO_PID)
        println_I("Starting PID");
        initPIDLocal();
        int i;
        for(i=3;i<numPidTotal;i++){
            SetPIDEnabled(i,FALSE);
        }
#endif
    

}
BOOL serVal =TRUE;

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

void SPItest(){
    RunEveryData loop = {0,100};
    BOOL val = TRUE;
    CloseSPI2();
    SPI_MISO_TRIS   =OUTPUT;
    SPI_MOSI_TRIS   =OUTPUT;
    SPI_CLK_TRIS    =OUTPUT;
    
    
    /*while (1){
      if(RunEvery(&loop)>0){
           //_RG7 = val;
           //_RG6 = val;
           if(val==TRUE)
               val=FALSE;
           else
               val=TRUE;
           _RG8 = val;
           println_E("Toggle pins");
        }
    }*/
}
BOOL printCalibrations = FALSE;
int main(){
    hardwareInit();
    runPidHysterisisCalibration(0);
    runPidHysterisisCalibration(1);
    runPidHysterisisCalibration(2);

    pid.MsTime=getMs();
    //startHomingLinks();
    setPrintLevelNoPrint();
    while(1){
        if(     printCalibrations == FALSE&&
                GetPIDCalibrateionState(0)==CALIBRARTION_DONE&&
                GetPIDCalibrateionState(1)==CALIBRARTION_DONE&&
                GetPIDCalibrateionState(2)==CALIBRARTION_DONE

                ){
            printCalibrations = TRUE;
            int group=0;
            for(group=0;group<3;group++){
                println_E("For Axis ");p_int_E(group);
                print_E(" upper: ");p_int_E(getPidGroupDataTable()[group].calibration.stop+getPidGroupDataTable()[group].calibration.upperHistoresis);
                print_E(" lower: ");p_int_E(getPidGroupDataTable()[group].calibration.stop+getPidGroupDataTable()[group].calibration.lowerHistoresis);
            }
            startHomingLinks();
        }
        //
        HomeLinks();
        //}
        bowlerSystem();
    }
}









