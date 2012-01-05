/*
 * UserInit.c
 *
 *  Created on: Nov 29, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"

BYTE InputState[NUM_PINS];

BYTE SaveTheState=0;

#define mInitSwitch()      (_TRISB0)=1;

const BYTE MY_MAC_ADDRESS[]={0x74,0xf7,0x26,0x01,0x01,0x01};

extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));
/*
const unsigned char ioNSName[] = "bcs.io.*;0.3;http://neuronrobotics.com/wiki/Bcs-io;";

const unsigned char setModeNSName[] = "bcs.io.setmode.*;0.3;http://neuronrobotics.com/wiki/Bcs-io-setmode;";

const unsigned char dyioNSName[] = "neuronrobotics.dyio.*;0.3;http://neuronrobotics.com/wiki/Neuronrobotics-dyio;";

const unsigned char pidNSName[] = "bcs.pid.*;0.3;http://neuronrobotics.com/wiki/Bcs-pid;";

const unsigned char dypidNSName[] = "bcs.pid.dypid.*;0.3;http://neuronrobotics.com/wiki/Bcs-pid-dypid;";
 */

const unsigned char ioNSName[] = "bcs.io.*;0.3;;";

const unsigned char setModeNSName[] = "bcs.io.setmode.*;;";

const unsigned char dyioNSName[] = "neuronrobotics.dyio.*;0.3;;";

const unsigned char pidNSName[] = "bcs.pid.*;0.3;;";

const unsigned char dypidNSName[] = "bcs.pid.dypid.*;0.3;;";

const unsigned char safeNSName[] = "bcs.safe.*;0.3;;";

void hardwareInit(){
	StartCritical();
	FlashGetMac(MyMAC.v);
	char macStr[13];
	int j=0,i=0;
	for (i=0;i<6;i++){
		macStr[j++]=GetHighNib(MyMAC.v[i]);
		macStr[j++]=GetLowNib(MyMAC.v[i]);
	}
	macStr[12]=0;
	printfDEBUG("MAC address is =");
	printfDEBUG_NNL(macStr);
	char * dev = "DyIO v.3";

	usb_CDC_Serial_Init(dev,macStr,0x04D8,0x3742);
	mInitSwitch();

	for (i=0;i<6;i++){
		MyMAC.v[i]= MY_MAC_ADDRESS[i];
	}

	Init_FLAG_BUSY_ASYNC();
	InitCTS_RTS_HO();

	//AVR Reset pin
	InitAVR_RST();
	ReleaseAVRReset();


	ConfigUARTOpenCollector();
	ConfigUARTRXTristate();


	InitLEDS();
	SetColor(0,0,1);
	//Starts Timer 3
	InitCounterPins();
	InitADC();
	println("Adding DyIO namespaces:");
	AddNamespace(sizeof(ioNSName), ioNSName);
	AddNamespace(sizeof(setModeNSName), setModeNSName);
	AddNamespace(sizeof(dyioNSName), dyioNSName);
	AddNamespace(sizeof(pidNSName), pidNSName);
	AddNamespace(sizeof(dypidNSName), dypidNSName);
	AddNamespace(sizeof(safeNSName), safeNSName);

	setMethodCallback(BOWLER_GET,UserGetRPCs);
	setMethodCallback(BOWLER_POST,UserPostRPCs);
	setMethodCallback(BOWLER_CRIT,UserCriticalRPCs);
	BYTE rev [] = {MAJOR_REV,MINOR_REV,FIRMWARE_VERSION};
	FlashSetFwRev(rev);

	//Starts co-proc uart
	initCoProcCom();

	EndCritical();
	INTEnableSystemMultiVectoredInt();
}

void UserInit(void){
	println("Starting PIC initialization");
	hardwareInit();
	println("Hardware Init done");

	InitPins();

	CheckRev();

	LoadEEstore();

	LoadDefaultValues();

	CartesianControllerInit();

	InitPID();

	UpdateAVRLED();

	//println("Syncing modes:");
	SyncModes();
	//println("Setting modes:");

	lockServos();

	printfDEBUG("###Starting PIC In Debug Mode###\n");// All printfDEBUG functions do not need to be removed from code if debug is disabled
}


