/*
 * ChannelValues.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"

void set8bit(BowlerPacket * Packet,BYTE val);
void set16bit(BowlerPacket * Packet,UINT16 val);
void set32bit(BowlerPacket * Packet,INT32 val);

INT32 get32bit(BowlerPacket * Packet);

BOOL SaveValue(BYTE pin,BYTE val){
	switch(GetChannelMode(pin)){
	case IS_SERVO:
	case IS_PWM:
		EEWriteValue(pin,val);
		return TRUE;
	default:
		return FALSE;
	}
}

BOOL GetChannelValue(BowlerPacket * Packet){
	BOOL ret=FALSE;
	BYTE pin = Packet->use.data[0];
	BYTE mode = GetChannelMode(pin);
	int i;
	UINT16 val=GetChanVal(pin);
	if(IsAsync(pin)){
		AsynAck();
	}
	Packet->use.head.Method=BOWLER_POST;
	if ((mode == IS_DC_MOTOR_VEL)||(mode == IS_DC_MOTOR_DIR)||(mode == IS_DO)|| (mode == IS_PWM)|| (mode == IS_SERVO) || (mode == IS_DI) ||(mode == IS_COUNTER_OUTPUT_HOME)||(mode == IS_COUNTER_INPUT_HOME)){
		set8bit(Packet, val);
		Packet->use.head.DataLegnth=6;
		ret = TRUE;
	}else if ((mode == IS_ANALOG_IN)){
		val=GetADC(pin);
		set16bit(Packet,val);
		Packet->use.head.DataLegnth=7;
		ret = TRUE;
	}else if ( (mode == IS_UART_TX) || (mode == IS_UART_RX)){
		//Number of bytes in the stream to be sent
		Packet->use.head.DataLegnth=5;
		UINT16 numBytes=Get_UART_Byte_CountPassThrough();
		if(numBytes>0){
			UARTGetArrayPassThrough(Packet->use.data,numBytes);
			for (i=0;i<numBytes;i++){
				Packet->use.data[(numBytes)-i]=Packet->use.data[(numBytes-1)-i];
			}
			Packet->use.data[0]=17;
			Packet->use.head.DataLegnth+=numBytes;
		}
		return TRUE;
	}else{
		return FALSE;
	}
	return ret;
}

UINT16 GetChanVal(BYTE pin){
	UINT16 val;
	BYTE mode = GetChannelMode(pin);
	switch (mode){
	case HIGH_IMPEDANCE:
		val=1;
		break;
	case IS_DI:
	case IS_DO:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
		val = GetDIO(pin);
		break;
	case IS_SERVO:
		val = GetServoPos(pin);
		break;
	case IS_PWM:
		val = GetPWM(pin);
		break;
	case IS_DC_MOTOR_VEL:
	case IS_DC_MOTOR_DIR:
		val = GetDCMotor(pin);
		break;
	case IS_ANALOG_IN:
		val=GetADC(pin);
		break;
	default:
		val=1;
	}
	return val;
}
BOOL isASetableMode(BYTE mode){
	if ((mode == IS_DO)|| (mode == IS_SERVO) || (mode == IS_PWM)|| (mode == IS_DI)||(mode == IS_DC_MOTOR_VEL)||(mode == IS_DC_MOTOR_DIR)){
		return TRUE;
	}
	return FALSE;
}

BOOL SetAllChannelValue(BowlerPacket * Packet){
	UINT32_UNION time;
	UINT32_UNION data;
	BYTE i;
	time.byte.FB=Packet->use.data[0];
	time.byte.TB=Packet->use.data[1];
	time.byte.SB=Packet->use.data[2];
	time.byte.LB=Packet->use.data[3];
	for(i=0;i<NUM_PINS;i++){
		data.byte.FB=Packet->use.data[4+(i*4)];
		data.byte.TB=Packet->use.data[5+(i*4)];
		data.byte.SB=Packet->use.data[6+(i*4)];
		data.byte.LB=Packet->use.data[7+(i*4)];
		if(isASetableMode(GetChannelMode(i))){
			 SetChanVal(i, data.Val, time.Val);
		}
	}

	return TRUE;
}
BOOL SetChannelValue(BowlerPacket * Packet){
	BOOL ret=FALSE;
	BYTE pin = Packet->use.data[0];
	BYTE mode = GetChannelMode(pin);
	BYTE bval;
	UINT16_UNION wval;
	BYTE zone=128;
	//println("Setting Value of mode: ");printMode(mode);print(" on pin:");p_ul(pin);
	if (isASetableMode(mode)){
		bval = Packet->use.data[1];
		if (Packet->use.head.DataLegnth>6){
			wval.byte.SB = Packet->use.data[2];
			wval.byte.LB = Packet->use.data[3];
		}else{
			//println("Packet was 6 or less data bytes");
			wval.Val=0;
		}
		SetChanVal(pin,bval,(float)wval.Val);
		ret = TRUE;
		READY(Packet,zone,0);
	}else if ( (mode == IS_ANALOG_OUT)){
		wval.byte.SB=Packet->use.data[1];
		wval.byte.LB=Packet->use.data[2];
		switch (mode){
			default:
				return FALSE;
			}
		ret = TRUE;
	}else if ((mode == IS_UART_TX) || (mode == IS_UART_RX)){
		//Number of bytes in the stream to be sent
		BYTE i;
		bval = Packet->use.head.DataLegnth-5;
		for (i=0;i<bval;i++){
			WriteAVRUART1(Packet->use.data[i+1]);
		}
		return TRUE;
	}
	return ret;
}



BOOL SetChanVal(BYTE pin,INT32 bval, float time){
	BYTE mode = GetChannelMode(pin);
	//println("Setting channel pos\n\tchan: ");p_ul(pin);print(" \n\tto val: ");p_ul(bval);print("\n\tin time: ");p_fl(time);
	switch (mode){
	case IS_DI:
	case IS_DO:
		SetDIO(pin,bval);
		break;
	case IS_SERVO:
		SetServoPos(pin,bval,time);
		break;
	case IS_PWM:
		SetPWM(pin,bval);
		break;
	case IS_DC_MOTOR_VEL:
	case IS_DC_MOTOR_DIR:
		SetDCMotor(pin,bval);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}


void set8bit(BowlerPacket * Packet,BYTE val){
	Packet->use.data[1]=val;
}
void set16bit(BowlerPacket * Packet,UINT16 val){
	UINT16_UNION wval;
	wval.Val=val;
	Packet->use.data[1]=wval.byte.SB;
	Packet->use.data[2]=wval.byte.LB;
}
void set32bit(BowlerPacket * Packet,INT32 val){
	INT32_UNION lval;
	lval.Val=val;
	Packet->use.data[1]=lval.byte.FB;
	Packet->use.data[2]=lval.byte.TB;
	Packet->use.data[3]=lval.byte.SB;
	Packet->use.data[4]=lval.byte.LB;
}
INT32 get32bit(BowlerPacket * Packet){
	INT32_UNION lval;
	lval.byte.FB=Packet->use.data[1];
	lval.byte.TB=Packet->use.data[2];
	lval.byte.SB=Packet->use.data[3];
	lval.byte.LB=Packet->use.data[4];
	return lval.Val;
}
