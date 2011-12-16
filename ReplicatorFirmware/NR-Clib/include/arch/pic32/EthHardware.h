/*********************************************************************
 *
 *	Hardware specific definitions
 *
 *********************************************************************
 * FileName:        HardwareProfile.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.10 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.34 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2010 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
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
 * Author               Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Howard Schlunder		10/03/06	Original, copied from Compiler.h
 * Ken Hesky            01/xx/10    Added MRF24WB0M-specific features
 ********************************************************************/
#ifndef __HARDWARE_PROFILE_H

#define PIC32_ENET_SK_DM320004		// PIC32MX795F512L Ethernet Starter Kit board with embedded Ethernet controller


// PIC32 Ethernet Starter Kit (04-02146) with PIC32MX795F512L processor and National DP83848 10/100 PHY
	// External SMSC PHY configuration
	#define	PHY_RMII				// external PHY runs in RMII mode
	#define	PHY_CONFIG_ALTERNATE	// alternate configuration used
	#define	PHY_ADDRESS			0x1	// the address of the National DP83848 PHY

    // Hardware mappings

	#define RED_LED_TRIS		LED0_TRIS	//
	#define RED_LED_IO			LED0_IO

	#define GREEN_LED_TRIS		LED1_TRIS	//
	#define GREEN_LED_IO		LED1_IO

	#define BLUE_LED_TRIS		LED2_TRIS	//
	#define BLUE_LED_IO			LED2_IO
	#define startLED()			mPORTDSetPinsDigitalOut(BIT_1|BIT_2|BIT_0)
	#define SET_RED(a)			(a==0?mPORTASetBits(BIT_0):mPORTAClearBits(BIT_0))
	#define SET_GREEN(a)		(a==0?mPORTASetBits(BIT_2):mPORTAClearBits(BIT_2))
	#define SET_BLUE(a)			(a==0?mPORTASetBits(BIT_1):mPORTAClearBits(BIT_1))

    #define LED0_TRIS			(TRISDbits.TRISD0)	// Ref LED1
	#define LED0_IO				(LATDbits.LATD0)
	#define LED1_TRIS			(TRISDbits.TRISD1)	// Ref LED2
	#define LED1_IO				(LATDbits.LATD1)
	#define LED2_TRIS			(TRISDbits.TRISD2)	// Ref LED3
	#define LED2_IO				(LATDbits.LATD2)

	#define LED3_TRIS			(LED2_TRIS)			// No such LED
	#define LED3_IO				(LATDbits.LATD6)
	#define LED4_TRIS			(LED2_TRIS)			// No such LED
	#define LED4_IO				(LATDbits.LATD6)
	#define LED5_TRIS			(LED2_TRIS)			// No such LED
	#define LED5_IO				(LATDbits.LATD6)
	#define LED6_TRIS			(LED2_TRIS)			// No such LED
	#define LED6_IO				(LATDbits.LATD6)
	#define LED7_TRIS			(LED2_TRIS)			// No such LED
	#define LED7_IO				(LATDbits.LATD6)

	#define LED_GET()			((BYTE)LATD & 0x07)
	#define LED_PUT(a)			do{LATD = (LATD & 0xFFF8) | ((a)&0x07);}while(0)

    #define BUTTON0_TRIS		(TRISDbits.TRISD6)	// Ref SW1
	#define	BUTTON0_IO			(PORTDbits.RD6)
	#define BUTTON1_TRIS		(TRISDbits.TRISD7)	// Ref SW2
	#define	BUTTON1_IO			(PORTDbits.RD7)
	#define BUTTON2_TRIS		(TRISDbits.TRISD13)	// Ref SW3
	#define	BUTTON2_IO			(PORTDbits.RD13)
	#define BUTTON3_TRIS		(TRISDbits.TRISD13)	// No BUTTON3 on this board
	#define	BUTTON3_IO			(1)
#if !defined(INPUT)
	#define INPUT 					1
#endif
	//Set buttons to be inputs and enable the weak pull-ups
	#define initButtons()       BUTTON0_TRIS=INPUT;BUTTON1_TRIS=INPUT;BUTTON2_TRIS=INPUT;CNPUESET=0x00098000;

	// Select which UART the STACK_USE_UART and STACK_USE_UART2TCP_BRIDGE
	// options will use.  You can change these to U1BRG, U1MODE, etc. if you
	// want to use the UART1 module instead of UART2.
	#define UBRG					U2BRG
	#define UMODE					U2MODE
	#define USTA					U2STA
	#define BusyUART()				BusyUART2()
	#define CloseUART()				CloseUART2()
	#define ConfigIntUART(a)		ConfigIntUART2(a)
	#define DataRdyUART()			DataRdyUART2()
	#define OpenUART(a,b,c)			OpenUART2(a,b,c)
	#define ReadUART()				ReadUART2()
	#define WriteUART(a)			WriteUART2(a)
	#define getsUART(a,b,c)			getsUART2(a,b,c)
	#if defined(__C32__)
		#define putsUART(a)			putsUART2(a)
	#else
		#define putsUART(a)			putsUART2((unsigned int*)a)
	#endif
	#define getcUART()				getcUART2()
	#define putcUART(a)				do{while(BusyUART()); WriteUART(a); while(BusyUART()); }while(0)
	#define putrsUART(a)			putrsUART2(a)


#endif
