/*
 * Pizo.h
 *
 *  Created on: Aug 7, 2010
 *      Author: hephaestus
 */

#ifndef PIZO_H_
#define PIZO_H_

	#define RED_LED_TRIS		(_TRISB1)	//
	#define RED_LED_IO			(_RB1)

	#define GREEN_LED_TRIS		(_TRISB2)	//
	#define GREEN_LED_IO		(_RB2)

	#define BLUE_LED_TRIS		(_TRISB3)	//
	#define BLUE_LED_IO			(_RB3)

	#define startLED()			 AD1CHS = 0x0000;AD1PCFG = 0xFFFF;AD1CON1 = 0x0000;AD1CON2 = 0x0000;AD1CON3 = 0x0000;AD1CSSL = 0x0000;PORTSetPinsDigitalOut(IOPORT_B,BIT_1|BIT_2|BIT_3)
	#define SET_RED(a)			(a==0?PORTSetBits(IOPORT_B,BIT_1):PORTClearBits(IOPORT_B,BIT_1))
	#define SET_GREEN(a)		(a==0?PORTSetBits(IOPORT_B,BIT_2):PORTClearBits(IOPORT_B,BIT_2))
	#define SET_BLUE(a)			(a==0?PORTSetBits(IOPORT_B,BIT_3):PORTClearBits(IOPORT_B,BIT_3))

#endif /* PIZO_H_ */
