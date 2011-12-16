/*
 * BowlerConfig.h
 *
 *  Created on: Jan 11, 2010
 *      Author: hephaestus
 */

#ifndef BOWLERCONFIG_H_
#define BOWLERCONFIG_H_

	#define USE_DYN_RPC

	#define ASSERTED				0
	#define NOT_ASSERTED			1
	#define OUTPUT 					0
	#define INPUT 					1

	#include "HardwareProfile.h"
	#include "Compiler.h"
    #include "GenericTypeDefs.h"
	#include "Delay.h"
	#include "Tick.h"
	#include "LED.h"
	#include "UART.h"
	#include "FlashStorage.h"

	#include "USB/usb_fifo.h"


	#define StartCritical()  INTDisableInterrupts();
	#define EndCritical()    INTEnableSystemMultiVectoredInt();INTEnableInterrupts();

	#define WriteUART_COM 			Write32UART1
	#define WriteUART_DEBUG 		Write32UART1

	#define USE_UART
	#define USE_USB

	WORD Get_HAL_Byte_Count();

#define Bowler_HAL_Init Pic32_Bowler_HAL_Init
void SetPICUARTFifo(BYTE_FIFO_STORAGE * s);
void SendPacketUSB(BYTE * packet,WORD size);
void Pic32_Bowler_HAL_Init(void);

#endif /* BOWLERCONFIG_H_ */
