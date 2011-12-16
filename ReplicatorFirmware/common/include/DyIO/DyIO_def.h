/**
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
#include "Bowler/Bowler.h"
#include "Debug_DyIO.h"
#include "ChannelMode.h"
#include "ChannelValues.h"
#include "Bowler/AbstractPID.h"
#ifndef DYIO_DEF_H_
#define DYIO_DEF_H_

#define NUM_PINS   			24

#define MAJOR_REV			3
#define MINOR_REV			7
#define FIRMWARE_VERSION	19

#define NO_CHANGE	 	 		0x00
#define HIGH_IMPEDANCE 	 		0x01
#define IS_DI	 		 		0x02
#define IS_DO		 			0x03
#define IS_ANALOG_IN 			0x04
#define IS_ANALOG_OUT			0x05
#define IS_PWM	 				0x06
#define IS_SERVO 				0x07
#define IS_UART_TX		 		0x08
#define IS_UART_RX	 			0x09
#define IS_SPI_MOSI				0x0A
#define IS_SPI_MISO				0x0B
#define IS_SPI_SCK	 			0x0C
//#define IS_SPI_SS	 			0x0D
#define IS_COUNTER_INPUT_INT	0x0E
#define IS_COUNTER_INPUT_DIR	0x0F
#define IS_COUNTER_INPUT_HOME	0x10
#define IS_COUNTER_OUTPUT_INT	0x11
#define IS_COUNTER_OUTPUT_DIR	0x12
#define IS_COUNTER_OUTPUT_HOME	0x13
#define IS_DC_MOTOR_VEL			0x14
#define IS_DC_MOTOR_DIR			0x15
#define IS_PPM_IN				0x16

//bcs.io.setmode
#define SCHM				0x6D686373// Set channel mode
#define SACM				0x6D636173// Set all channel modes

//bcs.io
#define GCHM				0x6D686367// Get channel mode
#define GACM				0x6D636167// Get all channel mode
#define SCHV				0x76686373// Set channel value
#define SACV				0x76636173// Set all channel values
#define GCHV				0x76686367// Get channel value
//#define GACV				0x76636167// Get all channel values
#define CCHN				0x6E686363// Configure channel
#define ASYN				0x6e797361 // 'asyn'  Set/Get asynchronous mode

//neuronrobotics.dyio
#define _REV				0x7665725f // '_rev'  Get the revision number
#define INFO				0x6f666e69 // 'info'  Get and set the name string
#define _PWR				0x7277705f // '_pwr'  Request the power state
//private
#define EEPD				0x64706565// Interface with the EEPROM
#define DASN			    0x6e736164 // 'dasn'  Get 8 bit Async data
#define AASN				0x6e736161 // 'aasn'  Get 16 bit Async data
#define SAVE				0x65766173 // 'save'  Get the save values for servos
#define _MAC				0x63616D5F// Provision MAC address
#define POVR				0x72766f70 // 'povr'  Power override packet

//bcs.pid.dypid
#define DPID				0x64697064 // 'dpid'  Dynamic PID

#define FLAG_BLOCK 0
#define FLAG_OK    1


typedef union __attribute__((__packed__)) _FUNCTION_MAP
	{
		struct{
			unsigned HAS_ANALOG_IN		:1;
			unsigned HAS_ANALOG_PUSHED	:1;
			unsigned HAS_PWM			:1;
			unsigned HAS_UART			:1;
			unsigned HAS_SPI			:1;
			unsigned HAS_COUNTER_INPUT	:1;
			unsigned HAS_COUNTER_OUTPUT	:1;
			unsigned HAS_DC_MOTOR		:1;
		};
		BYTE b;
	} FUNCTION_MAP;
	typedef struct __attribute__((__packed__)) _PIN_MAP
	{
		BYTE ServoPos;
#if !defined(__AVR_ATmega324P__)
		BYTE State;
#endif
	} PIN_MAP;

	typedef struct __attribute__((__packed__)) _STORAGE
	{
		char					LockCode[5];
		char 					Name[17];
	} STORAGE;


	typedef struct __attribute__((__packed__)) _DATA
	{
		//STORAGE self;
		PIN_MAP PIN[NUM_PINS];
		FUNCTION_MAP FUNCTION[NUM_PINS];
	} DATA_STRUCT;


BOOL ConfigChannel(BowlerPacket * Packet);
void ClearPinState(BYTE pin);
void InitPins(void);
void InitPinFunction(void);
void runDyIOMain(void);

#endif /* DYIO_DEF_H_ */
