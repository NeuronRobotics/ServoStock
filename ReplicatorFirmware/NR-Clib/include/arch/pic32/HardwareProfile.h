/*********************************************************************
 *
 *	Hardware specific definitions
 *
 *********************************************************************
 * FileName:        HardwareProfile.h
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
 * Author               Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Howard Schlunder		10/03/06	Original, copied from Compiler.h
 ********************************************************************/
#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H
#include "Compiler.h"

#define EM_PCB_V0p3

#if defined(ubw32)
#warning Using UBW32 PIN mapping
#else

#endif
// Set configuration fuses (but only once)
#if defined(THIS_IS_STACK_APPLICATION)
	#if defined(__18CXX)
		#if defined(__EXTENDED18__)
			#pragma config XINST=ON
		#elif !defined(HI_TECH_C)
			#pragma config XINST=OFF
		#endif

		#if defined(__18F8722) && !defined(HI_TECH_C)
			// PICDEM HPC Explorer or PIC18 Explorer board
			#pragma config OSC=HSPLL, FCMEN=OFF, IESO=OFF, PWRT=OFF, WDT=OFF, LVP=OFF
		#elif defined(_18F8722)	// HI-TECH PICC-18 compiler
			// PICDEM HPC Explorer or PIC18 Explorer board with HI-TECH PICC-18 compiler
			__CONFIG(1, HSPLL);
			__CONFIG(2, WDTDIS);
			__CONFIG(3, MCLREN);
			__CONFIG(4, XINSTDIS & LVPDIS);
		#elif defined(__18F87J10) && !defined(HI_TECH_C)
			// PICDEM HPC Explorer or PIC18 Explorer board
			#pragma config WDTEN=OFF, FOSC2=ON, FOSC=HSPLL
		#elif defined(__18F87J11) && !defined(HI_TECH_C)
			// PICDEM HPC Explorer or PIC18 Explorer board
			#pragma config WDTEN=OFF, FOSC=HSPLL
		#elif defined(__18F87J50) && !defined(HI_TECH_C)
			// PICDEM HPC Explorer or PIC18 Explorer board
			#pragma config WDTEN=OFF, FOSC=HSPLL, PLLDIV=3, CPUDIV=OSC1
		#elif (defined(__18F97J60) || defined(__18F96J65) || defined(__18F96J60) || defined(__18F87J60) || defined(__18F86J65) || defined(__18F86J60) || defined(__18F67J60) || defined(__18F66J65) || defined(__18F66J60)) && !defined(HI_TECH_C)
			// PICDEM.net 2 or any other PIC18F97J60 family device
			#pragma config WDT=OFF, FOSC2=ON, FOSC=HSPLL, ETHLED=ON
		#elif defined(_18F97J60) || defined(_18F96J65) || defined(_18F96J60) || defined(_18F87J60) || defined(_18F86J65) || defined(_18F86J60) || defined(_18F67J60) || defined(_18F66J65) || defined(_18F66J60)
			// PICDEM.net 2 board with HI-TECH PICC-18 compiler
			__CONFIG(1, WDTDIS & XINSTDIS);
			__CONFIG(2, HSPLL);
			__CONFIG(3, ETHLEDEN);
		#elif defined(__18F4620) && !defined(HI_TECH_C)
			#pragma config OSC=HSPLL, WDT=OFF, MCLRE=ON, PBADEN=OFF, LVP=OFF
		#endif
	#elif defined(__PIC24F__)
		// Explorer 16 board
		_CONFIG2(FNOSC_PRIPLL & POSCMOD_XT)		// Primary XT OSC with 4x PLL
		_CONFIG1(JTAGEN_OFF & FWDTEN_OFF)		// JTAG off, watchdog timer off
	#elif defined(__dsPIC33F__) || defined(__PIC24H__)
		// Explorer 16 board
		_FOSCSEL(FNOSC_PRIPLL)			// PLL enabled
		_FOSC(OSCIOFNC_OFF & POSCMD_XT)	// XT Osc
		_FWDT(FWDTEN_OFF)				// Disable Watchdog timer
		// JTAG should be disabled as well
	#elif defined(__dsPIC30F__)
		// dsPICDEM 1.1 board
		//_FOSC(XT_PLL16)								// XT Osc + 16X PLL
		_FOSC(FRC_PLL16)				// Internal Osc + 16X PLL
		_FWDT(WDT_OFF)					// enable Watchdog timer
		//_FBORPOR(MCLR_EN & PBOR_OFF & PWRT_OFF)
		_FBORPOR(MCLR_EN & PWRT_64 & PBOR_ON & BORV_27);
	#elif defined(__PIC32MX__)
		#if defined( __32MX440F128H__)
		/*
			#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
			#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
			#pragma config FPLLODIV = DIV_1         // PLL Output Divider
			#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
			#pragma config FWDTEN   = OFF           // Watchdog Timer
			#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
			#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
			#pragma config OSCIOFNC = OFF           // CLKO Enable

			#pragma config IESO     = ON           // Internal/External Switch-over
			#pragma config POSCMOD	= HS 		    // Oscillator Selection
			#pragma config FNOSC  = PRIPLL
			//#pragma config FNOSC    = FRC
			//#pragma config FRCDIV   = DIV_1
			#pragma config CP       = OFF           // Code Protect
			#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
		*/
			#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
			//#pragma config POSCMOD = OFF, FNOSC = FRCPLL, FPBDIV = DIV_1
			#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
			#pragma config FCKSM = CSDCMD, IESO = ON, PWP = OFF, DEBUG = OFF
			#pragma config FSOSCEN = OFF, CP = OFF, BWP = OFF, ICESEL = ICS_PGx1
		#elif defined( __32MX360F512L__)
			#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
			#pragma config POSCMOD = OFF, FNOSC = FRCPLL, FPBDIV = DIV_1
			//#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
			#pragma config FCKSM = CSDCMD, IESO = ON, PWP = OFF, DEBUG = OFF
			#pragma config FSOSCEN = OFF, CP = OFF, BWP = OFF, ICESEL = ICS_PGx1
		#elif defined( __32MX460F512L__)


			#ifdef USB_A0_SILICON_WORK_AROUND
				#pragma config UPLLEN   = OFF       // USB PLL Enabled (A0 bit inverted)
			#else
				#pragma config UPLLEN   = ON        // USB PLL Enabled
			#endif

			#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
			#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
			#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
			#pragma config FPLLODIV = DIV_1         // PLL Output Divider
			#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
			#pragma config FWDTEN   = OFF           // Watchdog Timer
			#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
			#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
			#pragma config OSCIOFNC = OFF           // CLKO Enable
			#pragma config POSCMOD  = HS            // Primary Oscillator
			#pragma config IESO     = OFF           // Internal/External Switch-over
			#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
			#pragma config FNOSC    = PRIPLL        // Oscillator Selection
			#pragma config CP       = OFF           // Code Protect
			#pragma config BWP      = OFF           // Boot Flash Write Protect
			#pragma config PWP      = OFF           // Program Flash Write Protect
			#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
			#pragma config DEBUG    = OFF            // Background Debugger Enable
		#else
			#error No hardware board defined, see "HardwareProfile.h" and __FILE__
		#endif
	#else
		#error no fuses set, check HardwareProfile.h
	#endif
