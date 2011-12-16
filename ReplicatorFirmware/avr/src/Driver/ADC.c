/*
 * ADC.c
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

extern DATA_STRUCT DATA;

BYTE InitADC(BYTE pin){
	if (!DATA.FUNCTION[pin].HAS_ANALOG_IN ){
		return FALSE;
	}

	ADMUXbits._REFS = 0;
	ADMUXbits._ADLAR = 0;

	ADCSRAbits._ADEN = 1;
	ADCSRAbits._ADIE = 0;
	ADCSRAbits._ADPS = 7;
    ADCSRB = 0x00;

	switch (pin){
	case 8:
		DIDR0bits._ADC0D=1;
		break;
	case 9:
		DIDR0bits._ADC1D=1;
		break;
	case 10:
		DIDR0bits._ADC2D=1;
		break;
	case 11:
		DIDR0bits._ADC3D=1;
		break;
	case 12:
		DIDR0bits._ADC4D=1;
		break;
	case 13:
		DIDR0bits._ADC5D=1;
		break;
	case 14:
		DIDR0bits._ADC6D=1;
		break;
	case 15:
		DIDR0bits._ADC7D=1;
		break;
	}

	return TRUE;
}
void ClearADC(BYTE pin){
	if (!DATA.FUNCTION[pin].HAS_ANALOG_IN){
		return;
	}
	switch (pin){
	case 8:
		DIDR0bits._ADC0D=0;
		break;
	case 9:
		DIDR0bits._ADC1D=0;
		break;
	case 10:
		DIDR0bits._ADC2D=0;
		break;
	case 11:
		DIDR0bits._ADC3D=0;
		break;
	case 12:
		DIDR0bits._ADC4D=0;
		break;
	case 13:
		DIDR0bits._ADC5D=0;
		break;
	case 14:
		DIDR0bits._ADC6D=0;
		break;
	case 15:
		DIDR0bits._ADC7D=0;
		break;
	}
	////printfDEBUG("Clearing ADC on pin:");
	////printfDEBUG_UL(pin);
}
UINT16 GetADC(BYTE pin){
	if(GetChannelMode(pin) != IS_ANALOG_IN)
		return 0;
	//UINT16_UNION adc;
	pin -=8;
	if (pin > 7){
		////printfDEBUG("Bad ADC pin:");
		////printfDEBUG_UL(pin);
		return 0;
	}

	////printfDEBUG("Getting ADC on pin:");
	////printfDEBUG_UL(pin);

	ADMUXbits._MUX = pin;
	ADCSRAbits._ADSC=1;
	while (	ADCSRAbits._ADSC==1);
	//adc.byte.LB =ADCL;
	//adc.byte.SB =ADCH;

	////printfDEBUG("ADC value is:");
	////printfDEBUG_UL(adc.Val);

	return ADC;
}
