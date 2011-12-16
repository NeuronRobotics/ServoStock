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

#define HIGHSPEED

extern DATA_STRUCT DATA;

void ClearPWM(BYTE channel){
	////printfDEBUG("Clearing PWM from pin:");
	////printfDEBUG_UL(channel);
	// Sets the compare channel to normal operation
	switch (channel){
	case 6:
		TCCR0Abits._COMA =0x00;
		break;
	case 7:
		TCCR0Abits._COMB =0x00;
		break;
	case 4:
		TCCR2Abits._COMA =0x00;
		break;
	case 5:
		TCCR2Abits._COMB =0x00;
		break;
	}
}

void enable(BYTE channel){
	if(   !(  GetChannelMode(channel) == IS_PWM
				||GetChannelMode(channel) == IS_DC_MOTOR_DIR
				||GetChannelMode(channel) == IS_DC_MOTOR_VEL) ){
			return;
		}
	switch (channel){
	case 6:
		DDRBbits._P3   = OUTPUT;// OC0A
		TCCR0Abits._WGM =0x03;// Fast WPM, 0xff top, 0x00 bottom
#if !defined(HIGHSPEED)
		TCCR0Bbits._CS = 5;// Clock select 1-5 are valid values
#else
		TCCR0Bbits._CS = 1;// Clock select 1-5 are valid values
#endif
		TCCR0Abits._COMA =0x02;//Fast PWM non inverting mode
		break;
	case 7:
		DDRBbits._P4   = OUTPUT;// OC0B
		TCCR0Abits._WGM =0x03;// Fast WPM, 0xff top, 0x00 bottom
#if !defined(HIGHSPEED)
		TCCR0Bbits._CS = 5;// Clock select 1-5 are valid values
#else
		TCCR0Bbits._CS = 1;// Clock select 1-5 are valid values
#endif
		TCCR0Abits._COMB =0x02;//Fast PWM non inverting mod
		break;
	// PWM on timer 2 have a few small differences
	case 4:
		DDRDbits._P7   = OUTPUT;// OC2A
		TCCR2Abits._WGM =0x03;// Fast WPM, 0xff top, 0x00 bottom
#if !defined(HIGHSPEED)
		TCCR2Bbits._CS = 7;// Clock select 1-7 are valid values
#else
		TCCR2Bbits._CS = 1;// Clock select 1-7 are valid values
#endif
		TCCR2Abits._COMA =0x02;//Fast PWM non inverting mode
		break;
	case 5:
		DDRDbits._P6   = OUTPUT;// OC2B
		TCCR2Abits._WGM =0x03;// Fast WPM, 0xff top, 0x00 bottom
#if !defined(HIGHSPEED)
		TCCR2Bbits._CS = 7;// Clock select 1-7 are valid values
#else
		TCCR2Bbits._CS = 1;// Clock select 1-7 are valid values
#endif
		TCCR2Abits._COMB =0x02;//Fast PWM non inverting mode
		break;
	}
}

BYTE InitPWM(BYTE channel){
	if (DATA.FUNCTION[channel].HAS_PWM == FALSE){
		return FALSE;
	}
	configPinMode(channel,IS_PWM,OUTPUT,OFF);
	//printfDEBUG("Initializing PWM from pin:");
	//printfDEBUG_UL(channel);
	//ClearPinState(channel);
	//DATA.PIN[channel].State=IS_PWM;
	enable(channel);
	SetPWM(channel,EEReadValue(channel));
	return TRUE;
}

void SetPWM(BYTE channel,BYTE val){
	if(   !(  GetChannelMode(channel) == IS_PWM
			||GetChannelMode(channel) == IS_DC_MOTOR_DIR
			||GetChannelMode(channel) == IS_DC_MOTOR_VEL) ){
		return;
	}
	enable(channel);
	switch (channel){
	case 6:
		OCR0A =val;
		break;
	case 7:
		OCR0B =val;
		break;
	case 4:
		OCR2A =val;
		break;
	case 5:
		OCR2B =val;
		break;
	}
}

BYTE GetPWM(BYTE pin){
	if (GetChannelMode(pin) != IS_PWM)
		return 0;
	return EEReadValue(pin);
}
