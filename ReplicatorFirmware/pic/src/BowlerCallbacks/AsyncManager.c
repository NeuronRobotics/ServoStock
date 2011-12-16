/*
 * AsyncManager.c
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"

extern DATA_STRUCT DATA;
#define ADCINIT 0xFFFF
//#define ANALOG_DEAD_BAND 10
//#define ADCINIT 0xFFFF
//static LONG counterInput[4];
//static WORD ADClocal[]={ADCINIT,ADCINIT,ADCINIT,ADCINIT,ADCINIT,ADCINIT,ADCINIT,ADCINIT};
//static BYTE DIGlocal[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//WORD ADC_val[]={ADCINIT,ADCINIT,ADCINIT,ADCINIT,ADCINIT,ADCINIT,ADCINIT,ADCINIT};
//BYTE DIG_val[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//static RunEveryData asyncSched = {0,100};
//static RunEveryData asyncFast={0,5};

void runAsyncIO();
static BOOL isInit=FALSE;
static AdvancedAsyncData asyncData[NUM_PINS];

void printAsyncType(BYTE t){
	switch(t){
	case AUTOSAMP:
		print("AUTOSAMP");return;
	case NOTEQUAL:
		print("NOTEQUAL");return;
	case DEADBAND:
		print("DEADBAND");return;
	case THRESHHOLD:
		print("THRESHHOLD");return;
	default:
		print("UNKNOWN: "); p_ul(t);return;
	}
}
void configAdvancedAsyncNotEqual(BYTE pin,float time){
	asyncData[pin].time.MsTime=getMs();
	asyncData[pin].time.setPoint=time;
	asyncData[pin].type = NOTEQUAL;
}
void configAdvancedAsyncDeadBand(BYTE pin,float time,INT32 deadbandSize){
	asyncData[pin].time.MsTime=getMs();
	asyncData[pin].time.setPoint=time;
	asyncData[pin].type = DEADBAND;
	asyncData[pin].deadBand.val=deadbandSize;
}
void configAdvancedAsyncTreshhold(BYTE pin,float time,INT32 threshholdValue, BYTE edgeType){
	asyncData[pin].time.MsTime=getMs();
	asyncData[pin].time.setPoint=time;
	asyncData[pin].type = THRESHHOLD;
	asyncData[pin].threshhold.val=threshholdValue;
	asyncData[pin].threshhold.edge=edgeType;
}
void configAdvancedAsyncAutoSample(BYTE pin,float time){
	asyncData[pin].time.MsTime=getMs();
	asyncData[pin].time.setPoint=time;
	asyncData[pin].type = AUTOSAMP;
}

void configAdvancedAsync(BowlerPacket * Packet){
	INT32_UNION val;
	INT32_UNION time;
	BYTE pin = Packet->use.data[0];
	BYTE type = Packet->use.data[1];
	time.byte.FB= Packet->use.data[2];
	time.byte.TB= Packet->use.data[3];
	time.byte.SB= Packet->use.data[4];
	time.byte.LB= Packet->use.data[5];
	switch(type){
	case AUTOSAMP:
		configAdvancedAsyncAutoSample(pin,time.Val);
		break;
	case NOTEQUAL:
		configAdvancedAsyncNotEqual(pin,time.Val);
		break;
	case DEADBAND:
		val.byte.FB= Packet->use.data[6];
		val.byte.TB= Packet->use.data[7];
		val.byte.SB= Packet->use.data[8];
		val.byte.LB= Packet->use.data[9];
		configAdvancedAsyncDeadBand(pin,time.Val,val.Val);
		break;
	case THRESHHOLD:
		val.byte.FB= Packet->use.data[6];
		val.byte.TB= Packet->use.data[7];
		val.byte.SB= Packet->use.data[8];
		val.byte.LB= Packet->use.data[9];
		configAdvancedAsyncTreshhold(pin,time.Val,val.Val,Packet->use.data[10]);
		break;
	default:
		ERR(Packet,45,0);
	}
	setAsyncLocal(pin,TRUE);
	READY(Packet,45,0);
}


void startAdvancedAsyncDefault(BYTE pin){
	//println("Starting advanced async on channel: ");p_ul(pin);
	asyncData[pin].currentVal=1;
	asyncData[pin].previousVal=1;
	asyncData[pin].time.MsTime=getMs();
	asyncData[pin].time.setPoint=100;
	asyncData[pin].type = NOTEQUAL;
	switch(GetChannelMode(pin)){
	case IS_DI:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
		asyncData[pin].time.setPoint=5;
		break;
	case IS_ANALOG_IN:
		asyncData[pin].currentVal=ADCINIT;
		asyncData[pin].previousVal=ADCINIT;
		asyncData[pin].type = DEADBAND;
		asyncData[pin].deadBand.val=10;
//		asyncData[pin].type = THRESHHOLD;
//		asyncData[pin].threshhold.val=512;
//		asyncData[pin].threshhold.edge=ASYN_RISING;
		break;
	}
	//println("Async Type set to: ");printAsyncType(asyncData[pin].type);
}

void initAdvancedAsync(){
	if(isInit == TRUE)
		return;
	isInit=TRUE;
	SyncModes();
	println("Initializing Advanced Async");
	int i;
	for (i=0;i<NUM_PINS;i++){
		startAdvancedAsyncDefault(i);
	}
}


BOOL isAnalog(BowlerPacket * Packet){
	if(		(Packet->use.head.RPC==GCHV) &&
			(GetChannelMode(Packet->use.data[0])==IS_ANALOG_IN)
			){
		return TRUE;
	}
	return FALSE;
}

void dealWithAsyncPacket(BowlerPacket * Packet){
	if(Packet->use.head.RPC==_PWR){
		SetColor(1,0,0);
		return;
	}
	ProcessAsyncData(Packet);
}

int GetDigitalValFromAsync(BYTE pin){
	initAdvancedAsync();
	if(GetChannelMode(pin)==IS_DI || GetChannelMode(pin)==IS_COUNTER_INPUT_HOME || GetChannelMode(pin)==IS_COUNTER_OUTPUT_HOME){
		return asyncData[pin].currentVal;
	}
	return 1;
}

void SetValFromAsync(int pin, int value){
	asyncData[pin].currentVal=value;
}

int GetAnalogValFromAsync(BYTE pin){
	initAdvancedAsync();
	if(pin<8||pin>15){
		println("###Invalid ADC pin! ");
		p_ul(pin);
		return 0;
	}
	if(GetChannelMode(pin)==IS_ANALOG_IN){
		if(asyncData[pin].currentVal==ADCINIT)
			SetValFromAsync( pin, GetADC(pin));
		return asyncData[pin].currentVal;
	}
	println("Pin not in analog mode: ");
	printMode(GetChannelMode(pin));
	return 0;
}

float lastSyncSession=0;



void SyncSessionTime(float time){
	lastSyncSession = time;
}

void RunAsync(void){
	PushCoProcAsync();
	runAsyncIO();
}

void ProcessAsyncData(BowlerPacket * Packet){
	//println("**Got Async Packet**");
	//printPacket(Packet);
	if (Packet->use.head.RPC==GCHV){
		BYTE pin = Packet->use.data[0];
		BYTE mode = GetChannelMode(pin);
		if(mode == IS_ANALOG_IN ){
			UINT16_UNION ana;
			ana.byte.SB = Packet->use.data[1];
			ana.byte.LB = Packet->use.data[2];
			//ADC_val[pin-8]=ana.Val;
			if(ana.Val>=0 && ana.Val<1024)
				asyncData[pin].currentVal=ana.Val;
			//println("***Setting analog value: ");p_ul(pin);print(", ");p_ul(ana.Val);
		}
		else if((mode == IS_DI) || (mode == IS_COUNTER_INPUT_HOME)|| (mode == IS_COUNTER_OUTPUT_HOME)){
			//DIG_val[pin]=Packet->use.data[1];
			asyncData[pin].currentVal=Packet->use.data[1];
			//println("***Setting digital value: ");p_ul(pin);print(", ");p_ul(Packet->use.data[1]);//printStream(DIG_val,NUM_PINS);
		}else {
			if(IsAsync(pin)){
				println("Sending async packet, not digital or analog");
				PutBowlerPacket(Packet);
			}
		}
	}else if (Packet->use.head.RPC==AASN){
		int i;
		for(i=0;i<8;i++){
			BYTE pin = i+8;
			BYTE mode = GetChannelMode(pin);
			if(mode == IS_ANALOG_IN ){
				UINT16_UNION ana;
				ana.byte.SB = Packet->use.data[i*2];
				ana.byte.LB = Packet->use.data[(i*2)+1];
				//ADC_val[pin-8]=ana.Val
				if(ana.Val>=0 && ana.Val<1024);
					asyncData[pin].currentVal=ana.Val;

			}
			//println("***Setting All analog value: ");
		}
	}else if (Packet->use.head.RPC==DASN){
		int i;
		for(i=0;i<NUM_PINS;i++){
			BYTE mode = GetChannelMode(i);
			if((mode == IS_DI) || (mode == IS_COUNTER_INPUT_HOME)|| (mode == IS_COUNTER_OUTPUT_HOME)){
				asyncData[i].currentVal=Packet->use.data[i];
			}

		}
		//println("***Setting All Digital value: ");printPacket(Packet);
	}else{
		enableDebug();
		println("***Async packet not GCHV***");
		printPacket(Packet);
	}
	//println("Async");
}

BOOL pushAsyncReady( BYTE pin){
	initAdvancedAsync();
	INT32 last;
	INT32 aval;
	INT32 db;
	int i=pin;
	if(GetChannelMode(i)==IS_COUNTER_INPUT_INT || GetChannelMode(i)==IS_COUNTER_OUTPUT_INT){
		asyncData[i].currentVal = GetCounterByChannel(i);
	}
	if(GetChannelMode(i)==IS_ANALOG_IN){
		asyncData[i].currentVal = GetAnalogValFromAsync(i);
	}
	if(RunEvery(&asyncData[pin].time) !=0){
		//println("Time to do something");
		switch(asyncData[pin].type&0x0F){
		case AUTOSAMP:
			//println("Auto samp");
			asyncData[pin].previousVal = asyncData[pin].currentVal;
			return TRUE;
		case NOTEQUAL:
			//
			if(asyncData[pin].currentVal != asyncData[pin].previousVal){
				//println("not equ");
				asyncData[pin].previousVal = asyncData[pin].currentVal;
				return TRUE;
			}
			break;
		case DEADBAND:
			aval = asyncData[pin].currentVal;
			last = asyncData[pin].previousVal;
			db = asyncData[pin].deadBand.val;
			if (	( 	( last >(aval+db)) ||
						( last <(aval-db)) ) &&
					(aval >=db)
					){
				//println("deadband");
				asyncData[pin].previousVal=aval;
				return TRUE;
			}
			break;
		case THRESHHOLD:
			//println("treshhold");
			aval = asyncData[pin].currentVal;
			last = asyncData[pin].previousVal;
			db = asyncData[pin].threshhold.val;
			asyncData[pin].previousVal = asyncData[pin].currentVal;
			if(asyncData[pin].threshhold.edge == ASYN_RISING || asyncData[pin].threshhold.edge == ASYN_BOTH){
				if(last<= db && aval>db){

					return TRUE;
				}
			}
			if(asyncData[pin].threshhold.edge == ASYN_FALLING|| asyncData[pin].threshhold.edge == ASYN_BOTH){
				if(last> db && aval<=db){
					return TRUE;
				}
			}
			break;
		default:
			print("\nNo type defined!! chan: ");p_ul(pin);print(" mode: ");printMode(GetChannelMode(pin));print(" type: ");printAsyncType(asyncData[pin].type);
			startAdvancedAsyncDefault(pin);
		}
	}else{

	}
	return FALSE;
}
//#define FASTIO
#if defined(FASTIO)
	int currentState [NUM_PINS];
#endif
void runAsyncIO(){
	initAdvancedAsync();
	int i;
#if defined(FASTIO)
	BOOL update=FALSE;
#endif
	for(i=0;i<NUM_PINS;i++){
		if(		IsAsync(i)==TRUE &&
				pushAsyncReady(i)==TRUE &&
				GetPIDGroup(i) == NOT_USED_IN_PID){
			switch(GetChannelMode(i)){
			case IS_DI:
			case IS_COUNTER_INPUT_HOME:
			case IS_COUNTER_OUTPUT_HOME:
				//println("Pushing digital chan: ");p_ul(i);print(" value:");p_ul(asyncData[i].currentVal);
#if defined(FASTIO)
				currentState [i] = GetDigitalValFromAsync(i);
				update=TRUE;
				break;
#else
				PushDIval(i,GetDigitalValFromAsync(i));
				break;
#endif

			case IS_ANALOG_IN:
				//println("Pushing analog chan: ");p_ul(i);print(" value:");p_ul(asyncData[i].currentVal);
#if defined(FASTIO)
				currentState [i] = GetAnalogValFromAsync(i);
				update=TRUE;
				break;
#else
				PushADCval(i,GetAnalogValFromAsync(i));
				break;
#endif

			case IS_COUNTER_OUTPUT_INT:
			case IS_COUNTER_INPUT_INT:
				//println("Pushing counter chan: ");p_ul(i);print(" value:");p_sl(asyncData[i].currentVal);
#if defined(FASTIO)
				currentState [i] = GetCounterByChannel(i);
				update=TRUE;
				break;
#else
				PushCounterChange(i,GetCounterByChannel(i));
				break;
#endif

			}
		}
	}
#if defined(FASTIO)
	if(update){
		//println("Pushing async");
		PushAllAsync(currentState);
	}
#endif
}

void initCounterAsync(BYTE chan,INT32 val){
	println("Setting up Counter Async chan: ");
	p_ul(chan);
	print(" to val: ");
	p_ul(val);
	asyncData[getCounterIntChannnel(chan)].currentVal=val;
	asyncData[getCounterIntChannnel(chan)].previousVal=val;
}
