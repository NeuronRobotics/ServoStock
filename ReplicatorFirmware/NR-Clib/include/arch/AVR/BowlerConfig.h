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
#ifndef BOWLERCONFIG_H_
#define BOWLERCONFIG_H_

	#include "reg_structs.h"
	#include <util/delay.h>
	#include <avr/io.h>
	#include <string.h>
	#include <avr/interrupt.h>

#if !defined(__AVR_ATmega324P__)
	#define USE_DYN_RPC
#endif

#define OUTPUT 					1
#define INPUT  					0
#define OFF						0
#define ON						1
#define ALLOUTPUT 				0xFF
#define ALLINPUT  				0x00
#define SDK_LED_ALLON 			0x00
#define SDK_LED_ALLOFF 			0xff
#define SDK_LED_ON 				0
#define SDK_LED_OFF 			1
#define UARTDELAY				5

#define Nop()					__asm__("nop\n\t")
#define nop()					Nop()

void WriteAVRUART0(BYTE val);
void WriteAVRUART1(BYTE val);

//#define WriteUART_COM 			WriteAVRUART0
//#define WriteUART_DEBUG 		WriteAVRUART1

#define StartCritical() cli()
#define EndCritical()   sei()

#define USE_UART
void AVR_Bowler_HAL_Init(void);
#define Bowler_HAL_Init() AVR_Bowler_HAL_Init()
#define SetColor(a,b,c)

#endif /* BOWLERCONFIG_H_ */