#endif // Prevent more than one set of config fuse definitions

// Clock frequency value.
// This value is used to calculate Tick Counter value
#if defined(__18CXX)
	// All PIC18 processors
	#if defined(PICDEMNET2) || defined(INTERNET_RADIO)
		#define GetSystemClock()		(41666667ul)      // Hz
		#define GetInstructionClock()	(GetSystemClock()/4)
		#define GetPeripheralClock()	GetInstructionClock()
	#elif defined(__18F87J50) || defined(_18F87J50)
		#define GetSystemClock()		(48000000ul)      // Hz
		#define GetInstructionClock()	(GetSystemClock()/4)
		#define GetPeripheralClock()	GetInstructionClock()
	#else
		#define GetSystemClock()		(40000000ul)      // Hz
		#define GetInstructionClock()	(GetSystemClock()/4)
		#define GetPeripheralClock()	GetInstructionClock()
	#endif
#elif defined(__PIC24F__)
	// PIC24F processor
	#define GetSystemClock()		(32000000ul)      // Hz
	#define GetInstructionClock()	(GetSystemClock()/2)
	#define GetPeripheralClock()	GetInstructionClock()
#elif defined(__PIC24H__)
	// PIC24H processor
	#define GetSystemClock()		(80000000ul)      // Hz
	#define GetInstructionClock()	(GetSystemClock()/2)
	#define GetPeripheralClock()	GetInstructionClock()
#elif defined(__dsPIC33F__)
	// dsPIC33F processor
	#define GetSystemClock()		(80000000ul)      // Hz
	#define GetInstructionClock()	(GetSystemClock()/2)
	#define GetPeripheralClock()	GetInwasp/structionClock()
