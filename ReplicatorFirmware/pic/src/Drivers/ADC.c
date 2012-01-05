/*
 * ADC.c
 *
 *  Created on: Feb 12, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"
float getVolt(BYTE chan);

BOOL init = FALSE;
#define AVG_SIZE 20

typedef struct __attribute__((__packed__)) _ROLLINGAVG
{
	float rawAvg[AVG_SIZE];
	float avgSum;
	BYTE avgIndex;
	BYTE adcChan;
} ROLLINGAVG;

ROLLINGAVG adc[3];
float calc(ROLLINGAVG * avg){
	float v=getVolt(avg->adcChan);
	avg->avgSum+=v;
	avg->rawAvg[avg->avgIndex ++]=v;
	if (avg->avgIndex == AVG_SIZE)
		avg->avgIndex=0;
	avg->avgSum-=(float)avg->rawAvg[avg->avgIndex];
	return (avg->avgSum/AVG_SIZE);
}
void InitADC(void){
	if (init)
		return;
	BYTE i,j;

	init = TRUE;
	DDPCONbits.JTAGEN=0;
	AD1CHS = 0x0000;
	AD1PCFG = 0xFFFF;
	AD1CON1 = 0x0000;
	AD1CON2 = 0x0000;
	AD1CON3 = 0x0000;
	AD1CSSL = 0x0000;// Auto Sample only pins that can be ADC
    AD1CHS = 0x0000;
#define PARAM1 ADC_MODULE_ON | ADC_FORMAT_INTG
#define PARAM2 ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1| ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF
#define PARAM3 ADC_CONV_CLK_INTERNAL_RC |ADC_CONV_CLK_32Tcy |ADC_SAMPLE_TIME_31
#define PARAM4 ENABLE_AN12_ANA|ENABLE_AN13_ANA|ENABLE_AN14_ANA|ENABLE_AN15_ANA
#define PARAM5 0

	AD1CON1bits.ASAM = 0;// Enable automatic sampling by setting
	AD1CON1bits.SSRC = 0;
	AD1CON1bits.FORM = 0;			// Output in Integer Format
	AD1CON1bits.ADON = 1;			// Start the ADC module

	AD1CON2bits.VCFG = 0;
	AD1CON2bits.SMPI = 0;// Samples before an interupt
	AD1CON2bits.CSCNA = 0;// Sequentially scan MUXA by setting

	AD1CON3bits.SAMC = 0;// number of A/D clocks between the start of acquisition and the start of conversion
	AD1CON3bits.ADCS = 13;// A/D Conversion clock
	AD1CON3bits.ADRC = 1;// Use RC osscilator for conversion clock by setting

    mPORTBSetPinsAnalogIn(PARAM4);
    //Use sample channel A
	AD1CHSbits.CH0NA=1;
	EnableADC10();

	adc[0].adcChan=15;
	adc[1].adcChan=12;
	adc[2].adcChan=14;
	for(i=0;i<3;i++){
		adc[i].avgSum=0;
		adc[i].avgIndex=0;
		for(j=0;j<AVG_SIZE;j++){
			calc(&adc[i]);
		}
	}
	println("Initialized the ADC");
}
float lastHighTime=0;
float lastLowTime=0;

static BOOL lockOutRail = FALSE;
static BOOL externalLock=FALSE;
BOOL isLocked(void){
	return lockOutRail;
}
BOOL isActive(void){
	return externalLock;
}
void unlockServos(){
	externalLock=FALSE;
}
void lockServos(){
	externalLock=TRUE;
}
#define flux 200
RunEveryData lockOutTimeout;
BYTE GetRawVoltageCode(BYTE bank){
	BYTE back;

	float rv =GetRawVoltage();
	if(lockOutRail == FALSE){
		float current = getMs();
		float diffLow = (current-lastLowTime);
		float diffHigh = (current-lastHighTime);
		if((current>lastLowTime) && (current>lastHighTime)){
			if((lastHighTime != 0) &&  (lastLowTime != 0)){
				if((diffLow<flux) && (diffHigh<flux)){
					lockOutRail=TRUE;
					lockOutTimeout.MsTime=current;
					lockOutTimeout.setPoint=1000;
					UpstreamPushPowerChange();
				}
			}
		}
	}else{
		if(RunEvery(&lockOutTimeout)>0){
			lockOutRail = FALSE;
			UpstreamPushPowerChange();
		}
		return 0;
	}
	if(bank==0){
		rv = GetRail0Voltage();
	}else{
		rv = GetRail1Voltage();
	}
	if(rv>RawVoltageMin){
		lastHighTime = getMs();
		if(externalLock==TRUE)
			return 3;
		back=1;
	}else {
		lastLowTime = getMs();
		if(rv<4 && externalLock==FALSE){
			back=2;
		}else{
			back=0;
		}
	}
	return back;
}

float GetRawVoltage(void){
	return calc(&adc[2]);
}

float GetRail0Voltage(void){
	return calc(&adc[0]);
}

float GetRail1Voltage(void){
	return calc(&adc[1]);
}

float getVolt(BYTE chan){
	InitADC();
	AD1CHSbits.CH0SA = chan;
	AD1CON1bits.SAMP = 1;
	Delay10us(5);
	AD1CON1bits.SAMP = 0;
	while (AD1CON1bits.DONE == 0){
		// Wait for ADC to finish
		buttonCheck(2);
	}
	AD1CHS =0;
	WORD tmp = ADC1BUF0;
	float back = ((float)tmp)*0.017283951;
	//println("Voltage on chan:");
	//p_ul(chan);
	//print(" is ");
	//p_ul(tmp);
	//print(" is scaled to ");
	//p_fl(back);
	return back;
}
