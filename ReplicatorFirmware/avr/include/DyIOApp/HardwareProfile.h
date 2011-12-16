/*
 * HardwareProfile.h
 *
 *  Created on: Jan 25, 2010
 *      Author: bigpappa
 */

#ifndef HARDWAREPROFILE_H_
#define HARDWAREPROFILE_H_

#define FlagBusy_DDR	DDRCbits._P7
#define FlagAsync_DDR 	DDRCbits._P6
#define FlagBusy_IO		PORTCbits._P7
#define FlagAsync		PINCbits._P6
#define InitFlagPins() 	FlagBusy_DDR=OUTPUT;FlagAsync_DDR=INPUT;FlagBusy_IO=0;PORTCbits._P6=1;


#define DDR_Bank0		DDRBbits._P2
#define DDR_Bank1		DDRBbits._P1
#define Bank0			PORTBbits._P2
#define Bank1			PORTBbits._P1

#define Bank0Green()	DDR_Bank0=OUTPUT;Bank0=1;
#define Bank0Red()		DDR_Bank0=OUTPUT;Bank0=0;
#define Bank0Off()		DDR_Bank0=INPUT;Bank0=0;

#define Bank1Green()	DDR_Bank1=OUTPUT;Bank1=1;
#define Bank1Red()		DDR_Bank1=OUTPUT;Bank1=0;
#define Bank1Off()		DDR_Bank1=INPUT;Bank1=0;

#define InitBankLEDs()	Bank0Off();Bank1Off();


#define DDR0		DDRBbits._P7
#define PO0			PORTBbits._P7
#define PI0			PINBbits._P7

#define DDR1		DDRBbits._P6
#define PO1			PORTBbits._P6
#define PI1			PINBbits._P6

#define DDR2		DDRBbits._P5
#define PO2			PORTBbits._P5
#define PI2			PINBbits._P5

#define DDR3		DDRDbits._P5
#define PO3			PORTDbits._P5
#define PI3			PINDbits._P5

#define DDR4		DDRDbits._P7
#define PO4			PORTDbits._P7
#define PI4			PINDbits._P7

#define DDR5		DDRDbits._P6
#define PO5			PORTDbits._P6
#define PI5			PINDbits._P6

#define DDR6		DDRBbits._P3
#define PO6			PORTBbits._P3
#define PI6			PINBbits._P3

#define DDR7		DDRBbits._P4
#define PO7			PORTBbits._P4
#define PI7			PINBbits._P4

#define DDR8		DDRAbits._P0
#define PO8			PORTAbits._P0
#define PI8			PINAbits._P0

#define DDR9		DDRAbits._P1
#define PO9			PORTAbits._P1
#define PI9			PINAbits._P1

#define DDR10		DDRAbits._P2
#define PO10		PORTAbits._P2
#define PI10		PINAbits._P2

#define DDR11		DDRAbits._P3
#define PO11		PORTAbits._P3
#define PI11		PINAbits._P3


#define DDR12		DDRAbits._P4
#define PO12		PORTAbits._P4
#define PI12		PINAbits._P4

#define DDR13		DDRAbits._P5
#define PO13		PORTAbits._P5
#define PI13		PINAbits._P5

#define DDR14		DDRAbits._P6
#define PO14		PORTAbits._P6
#define PI14		PINAbits._P6


#define DDR15		DDRAbits._P7
#define PO15		PORTAbits._P7
#define PI15		PINAbits._P7

#define DDR16		DDRDbits._P3
#define PO16		PORTDbits._P3
#define PI16		PINDbits._P3

#define DDR17		DDRDbits._P2
#define PO17		PORTDbits._P2
#define PI17		PINDbits._P2

#define DDR18		DDRCbits._P5
#define PO18		PORTCbits._P5
#define PI18		PINCbits._P5

#define DDR19		DDRCbits._P4
#define PO19		PORTCbits._P4
#define PI19		PINCbits._P4

#define DDR20		DDRCbits._P3
#define PO20		PORTCbits._P3
#define PI20		PINCbits._P3

#define DDR21		DDRCbits._P2
#define PO21		PORTCbits._P2
#define PI21		PINCbits._P2

#define DDR22		DDRCbits._P1
#define PO22		PORTCbits._P1
#define PI22		PINCbits._P1

#define DDR23		DDRCbits._P0
#define PO23		PORTCbits._P0
#define PI23		PINCbits._P0










#endif /* HARDWAREPROFILE_H_ */