#elif defined(__dsPIC30F__)
	// dsPIC30F processor
	#define GetSystemClock()		(117920000ul)      // Hz
	#define GetInstructionClock()	(GetSystemClock()/4)
	#define GetPeripheralClock()	GetInstructionClock()

#elif defined(__PIC32MX__)
	// PIC32MX processor
	#define GetSystemClock()		(80000000ul)      // Hz (80 mhz)
	#define GetInstructionClock()	(GetSystemClock()/1)
	#define GetPeripheralClock()	(GetInstructionClock()/1)	// Set your divider according to your Peripheral Bus Frequency configuration fuse setting
	//#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FPBDIV = DIV_1, POSCMOD = XT, FNOSC = PRIPLL, CP = OFF
#endif

#if !defined(RED_LED_TRIS)
	#define RED_LED_TRIS		(_TRISB3)	//
	#define RED_LED_IO			(_RB3)

	#define GREEN_LED_TRIS		(_TRISB2)	//
	#define GREEN_LED_IO		(_RB2)

	#define BLUE_LED_TRIS		(_TRISB1)	//
	#define BLUE_LED_IO			(_RB1)
	#define startLED()			 AD1CHS = 0x0000;AD1PCFG = 0xFFFF;AD1CON1 = 0x0000;AD1CON2 = 0x0000;AD1CON3 = 0x0000;AD1CSSL = 0x0000;PORTSetPinsDigitalOut(IOPORT_B,BIT_1|BIT_2|BIT_3)
	#define SET_RED(a)			(a==0?PORTSetBits(IOPORT_B,BIT_3):PORTClearBits(IOPORT_B,BIT_3))
	#define SET_GREEN(a)		(a==0?PORTSetBits(IOPORT_B,BIT_2):PORTClearBits(IOPORT_B,BIT_2))
	#define SET_BLUE(a)			(a==0?PORTSetBits(IOPORT_B,BIT_1):PORTClearBits(IOPORT_B,BIT_1))
#endif

	#define FLAG_BUSY_TRIS			(_TRISD5)
	#define	FLAG_BUSY				(_RD5)
	#define FLAG_ASYNC_TRIS			(_TRISD7)
	#define FLAG_ASYNC				(_RD7)
	#define Init_FLAG_BUSY_ASYNC()	FLAG_ASYNC_TRIS=INPUT;FLAG_BUSY_TRIS=INPUT;


	#define AVR_RST_TRIS		(_TRISE3)
	#define AVR_RST_IO			(_RE3)
	#define InitAVR_RST()	  	 mPORTEOpenDrainOpen(BIT_3);AVR_RST_IO=0;
	//#define InitAVR_RST()	  	 mPORTEOpenDrainOpen(BIT_3);AVR_RST_IO=1;

	#define SPI_SCK_IO			(_RG6)
	#define SPI_SDI_IO			(_RG7)
	#define SPI_SDI_TRIS		(_TRISG7)
	#define SPI_SDO_IO			(_RG8)
	#define InitSPI_AVR()		mPORTGOpenDrainOpen(BIT_8);mPORTGOpenDrainOpen(BIT_6);SPI_SCK_IO=1;SPI_SDO_IO=1;SPI_SDI_TRIS=INPUT;

	#define RTS_HO_TRIS			(_TRISD4)
	#define	RTS_HO_IO			(_RD4)
	#define CTS_HO_TRIS			(_TRISD0)
	#define CTS_HO_IO			(_RD0)
	#define InitCTS_RTS_HO()	mPORTDOpenDrainOpen(BIT_4);CTS_HO_TRIS=INPUT;RTS_HO_IO=NOT_ASSERTED;

	#define UART2TX_TRIS		(_TRISF5)
	#define UART2TX_IO			(_RF5)
	#define UART2RX_TRIS		(_TRISF4)
	#define UART2RX_IO			(_RF4)

	#define UART1TX_TRIS		(_TRISD3)
	#define UART1TX_IO			(_RD3)
	#define UART1RX_TRIS		(_TRISD2)
	#define UART1RX_IO			(_RD2)
	#define ConfigUARTOpenCollector()	mPORTDOpenDrainOpen(BIT_3); mPORTFOpenDrainOpen(BIT_5);
	#define ConfigUARTRXTristate()	UART1RX_TRIS=INPUT;UART2RX_TRIS=INPUT;
	#define InitBankLEDs()
	//#define InitDS_IO()

#endif
