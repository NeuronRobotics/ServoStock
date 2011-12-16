/*
 * ChannelMode.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"

extern DATA_STRUCT DATA;

BOOL setMode(BYTE pin,BYTE mode);
void setAsync(BYTE channel,BOOL async);
void setAsyncLocal(BYTE channel,BOOL async);
void SyncModes(void);
BOOL isAsync[NUM_PINS];



void InitPinStates(void){
	SyncModes();
	int i;
	for (i=0;i<NUM_PINS;i++){
		setMode(i,GetChannelMode(i));
	}
}
BYTE GetChannelMode(BYTE chan){
	//Strip off the internally stored High Bit
	return DATA.PIN[chan].State & 0x7f;
}
BOOL SetChannelMode(BowlerPacket * Packet){

	BYTE pin =Packet->use.data[0];

	BYTE mode=Packet->use.data[1]& 0x7f;

	if(Packet->use.head.DataLegnth == 7){
		isAsync[pin] = Packet->use.data[2]?TRUE:FALSE;
	}

	if(setMode(pin,mode)){
		//printfDEBUG("Valid Mode, setting...");
		//printfDEBUG("Sending Mode Set To Co Proc");

		//ASYNC managed in EEPROM on co proc
		SendPacketToCoProc(Packet);

		SyncModes();
		READY(Packet,4,33);
		if(isAsync[pin])
			startAdvancedAsyncDefault(pin);
		return TRUE;
	}else{
		printfDEBUG("Mode Invalid!");
		return FALSE;
	}

}

BOOL SetAllChannelMode(BowlerPacket * Packet){
	SendPacketToCoProc(Packet);
	SyncModes();
	int i=0;
	for(i=0;i<NUM_PINS;i++){
		if(IsAsync(i))
			startAdvancedAsyncDefault(i);
	}
	return TRUE;
}


BOOL setMode(BYTE pin,BYTE mode){
	//printfDEBUG("Setting Mode: ");printMode(mode);printfDEBUG_NNL(" on: ");printfDEBUG_UL(pin);
	BYTE currentMode = GetChannelMode(pin);
	ClearCounter(pin);
	StopSPI(currentMode);
	clearPPM(pin);
	switch (mode & 0x7f){

	case IS_SERVO:
		if(((pin < 12) && (isRegulated_0() == 0)) || ((pin >= 12) && (isRegulated_1()== 0))   ){
			//printfDEBUG_NNL("|Mode is now servo");
			break;
		}else{
			//printfDEBUG_NNL(" Servo Mode could not be set, voltage invalid");
			return FALSE;
		}
	case IS_SPI_MOSI:
	case IS_SPI_MISO:
	case IS_SPI_SCK:
		if(DATA.FUNCTION[pin].HAS_SPI != FALSE){
			//printfDEBUG_NNL("|Mode is now SPI");
			InitSPI();
			break;
		}else{
			return FALSE;
		}

	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		if(DATA.FUNCTION[pin].HAS_COUNTER_INPUT != FALSE){
			//printfDEBUG_NNL("|Mode is now Counter Input");
			StartCounterInput(pin);
			break;
		}else{
			//printfDEBUG_NNL(", Counter Input not availible");
			return FALSE;
		}
		break;
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_OUTPUT_DIR:
	case IS_COUNTER_OUTPUT_HOME:
		if(DATA.FUNCTION[pin].HAS_COUNTER_OUTPUT != FALSE){
			//printfDEBUG_NNL("|Mode is now Counter Output");
			StartCounterOutput(pin);
			break;
		}else{
			//printfDEBUG_NNL(", Counter Output not availible");
			return FALSE;
		}
		break;
	case IS_PPM_IN:
		//println("Setting up PPM...");
		startPPM(pin);
		break;
	}
	DATA.PIN[pin].State=mode;
	return TRUE;
}
void setAsync(BYTE channel,BOOL async){
	SyncModes();
	BYTE mode = GetChannelMode(channel);
	mode = (async)?mode|0x80:mode;
	DATA.PIN[channel].State = mode;
	SetCoProcMode(channel,mode);
	startAdvancedAsyncDefault(channel);
}

void setAsyncLocal(BYTE channel,BOOL async){
	isAsync[channel]=async;
}

BOOL IsAsync(BYTE channel){
	if (isAsync[channel]){
		return TRUE;
	}
	BYTE mode=GetChannelMode(channel);
	switch(mode){
	case IS_UART_RX:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_INPUT_INT:
		return TRUE;
	default:
		return FALSE;
	}
}

