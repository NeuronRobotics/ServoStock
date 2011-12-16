/*
 * Pin_State.c
 *
 *  Created on: Nov 23, 2009
 *      Author: hephaestus
 */
#include "UserApp.h"

extern DATA_STRUCT DATA;

void InitPins(void){
	InitPinFunction();
	InitPinModes();
	int i=0;
	for(i=0;i<NUM_PINS;i++){
		initPinState(i);
	}
}


void ClearPinState(BYTE pin){

	BYTE current = GetChannelMode(pin);

	ClearPWM(pin);
	ClearADC(pin);
	ClearDCMotor(pin);

	if ( (current >= IS_SPI_MOSI)&&(current <= IS_SPI_SCK)){
		EEWriteMode(0,IS_DI);
		EEWriteMode(1,IS_DI);
		EEWriteMode(2,IS_DI);
		EEWriteMode(3,IS_DI);
	}
	if ((current == IS_UART_TX)||(current == IS_UART_RX)){
		StopUartPassThrough(pin);
		EEWriteMode(16,IS_DI);
		EEWriteMode(17,IS_DI);
	}
	SetPinTris(pin,INPUT);
}
