/*********************************************************************
 *
 *                  Tick Manager for PIC18
 *
 *********************************************************************
 * FileName:        Tick.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.00 or higher
 *					Microchip C30 v3.01 or higher
 *					Microchip C18 v3.13 or higher
 *					HI-TECH PICC-18 STD 9.50PL3 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2008 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c and
 *      ENC28J60.h ported to a non-Microchip device used in
 *      conjunction with a Microchip ethernet controller for the
 *      sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date    Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Nilesh Rajbharti     6/28/01 Original        (Rev 1.0)
 * Nilesh Rajbharti     2/9/02  Cleanup
 * Nilesh Rajbharti     5/22/02 Rev 2.0 (See version.log for detail)
 ********************************************************************/
#ifndef __TICK_H
#define __TICK_H

#include "GenericTypeDefs.h"
#include "Compiler.h"
#if !defined(_SYSTEM_SERVICES_H_)
// All TICKS are stored as 32-bit unsigned integers.
//typedef unsigned int TICK;
#endif
// This value is used by TCP to implement timeout actions.
// For this definition, the Timer must be initialized to use
// a 1:256 prescalar in Tick.c.  If using a 32kHz watch crystal
// as the time base, modify the Tick.c file to use no prescalar.
#if !defined(TICKS_PER_SECOND)
	#define TICKS_PER_SECOND		((GetPeripheralClock()+128ull)/256ull)	// Internal core clock drives timer
#endif
//#define TICKS_PER_SECOND		(32768ul)								// 32kHz crystal drives timer with no scalar

// Represents one second in Ticks
#define TICK_SECOND				((QWORD)TICKS_PER_SECOND)
// Represents one minute in Ticks
#define TICK_MINUTE				((QWORD)TICKS_PER_SECOND)*60ull)
// Represents one hour in Ticks
#define TICK_HOUR				((QWORD)TICKS_PER_SECOND*3600ull)
#if !defined(_SYSTEM_SERVICES_H_)
	// Deprecated.  Do not use this function.
	#define TickGetDiff(a, b)       ((a)-(b))
#endif
void TickInit(void);
DWORD TickGet(void);
DWORD TickGetUpper();
DWORD TickGetLower();

float MyTickConvertToMilliseconds(float dwTickValue);
float TickGetMS(void);

#endif
