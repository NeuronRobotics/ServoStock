/*
 * ChannelMode.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"

extern DATA_STRUCT DATA;

void InitPinModes(void){
	BYTE i;
	BYTE mode=0;
	for (i=0;i<24;i++){
		//ClearPinState(i);
		SetPinTris(i,INPUT);
		SetDIO(i,0);
		SetPWM(i,EEReadValue(i));
		SetServoPos(i,EEReadValue(i),0);
		mode=EEReadMode(i);
		if((mode == 0)||(mode == 255)||(mode == 1)){
			EEWriteMode(i,IS_DI);
		}
		setMode(i,EEReadMode(i));
	}

}


BYTE GetChannelMode(BYTE chan){
	return EEReadMode(chan) & 0x7f;
}
BOOL SetChannelMode(BowlerPacket * Packet){
	//BYTE isAsync;
	BYTE pin = Packet->use.data[0];
	BYTE mode = Packet->use.data[1];
	if(Packet->use.head.DataLegnth>6){
		if((Packet->use.data[2]>0))
			mode |=0x80;
	}
	return setMode(pin,mode);
}

BOOL SetAllChannelMode(BowlerPacket * Packet){
	BYTE i;
	for (i=0;i<NUM_PINS;i++){
		if(!setMode(i,Packet->use.data[i])){
			return FALSE;
		}
	}
	return TRUE;
}


BOOL setMode(BYTE pin,BYTE mode){
	ClearPinState(pin);
	//println("Pin :");p_ul(pin);print(" is mode: ");printMode(mode);
	//BYTE pwm,dir;
	if (mode == NO_CHANGE){
		return TRUE;
	}
	switch (mode & 0x7F){
	case HIGH_IMPEDANCE:
		ClearPinState(pin);
		// Return here so as not to save this state to the eeprom
		return TRUE;
	case IS_UART_TX:
	case IS_UART_RX:
		if(pin == 17 || pin == 16){
			configPinMode(16,IS_UART_TX,OUTPUT,ON);
			configPinMode(17,IS_UART_RX,INPUT,ON);
			InitUART();
			return TRUE;
		}
		break;
	case IS_SPI_MOSI:
	case IS_SPI_MISO:
	case IS_SPI_SCK:
		if(DATA.FUNCTION[pin].HAS_SPI  ){
			configPinMode(0,IS_SPI_SCK,INPUT,ON);
			configPinMode(1,IS_SPI_MISO,INPUT,ON);
			configPinMode(2,IS_SPI_MOSI,INPUT,ON);
			return TRUE;
		}
		break;
	case IS_ANALOG_IN:
		configPinMode(pin,mode,INPUT,OFF);
		if(InitADC(pin)){
			return TRUE;
		}
		break;
	case IS_PWM:
		if(InitPWM(pin)){
			return TRUE;
		}
		return FALSE;
	case IS_DC_MOTOR_VEL:
	case IS_DC_MOTOR_DIR:
		if(InitDCMotor(pin)){
			return TRUE;
		}
		return FALSE;
	case IS_SERVO:
		InitServo(pin);
		configPinMode(pin,mode,OUTPUT,OFF);
		return TRUE;
	case IS_DO:
		configPinMode(pin,mode,OUTPUT,OFF);
		return TRUE;
	case IS_DI:
	case IS_PPM_IN:
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_OUTPUT_DIR:
	case IS_COUNTER_OUTPUT_HOME:
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		configPinMode(pin,mode,INPUT,ON);
		return TRUE;
	default:
		configPinMode(pin,mode,INPUT,ON);
		return TRUE;
	}
	return FALSE;
}

void configPinMode(BYTE pin,BYTE mode,BYTE tris,BYTE io){
	ClearPinState(pin);
	SetPinTris(pin,tris);
	SetDIO(pin,io);
	//DATA.PIN[pin].State=mode;
	//print("\nSetting mode: ");printMode(mode);print(" on chan: ");p_ul(pin);
	EEWriteMode(pin,mode);
}



BOOL IsAsync(BYTE channel){
	if (EEReadMode(channel)>0x80){
		return TRUE;
	}
	BYTE mode=GetChannelMode(channel);
	switch(mode){
	case IS_UART_RX:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
		return TRUE;
	default:
		return FALSE;
	}
}
