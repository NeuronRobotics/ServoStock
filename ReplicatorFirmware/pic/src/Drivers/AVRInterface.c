/*
 * AVRInterface.c
 *
 *  Created on: May 23, 2010
 *      Author: acamilo
 */
#include "UserApp.h"

	// acamilo:
	// 		change fuses to f7
	// 		SUT changed to LONG to increase oscilator stabalization time.
	// 		Oscilator drive method changed to FullSwing from Low Power.
	// 		SEE DS section 8.4 (p. 34)
#define AVR_LOW			0xf7
#define AVR_HIGH		0xd1
#define AVR_EXT			0xff
//static BYTE progmode []						={0xAC,0x53,0x00,0x00};

void getCmd(BYTE comand, BYTE addrHigh, BYTE addrLow, BYTE data) {
	GetByteSPI(comand);
	GetByteSPI(addrHigh);
	GetByteSPI(addrLow);
	GetByteSPI(data);
}

void writeLowFuse()
{
  getCmd(0xac, 0xa0, 0, AVR_LOW);

  DelayMs(5);
}


void writeHighFuse()
{
  getCmd(0xac, 0xa8, 0,AVR_HIGH);
  DelayMs(5);
}

void PowerCycleAVR(){
	println("Power cycling the AVR");
	HoldAVRReset();
//	getCommand(progmode);
//	writeLowFuse();
//	writeHighFuse();
//	writeExtendedFuse();
	ReleaseAVRReset();
}
void HoldAVRReset(void){
	AVR_RST_IO=0;
	println("Holding AVR in reset");
	DelayMs(10);
}

void ReleaseAVRReset(void){
	AVR_RST_IO=1;
	UpdateAVRLED();
	DelayMs(30);
	println("Release AVR in reset");
}

BOOL writeAVRTempFlashPageLowByte(BYTE data, BYTE address){
	GetByteSPI(0x40);
	GetByteSPI(0x00);
	GetByteSPI(address);
	BYTE result = GetByteSPI(data);
	DelayMs(10);
	if (result==address) return TRUE;
	return FALSE;
}

BOOL writeAVRTempFlashPageHighByte(BYTE data, BYTE address){
	GetByteSPI(0x48);
	GetByteSPI(0x00);
	GetByteSPI(address);
	BYTE result = GetByteSPI(data);
	DelayMs(10);
	if (result==address) return TRUE;
	return FALSE;

}



void writeExtendedFuse()
{
  getCmd(0xac, 0xa4, 0, AVR_EXT);
  DelayMs(5);
}
