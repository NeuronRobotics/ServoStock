/*
 *
 * Copyright 2009 Neuron Robotics, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "UserApp.h"
extern DATA_STRUCT DATA;


void setDig(BYTE pin, BYTE val);
void setAnv(BYTE pin, UINT16 val);
typedef struct __attribute__((__packed__)) _DIG_VALS{
	unsigned b0;
	unsigned b1;
	unsigned b2;
	unsigned b3;
	unsigned b4;
	unsigned b5;
	unsigned b6;
	unsigned b7;
	unsigned b8;
	unsigned b9 ;
	unsigned b10;
	unsigned b11;
	unsigned b12;
	unsigned b13;
	unsigned b14;
	unsigned b15;
	unsigned b16;
	unsigned b17;
	unsigned b18;
	unsigned b19;
	unsigned b20;
	unsigned b21;
	unsigned b22;
	unsigned b23;
//	unsigned 	 :8;
//	BYTE b0;
//	BYTE b1;
//	BYTE b2;
//	BYTE b3;
//	BYTE b4;
//	BYTE b5;
//	BYTE b6;
//	BYTE b7;
//	BYTE b8;
//	BYTE b9 ;
//	BYTE b10;
//	BYTE b11;
//	BYTE b12;
//	BYTE b13;
//	BYTE b14;
//	BYTE b15;
//	BYTE b16;
//	BYTE b17;
//	BYTE b18;
//	BYTE b19;
//	BYTE b20;
//	BYTE b21;
//	BYTE b22;
//	BYTE b23;
} DIG_VALS;
typedef struct __attribute__((__packed__)) _ADC_VALS{
	unsigned b0 :11;
	unsigned b1 :11;
	unsigned b2 :11;
	unsigned b3 :11;
	unsigned b4 :11;
	unsigned b5 :11;
	unsigned b6 :11;
	unsigned b7 :11;

//	UINT16 b0 ;
//	UINT16 b1 ;
//	UINT16 b2 ;
//	UINT16 b3 ;
//	UINT16 b4 ;
//	UINT16 b5 ;
//	UINT16 b6 ;
//	UINT16 b7 ;

} ADC_VALS;

static DIG_VALS dig;
static ADC_VALS adv;

//BYTE DI_PUSH_val[24];
//UINT16 ADC_val[8];
#define ANALOG_DEAD_BAND 10
BOOL ack=FALSE;
RunEveryData asyncSched = {0,10.0};
#define blockTime 25
RunEveryData block0 = {0,blockTime};
RunEveryData block1 = {(blockTime/3),blockTime};
RunEveryData block2 = {((blockTime/3)*2),blockTime};

//static BYTE asyncIndex = 0;

void initPinState(BYTE i){
	BYTE mode =GetChannelMode(i);
	if ((mode == IS_ANALOG_IN) ){
		setAnv(i,GetADC(i));
	}
	if(((mode == IS_DI) )  || ((mode == IS_COUNTER_INPUT_HOME)||(mode == IS_COUNTER_OUTPUT_HOME))){
		setDig(i,GetDIO(i)?1:0);
	}
}

static INT16 aval,last;
BOOL checkAnalog(){
	BOOL update=FALSE;
	int i=0;
	for(i=8;i<16;i++){
		if ((GetChannelMode(i) == IS_ANALOG_IN) ){
			aval = GetADC(i);
			last = getAnv(i);
			if (( last >(aval+ANALOG_DEAD_BAND))||(	(last < (aval-ANALOG_DEAD_BAND) && (aval >=ANALOG_DEAD_BAND)	))){
				ack=TRUE;
				setAnv(i,aval);
				//PushADCval(i,aval);
				update= TRUE;
			}

		}
	}
	if(update)
		PushAllAdcVal();

	return update;
}
BOOL checkDigital(){
	int i;
	BOOL update=FALSE;
	for(i=0;i<NUM_PINS;i++){
		BYTE mode = GetChannelMode(i);
		BOOL run = (((mode == IS_DI) )  || ((mode == IS_COUNTER_INPUT_HOME)||(mode == IS_COUNTER_OUTPUT_HOME)));
		if (run){
			aval=GetDIO(i)?1:0;
			if (aval!=getDig(i)){
				ack=TRUE;
				setDig(i,aval);
				//PushDIval(i,aval);
				//return;
				update= TRUE;
			}

		}
	}
	if(update)
		PushAllDiVal();

	return update;
}

void resetBlocks(){
	block0.setPoint = blockTime;
	block0.MsTime=getMs();

	block1.setPoint = blockTime;
	block1.MsTime=block0.MsTime+(blockTime/3);

	block2.setPoint = blockTime;
	block2.MsTime=block1.MsTime+(blockTime/3);
}

void UserRun(void){
#if defined(DEBUG)
	if(GetChannelMode(16)!=IS_UART_TX){
		setMode(16,IS_UART_TX);
		ConfigureUART(115200);
	}
#endif
#if defined(WPIRBE)
	SPISlaveServer();
#endif
#if defined(USE_AS_LIBRARY)
	RunUserCode();
#endif
//	int i;
//	for(i=0;i<NUM_PINS;i++){
//		checkAnalog(i);
//		checkDigital(i);
////		asyncIndex++;
////		if(asyncIndex== NUM_PINS)
////			asyncIndex=0;
//	}
	if (Get_UART_Byte_CountPassThrough()>0){
		PushSerial();
	}

	if(!(block0.MsTime > 0)){
		resetBlocks();
	}
	if(!(block1.MsTime > 0)){
		resetBlocks();
	}
	if(!(block2.MsTime > 0)){
		resetBlocks();
	}
//	if(!(asyncSched.MsTime > 0)){
//		asyncSched.setPoint = 5;
//		asyncSched.MsTime=now;
//		//println("Resetting async");
//	}

	if (RunEvery(&block0)>0){
		//println("Step 0");
		//
		RunServo(0);

		//return;
	}
	if (RunEvery(&block1)>0){
		//println("Step 1");
		RunServo(1);
		//return;
	}
	if (RunEvery(&block2)>0){
		//println("Step 2");
		RunServo(2);
		resetBlocks();
		//return;
	}
}

void AsynAck(void){
	ack=TRUE;
}

BOOL getDig(BYTE pin){
	switch(pin){
	case 0:
		return dig.b0?1:0;
	case 1:
		return dig.b1?1:0;
	case 2:
		return dig.b2?1:0;
	case 3:
		return dig.b3?1:0;
	case 4:
		return dig.b4?1:0;
	case 5:
		return dig.b5?1:0;
	case 6:
		return dig.b6?1:0;
	case 7:
		return dig.b7?1:0;
	case 8:
		return dig.b8?1:0;
	case 9:
		return dig.b9?1:0;
	case 10:
		return dig.b10?1:0;
	case 11:
		return dig.b11?1:0;
	case 12:
		return dig.b12?1:0;
	case 13:
		return dig.b13?1:0;
	case 14:
		return dig.b14?1:0;
	case 15:
		return dig.b15?1:0;
	case 16:
		return dig.b16?1:0;
	case 17:
		return dig.b17?1:0;
	case 18:
		return dig.b18?1:0;
	case 19:
		return dig.b19?1:0;
	case 20:
		return dig.b20?1:0;
	case 21:
		return dig.b21?1:0;
	case 22:
		return dig.b22?1:0;
	case 23:
		return dig.b23?1:0;
	default:
		return 0;
	}
}

void setDig(BYTE pin, BYTE val){
	switch(pin){
	case 0:
		dig.b0=(val>0)?1:0;
	case 1:
		dig.b1=(val>0)?1:0;
	case 2:
		dig.b2=(val>0)?1:0;
	case 3:
		dig.b3=(val>0)?1:0;
	case 4:
		dig.b4=(val>0)?1:0;
	case 5:
		dig.b5=(val>0)?1:0;
	case 6:
		dig.b6=(val>0)?1:0;
	case 7:
		dig.b7=(val>0)?1:0;
	case 8:
		dig.b8=(val>0)?1:0;
	case 9:
		dig.b9=(val>0)?1:0;
	case 10:
		dig.b10=(val>0)?1:0;
	case 11:
		dig.b11=(val>0)?1:0;
	case 12:
		dig.b12=(val>0)?1:0;
	case 13:
		dig.b13=(val>0)?1:0;
	case 14:
		dig.b14=(val>0)?1:0;
	case 15:
		dig.b15=(val>0)?1:0;
	case 16:
		dig.b16=(val>0)?1:0;
	case 17:
		dig.b17=(val>0)?1:0;
	case 18:
		dig.b18=(val>0)?1:0;
	case 19:
		dig.b19=(val>0)?1:0;
	case 20:
		dig.b20=(val>0)?1:0;
	case 21:
		dig.b21=(val>0)?1:0;
	case 22:
		dig.b22=(val>0)?1:0;
	case 23:
		dig.b23=(val>0)?1:0;
	}
}

UINT16 getAnv(BYTE pin){
	switch(pin){
	case 8:
		return adv.b0;
	case 9:
		return adv.b1;
	case 10:
		return adv.b2;
	case 11:
		return adv.b3;
	case 12:
		return adv.b4;
	case 13:
		return adv.b5;
	case 14:
		return adv.b6;
	case 15:
		return adv.b7;
	default:
		return 0;
	}
}
void setAnv(BYTE pin,UINT16 val){
	switch(pin){
	case 8:
		adv.b0=val;
	case 9:
		adv.b1=val;
	case 10:
		adv.b2=val;
	case 11:
		adv.b3=val;
	case 12:
		adv.b4=val;
	case 13:
		adv.b5=val;
	case 14:
		adv.b6=val;
	case 15:
		adv.b7=val;
	}
}
