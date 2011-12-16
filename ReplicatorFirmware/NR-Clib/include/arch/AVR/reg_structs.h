/**
 * \file reg_structs.h
 * \author Peter Alley
 * \date 26 JAN 2010
 *
 * This file redefines all of the registers of the ATmega644p as structs
 * to allow for easy access to individual bit fields in each register.
 *
 * The general usage is <register name>bits._<bitfield name>
 */

#ifndef REG_STRUCTS_H_
#define REG_STRUCTS_H_

/**
 * Generic 8-bit register
 */
typedef union {
	struct {
		unsigned _P0:1;
		unsigned _P1:1;
		unsigned _P2:1;
		unsigned _P3:1;
		unsigned _P4:1;
		unsigned _P5:1;
		unsigned _P6:1;
		unsigned _P7:1;
	};
	struct {
		unsigned _w:8;
	};
} __8bitreg_t;

/**
 * DIO
 * PIN, DDR, PORT for A,B,C,D
 * 8bitreg
 */

/**
 * ADC port
 * 8bitreg
 */

/**
 * SPI port
 */
typedef union {
	struct {
		unsigned 		:5;
		unsigned _MOSI	:1;
		unsigned _MISO	:1;
		unsigned _SCK	:1;
	};
	struct {
		unsigned _w		:8;
	};
} __SPIPORTbits_t;

/**
 * TIFR0
 */
typedef union {
	struct {
		unsigned _TOV0	:1;
		unsigned _OCF0A	:1;
		unsigned _OCF0B	:1;
		unsigned 		:5;
	};
	struct {
		unsigned _w:8;
	};
} __TIFR0bits_t;

/**
 * TIFR1
 */
typedef union {
	struct {
		unsigned _TOV1	:1;
		unsigned _OCF1A	:1;
		unsigned _OCF1B	:1;
		unsigned		:2;
		unsigned _ICF1	:1;
		unsigned 		:2;
	};
	struct {
		unsigned _w:8;
	};
} __TIFR1bits_t;

/**
 * TIFR2
 */
typedef union {
	struct {
		unsigned _TOV2	:1;
		unsigned _OCF2A	:1;
		unsigned _OCF2B	:1;
		unsigned 		:5;
	};
	struct {
		unsigned _w:8;
	};
} __TIFR2bits_t;

/**
 * PCIFR
 */
typedef union {
	struct {
		unsigned _PCIF0	:1;
		unsigned _PCIF1	:1;
		unsigned _PCIF2	:1;
		unsigned _PCIF3	:1;
		unsigned 		:4;
	};
	struct {
		unsigned _w:8;
	};
} __PCIFRbits_t;

/**
 * EIFR
 */
typedef union {
	struct {
		unsigned _INTF0	:1;
		unsigned _INTF1	:1;
		unsigned _INTF2	:1;
		unsigned 		:5;
	};
	struct {
		unsigned _w:8;
	};
} __EIFRbits_t;

/**
 * EIMSK
 */
typedef union {
	struct {
		unsigned _INT0	:1;
		unsigned _INT1	:1;
		unsigned _INT2	:1;
		unsigned 		:5;
	};
	struct {
		unsigned _w:8;
	};
} __EIMSKbits_t;

/**
 * GPIOR0
 */
typedef union {
	struct {
		unsigned _b0	:1;
		unsigned _b1	:1;
		unsigned _b2	:1;
		unsigned _b3	:1;
		unsigned _b4	:1;
		unsigned _b5	:1;
		unsigned _b6	:1;
		unsigned _b7	:1;
	};
	struct {
		unsigned _w:8;
	};
} __GPIOR0bits_t;

/**
 * EECR
 */
typedef union {
	struct {
		unsigned _EERE	:1;
		unsigned _EEPE	:1;
		unsigned _EEMPE	:1;
		unsigned _EERIE	:1;
		unsigned _EEPM0	:1;
		unsigned _EEPM1	:1;
		unsigned		:2;
	};
	struct {
		unsigned 		:4;
		unsigned _EEPM	:2;
		unsigned		:2;
	};
	struct {
		unsigned _w		:8;
	};
} __EECRbits_t;

/**
 * EEDR
 * 8bitreg
 */

/**
 * EEAR
 */
typedef union {
	struct {
		unsigned _low	:8;
		unsigned _high	:8;
	};
	struct {
		unsigned _w		:16;
	};
}__16bitreg_t;

/**
 * EEARL
 * 8bitreg
 */

/**
 * EEARH
 * 8bitreg
 */

/**
 * GTCCR
 */
typedef union {
	struct {
		unsigned _PSRSYNC	:1;
		unsigned _PSRASY		:1;
		unsigned 			:5;
		unsigned _TSM		:1;
	};
	struct {
		unsigned _w:8;
	};
} __GTCCRbits_t;

/**
 * TCCR0A
 */
typedef union {
	struct {
		unsigned _WGM00	:1;
		unsigned _WGM01	:1;
		unsigned		:2;
		unsigned _COM0B0	:1;
		unsigned _COM0B1	:1;
		unsigned _COM0A0	:1;
		unsigned _COM0A1	:1;
	};
	struct {
		unsigned _WGM	:2;
		unsigned		:2;
		unsigned _COMB	:2;
		unsigned _COMA	:2;
	};
	struct {
		unsigned _w:8;
	};
} __TCCR0Abits_t;

/**
 * TCCR0B
 */
typedef union {
	struct {
		unsigned _CS00	:1;
		unsigned _CS01	:1;
		unsigned _CS02	:1;
		unsigned _WGM02	:1;
		unsigned		:2;
		unsigned _FOC0B	:1;
		unsigned _FOC0A	:1;
	};
	struct {
		unsigned _CS	:3;
		unsigned _WGM	:1;
		unsigned		:2;
		unsigned _FOC	:2;
	};
	struct {
		unsigned _w:8;
	};
} __TCCR0Bbits_t;

/**
 * TCNT0
 * 8bitreg
 */

/**
 * OCR0A
 * 8bitreg
 */

/**
 * OCR0B
 * 8bitreg
 */

/**
 * GPIOR1
 * 8bitreg
 */

/**
 * GPIOR2
 * 8bitreg
 */

/**
 * SPCR
 */
typedef union {
	struct {
		unsigned _SPR0	:1;
		unsigned _SPR1	:1;
		unsigned _CPHA	:1;
		unsigned _CPOL	:1;
		unsigned _MSTR	:1;
		unsigned _DORD	:1;
		unsigned _SPE	:1;
		unsigned _SPIE	:1;
	};
	struct {
		unsigned _SPR	:2;
		unsigned		:6;
	};
	struct {
		unsigned _w:8;
	};
} __SPCRbits_t;

/**
 * SPSR
 */
typedef union {
	struct {
		unsigned _SPI2X	:1;
		unsigned 		:5;
		unsigned _WCOL	:1;
		unsigned _SPIF	:1;
	};
	struct {
		unsigned _w:8;
	};
} __SPSRbits_t;

/**
 * SPDR
 * 8bitreg
 */

/**
 * ACSR
 */
typedef union {
	struct {
		unsigned _ACIS0	:1;
		unsigned _ACIS1	:1;
		unsigned _ACIC	:1;
		unsigned _ACIE	:1;
		unsigned _ACI	:1;
		unsigned _ACO	:1;
		unsigned _ACBG	:1;
		unsigned _ACD	:1;
	};
	struct {
		unsigned _w:8;
	};
} __ACSRbits_t;

/**
 * MONDR / OCDR
 */
typedef union {
	struct {
		unsigned _OCDR0	:1;
		unsigned _OCDR1	:1;
		unsigned _OCDR2	:1;
		unsigned _OCDR3	:1;
		unsigned _OCDR4	:1;
		unsigned _OCDR5	:1;
		unsigned _OCDR6	:1;
		unsigned _OCDR7	:1;
	};
	struct {
		unsigned		:6;
		unsigned _IDRD	:1;
	};
	struct {
		unsigned _w:8;
	};
} __OCDRbits_t;

/**
 * SMCR
 */
typedef union {
	struct {
		unsigned _SE	:1;
		unsigned _SM0	:1;
		unsigned _SM1	:1;
		unsigned _SM2	:1;
		unsigned 		:4;
	};
	struct {
		unsigned		:1;
		unsigned _SM	:3;
		unsigned		:5;
	};
	struct {
		unsigned _w:8;
	};
} __SMCRbits_t;

/**
 * MCUSR
 */
typedef union {
	struct {
		unsigned _PORF	:1;
		unsigned _EXTRF	:1;
		unsigned _BORF	:1;
		unsigned _WDRF	:1;
		unsigned _JTRF	:1;
		unsigned 		:3;
	};
	struct {
		unsigned _w:8;
	};
} __MCUSRbits_t;

/**
 * MCUCR
 */
typedef union {
	struct {
		unsigned _IVCE	:1;
		unsigned _IVSEL	:1;
		unsigned		:2;
		unsigned _PUD	:1;
		unsigned _BODSE	:1;
		unsigned _BODS	:1;
		unsigned _JTD	:1;
	};
	struct {
		unsigned _w:8;
	};
} __MCUCRbits_t;

/**
 * SPMCSR
 */
typedef union {
	struct {
		unsigned _SPMEN		:1;
		unsigned _PGERS		:1;
		unsigned _PGWRT		:1;
		unsigned _BLBSET	:1;
		unsigned _RWWSRE	:1;
		unsigned _SIGRD		:1;
		unsigned _RWWSB		:1;
		unsigned _SPMIE		:1;
	};
	struct {
		unsigned _w:8;
	};
} __SPMCSRbits_t;

/**
 * WDTCSR
 */
typedef union {
	struct {
		unsigned _WDP0	:1;
		unsigned _WDP1	:1;
		unsigned _WDP2	:1;
		unsigned _WDE	:1;
		unsigned _WDCE	:1;
		unsigned _WDP3	:1;
		unsigned _WDIE	:1;
		unsigned _WDIF	:1;
	};
	struct {
		unsigned _WDP	:3;
		unsigned		:5;
	};
	struct {
		unsigned _w:8;
	};
} __WDTCSRbits_t;

/**
 * CLKPR
 */
typedef union {
	struct {
		unsigned _CLKPS0	:1;
		unsigned _CLKPS1	:1;
		unsigned _CLKPS2	:1;
		unsigned _CLKPS3	:1;
		unsigned 			:3;
		unsigned _CLKPCE	:1;
	};
	struct {
		unsigned _CLKPS	:4;
		unsigned		:4;
	};
	struct {
		unsigned _w:8;
	};
} __CLKPRbits_t;

/**
 * PRR
 */
typedef union {
	struct {
		unsigned _PRADC		:1;
		unsigned _PRUSART0	:1;
		unsigned _PRSPI		:1;
		unsigned _PRTIM1	:1;
		unsigned _PRUSART1	:1;
		unsigned _PRTIM0	:1;
		unsigned _PRTIM2	:1;
		unsigned _PRTWI		:1;
	};
	struct {
		unsigned _w:8;
	};
} __PRRbits_t;

/**
 * OSCCAL
 * 8bitreg
 */

/**
 * PCICR
 */
typedef union {
	struct {
		unsigned _PCIE0	:1;
		unsigned _PCIE1	:1;
		unsigned _PCIE2	:1;
		unsigned _PCIE3	:1;
		unsigned 		:4;
	};
	struct {
		unsigned _PCIE	:4;
		unsigned 		:4;
	};
	struct {
		unsigned _w:8;
	};
} __PCICRbits_t;

/**
 * EICRA
 */
typedef union {
	struct {
		unsigned _ISC00	:1;
		unsigned _ISC01	:1;
		unsigned _ISC10	:1;
		unsigned _ISC11	:1;
		unsigned _ISC20	:1;
		unsigned _ISC21	:1;
		unsigned		:2;
	};
	struct {
		unsigned _ISC0	:2;
		unsigned _ISC1	:2;
		unsigned _ISC2	:2;
		unsigned		:2;
	};
	struct {
		unsigned _w:8;
	};
} __EICRAbits_t;

/**
 * PCMSK0
 */
typedef union {
	struct {
		unsigned _PCINT0:1;
		unsigned _PCINT1:1;
		unsigned _PCINT2:1;
		unsigned _PCINT3:1;
		unsigned _PCINT4:1;
		unsigned _PCINT5:1;
		unsigned _PCINT6:1;
		unsigned _PCINT7:1;
	};
	struct {
		unsigned _w:8;
	};
} __PCMSK0bits_t;

/**
 * PCMSK1
 */
typedef union {
	struct {
		unsigned _PCINT8:1;
		unsigned _PCINT9:1;
		unsigned _PCINT10:1;
		unsigned _PCINT11:1;
		unsigned _PCINT12:1;
		unsigned _PCINT13:1;
		unsigned _PCINT14:1;
		unsigned _PCINT15:1;
	};
	struct {
		unsigned _w:8;
	};
} __PCMSK1bits_t;

/**
 * PCMSK2
 */
typedef union {
	struct {
		unsigned _PCINT16:1;
		unsigned _PCINT17:1;
		unsigned _PCINT18:1;
		unsigned _PCINT19:1;
		unsigned _PCINT20:1;
		unsigned _PCINT21:1;
		unsigned _PCINT22:1;
		unsigned _PCINT23:1;
	};
	struct {
		unsigned _w:8;
	};
} __PCMSK2bits_t;

/**
 * TIMSK0
 */
typedef union {
	struct {
		unsigned _TOIE0	:1;
		unsigned _OCIE0A	:1;
		unsigned _OCIE0B	:1;
		unsigned 		:5;
	};
	struct {
		unsigned _w:8;
	};
} __TIMSK0bits_t;

/**
 * TIMSK1
 */
typedef union {
	struct {
		unsigned _TOIE1	:1;
		unsigned _OCIE1A	:1;
		unsigned _OCIE1B	:1;
		unsigned 		:2;
		unsigned _ICIE1	:1;
		unsigned 		:2;
	};
	struct {
		unsigned _w:8;
	};
} __TIMSK1bits_t;

/**
 * TIMSK2
 */
typedef union {
	struct {
		unsigned _TOIE2		:1;
		unsigned _OCIE2A	:1;
		unsigned _OCIE2B	:1;
		unsigned 			:5;
	};
	struct {
		unsigned _w:8;
	};
} __TIMSK2bits_t;

/**
 * PCMSK3
 */
typedef union {
	struct {
		unsigned _PCINT24:1;
		unsigned _PCINT25:1;
		unsigned _PCINT26:1;
		unsigned _PCINT27:1;
		unsigned _PCINT28:1;
		unsigned _PCINT29:1;
		unsigned _PCINT30:1;
		unsigned _PCINT31:1;
	};
	struct {
		unsigned _w:8;
	};
} __PCMSK3bits_t;

/**
 * ADCW
 * 16bitreg
 */

/**
 * ADCL
 * 8bitreg
 */

/**
 * ADCH
 * 8bitreg
 */

/**
 * ADCSRA
 */
typedef union {
	struct {
		unsigned _ADPS0	:1;
		unsigned _ADPS1	:1;
		unsigned _ADPS2	:1;
		unsigned _ADIE	:1;
		unsigned _ADIF	:1;
		unsigned _ADATE	:1;
		unsigned _ADSC	:1;
		unsigned _ADEN	:1;
	};
	struct {
		unsigned _ADPS	:3;
		unsigned		:5;
	};
	struct {
		unsigned _w:8;
	};
} __ADCSRAbits_t;

/**
 * ADCSRB
 */
typedef union {
	struct {
		unsigned _ADTS0	:1;
		unsigned _ADTS1	:1;
		unsigned _ADTS2	:1;
		unsigned 		:3;
		unsigned _ACME	:1;
		unsigned 		:1;
	};
	struct {
		unsigned _ADTS	:3;
		unsigned		:5;
	};
	struct {
		unsigned _w:8;
	};
} __ADCSRBbits_t;

/**
 * ADMUX
 */
typedef union {
	struct {
		unsigned _MUX0	:1;
		unsigned _MUX1	:1;
		unsigned _MUX2	:1;
		unsigned _MUX3	:1;
		unsigned _MUX4	:1;
		unsigned _ADLAR	:1;
		unsigned _REFS0	:1;
		unsigned _REFS1	:1;
	};
	struct {
		unsigned _MUX	:5;
		unsigned		:1;
		unsigned _REFS	:2;
	};
	struct {
		unsigned _w:8;
	};
} __ADMUXbits_t;

/**
 * DIDR0
 */
typedef union {
	struct {
		unsigned _ADC0D	:1;
		unsigned _ADC1D	:1;
		unsigned _ADC2D	:1;
		unsigned _ADC3D	:1;
		unsigned _ADC4D	:1;
		unsigned _ADC5D	:1;
		unsigned _ADC6D	:1;
		unsigned _ADC7D	:1;
	};
	struct {
		unsigned _w:8;
	};
} __DIDR0bits_t;

/**
 * DIDR1
 */
typedef union {
	struct {
		unsigned _AIN0D	:1;
		unsigned _AIN1D	:1;
		unsigned 		:6;
	};
	struct {
		unsigned _w:8;
	};
} __DIDR1bits_t;

/**
 * TCCR1A
 */
typedef union {
	struct {
		unsigned _WGM10		:1;
		unsigned _WGM11		:1;
		unsigned			:2;
		unsigned _COM1B0	:1;
		unsigned _COM1B1	:1;
		unsigned _COM1A0	:1;
		unsigned _COM1A1	:1;
	};
	struct {
		unsigned _WGM	:2;
		unsigned		:2;
		unsigned _COMB	:2;
		unsigned _COMA	:2;
	};
	struct {
		unsigned _w:8;
	};
} __TCCR1Abits_t;

/**
 * TCCR1B
 */
typedef union {
	struct {
		unsigned _CS10	:1;
		unsigned _CS11	:1;
		unsigned _CS12	:1;
		unsigned _WGM12	:1;
		unsigned _WGM13	:1;
		unsigned		:1;
		unsigned _ICES1	:1;
		unsigned _ICNC1	:1;
	};
	struct {
		unsigned _CS	:3;
		unsigned _WGM	:2;
		unsigned 		:3;
	};
	struct {
		unsigned _w:8;
	};
} __TCCR1Bbits_t;

/**
 * TCCR1C
 */
typedef union {
	struct {
		unsigned 		:6;
		unsigned _FOC1A	:1;
		unsigned _FOC1B	:1;
	};
	struct {
		unsigned		:6;
		unsigned _FOC	:2;
	};
	struct {
		unsigned _w:8;
	};
} __TCCR1Cbits_t;

/**
 * TCNT1
 * 16bitreg
 */

/**
 * TCNT1H
 * 8bitreg
 */

/**
 * TCNT1L
 * 8bitreg
 */

/**
 * ICR1
 * 16bitreg
 */

/**
 * ICR1H
 * 8bitreg
 */

/**
 * ICR1L8bitreg
 */

/**
 * OCR1A
 * 16bitreg
 */

/**
 * OCR1AH
 * 8bitreg
 */

/**
 * OCR1AL
 * 8bitreg
 */

/**
 * OCR1B
 * 16bitreg
 */

/**
 * OCR1H
 * 8bitreg
 */

/**
 * OCR1BL
 * 8bitreg
 */

/**
 * TCCR2A
 */
typedef union {
	struct {
		unsigned _WGM20		:1;
		unsigned _WGM21		:1;
		unsigned			:2;
		unsigned _COM2B0	:1;
		unsigned _COM2B1	:1;
		unsigned _COM2A0	:1;
		unsigned _COM2A1	:1;
	};
	struct {
		unsigned _WGM		:2;
		unsigned			:2;
		unsigned _COMB		:2;
		unsigned _COMA		:2;
	};
	struct {
		unsigned _w:8;
	};
} __TCCR2Abits_t;

/**
 * TCCR2B
 */
typedef union {
	struct {
		unsigned _CS20	:1;
		unsigned _CS21	:1;
		unsigned _CS22	:1;
		unsigned _WGM22	:1;
		unsigned		:2;
		unsigned _FOC2B	:1;
		unsigned _FOC2A	:1;
	};
	struct {
		unsigned _CS	:3;
		unsigned _WGM	:1;
		unsigned		:1;
		unsigned _FOC	:2;
	};
	struct {
		unsigned _w:8;
	};
} __TCCR2Bbits_t;

/**
 * TCNT2
 * 8bitreg
 */

/**
 * OCR2A
 * 8bitreg
 */

/**
 * OCR2B
 * 8bitreg
 */

/**
 * ASSR
 */
typedef union {
	struct {
		unsigned _TCR2BUB	:1;
		unsigned _TCR2AUB	:1;
		unsigned _OCR2BUB	:1;
		unsigned _OCR2AUB	:1;
		unsigned _TCN2UB	:1;
		unsigned _AS2		:1;
		unsigned _EXCLK		:1;
		unsigned 			:1;
	};
	struct {
		unsigned _w:8;
	};
} __ASSRbits_t;

/**
 * TWBR
 * 8bitreg
 */

/**
 * TWSR
 */
typedef union {
	struct {
		unsigned _TWPS0	:1;
		unsigned _TWPS1	:1;
		unsigned 		:1;
		unsigned _TWS3	:1;
		unsigned _TWS4	:1;
		unsigned _TWS5	:1;
		unsigned _TWS6	:1;
		unsigned _TWS7	:1;
	};
	struct {
		unsigned _TWPS	:2;
		unsigned		:1;
		unsigned _TWS	:5;
	};
	struct {
		unsigned _w:8;
	};
} __TWSRbits_t;

/**
 * TWAR
 */
typedef union {
	struct {
		unsigned _TWGCE	:1;
		unsigned _TWA0	:1;
		unsigned _TWA1	:1;
		unsigned _TWA2	:1;
		unsigned _TWA3	:1;
		unsigned _TWA4	:1;
		unsigned _TWA5	:1;
		unsigned _TWA6	:1;
	};
	struct {
		unsigned		:1;
		unsigned _TWA	:7;
	};
	struct {
		unsigned _w:8;
	};
} __TWARbits_t;

/**
 * TWDR
 * 8bitreg
 */

/**
 * TWCR
 */
typedef union {
	struct {
		unsigned _TWIE	:1;
		unsigned		:1;
		unsigned _TWEN	:1;
		unsigned _TWWC	:1;
		unsigned _TWSTO	:1;
		unsigned _TWSTA	:1;
		unsigned _TWEA	:1;
		unsigned _TWINT	:1;
	};
	struct {
		unsigned _w:8;
	};
} __TWCRbits_t;

/**
 * TWAMR
 */
typedef union {
	struct {
		unsigned _TWAM0	:1;
		unsigned _TWAM1	:1;
		unsigned _TWAM2	:1;
		unsigned _TWAM3	:1;
		unsigned _TWAM4	:1;
		unsigned _TWAM5	:1;
		unsigned _TWAM6	:1;
		unsigned _TWAM7	:1;
	};
	struct {
		unsigned _w:8;
	};
} __TWAMRbits_t;

/**
 * UCSR0A
 */
typedef union {
	struct {
		unsigned _MPCM0	:1;
		unsigned _U2X0	:1;
		unsigned _UPE0	:1;
		unsigned _DOR0	:1;
		unsigned _FE0	:1;
		unsigned _UDRE0	:1;
		unsigned _TXC0	:1;
		unsigned _RXC0	:1;
	};
	struct {
		unsigned _w:8;
	};
} __UCSR0Abits_t;

/**
 * UCSR0B
 */
typedef union {
	struct {
		unsigned _TXB80		:1;
		unsigned _RXB80		:1;
		unsigned _UCSZ02	:1;
		unsigned _TXEN0		:1;
		unsigned _RXEN0		:1;
		unsigned _UDRIE0	:1;
		unsigned _TXCIE0	:1;
		unsigned _RXCIE0	:1;
	};
	struct {
		unsigned w:8;
	};
} __UCSR0Bbits_t;

/**
 * UCSR0C
 */
typedef union {
	struct {
		unsigned _UCPOL0	:1;
		unsigned _UCSZ00	:1;
		unsigned _UCSZ01	:1;
		unsigned _USBS0		:1;
		unsigned _UPM00		:1;
		unsigned _UPM01		:1;
		unsigned _UMSEL00	:1;
		unsigned _UMSEL01	:1;
	};
	struct {
		unsigned 		:1;
		unsigned _UCSZ0	:2;
		unsigned		:1;
		unsigned _UPM0	:2;
		unsigned _UMSEL0:2;
	};
	struct {
		unsigned _w:8;
	};
} __UCSR0Cbits_t;

/**
 * UBRR0
 * 16bitreg
 */

/**
 * UBRR0H
 * 8bitreg
 */

/**
 * UBRR0L
 * 8bitreg
 */

/**
 * UDR0
 * 8bitreg
 */

/**
 * UCSR1A
 */
typedef union {
	struct {
		unsigned _MPCM1	:1;
		unsigned _U2X1	:1;
		unsigned _UPE1	:1;
		unsigned _DOR1	:1;
		unsigned _FE1	:1;
		unsigned _UDRE1	:1;
		unsigned _TXC1	:1;
		unsigned _RXC1	:1;
	};
	struct {
		unsigned _w:8;
	};
} __UCSR1Abits_t;

/**
 * UCSR1B
 */
typedef union {
	struct {
		unsigned _TXB81		:1;
		unsigned _RXB81		:1;
		unsigned _UCSZ12	:1;
		unsigned _TXEN1		:1;
		unsigned _RXEN1		:1;
		unsigned _UDRIE1	:1;
		unsigned _TXCIE1	:1;
		unsigned _RXCIE1	:1;
	};
	struct {
		unsigned _w:8;
	};
} __UCSR1Bbits_t;

/**
 * UCSR1C
 */
typedef union {
	struct {
		unsigned _UCPOL1	:1;
		unsigned _UCSZ10	:1;
		unsigned _UCSZ11	:1;
		unsigned _USBS1		:1;
		unsigned _UPM10		:1;
		unsigned _UPM11		:1;
		unsigned _UMSEL10	:1;
		unsigned _UMSEL11	:1;
	};
	struct {
		unsigned 		:1;
		unsigned _UCSZ1	:2;
		unsigned		:1;
		unsigned _UPM1	:2;
		unsigned _UMSEL1:2;
	};
	struct {
		unsigned _w:8;
	};
} __UCSR1Cbits_t;

/**
 * UBRR1
 * 16bitreg
 */

/**
 * UBRR1H
 * 8bitreg
 */

/**
 * UBRR1L
 * 8bitreg
 */

/**
 * UDR1
 * 8bitreg
 */

//#if __AVR_ARCH__ < 100
//extern volatile __8bitreg_t 	PINAbits  	__asm__ ("0x00") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	ADCPINbits  __asm__ ("0x00") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	DDRAbits  	__asm__ ("0x01") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	ADCDDRbits  __asm__ ("0x01") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	PORTAbits 	__asm__ ("0x02") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	ADCPORTbits __asm__ ("0x02") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	PINBbits  	__asm__ ("0x03") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	DDRBbits  	__asm__ ("0x04") __attribute__((section("sfr")));
//extern volatile __SPIPORTbits_t	SPIDDRbits  __asm__ ("0x04") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	PORTBbits 	__asm__ ("0x05") __attribute__((section("sfr")));
//extern volatile __SPIPORTbits_t	SPIPORTbits __asm__ ("0x05") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	PINCbits  	__asm__ ("0x06") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	DDRCbits  	__asm__ ("0x07") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	PORTCbits 	__asm__ ("0x08") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	PINDbits  	__asm__ ("0x09") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	DDRDbits  	__asm__ ("0x0A") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	PORTDbits 	__asm__ ("0x0B") __attribute__((section("sfr")));
//extern volatile __TIFR0bits_t 	TIFR0bits 	__asm__ ("0x15") __attribute__((section("sfr")));
//extern volatile __TIFR1bits_t 	TIFR1bits 	__asm__ ("0x16") __attribute__((section("sfr")));
//extern volatile __TIFR2bits_t 	TIFR2bits 	__asm__ ("0x17") __attribute__((section("sfr")));
//extern volatile __PCIFRbits_t 	PCIFRbits 	__asm__ ("0x1B") __attribute__((section("sfr")));
//extern volatile __EIFRbits_t 	EIFRits 	__asm__ ("0x1C") __attribute__((section("sfr")));
//extern volatile __EIMSKbits_t 	EIMSKbits 	__asm__ ("0x1D") __attribute__((section("sfr")));
//extern volatile __GPIOR0bits_t 	GPIOR0bits 	__asm__ ("0x1E") __attribute__((section("sfr")));
//extern volatile __EECRbits_t 	EECRbits 	__asm__ ("0x1F") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	EEDRbits 	__asm__ ("0x20") __attribute__((section("sfr")));
//extern volatile __16bitreg_t 	EEARbits 	__asm__ ("0x21") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	EEARLbits 	__asm__ ("0x21") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	EEARHbits 	__asm__ ("0x22") __attribute__((section("sfr")));
//extern volatile __GTCCRbits_t 	GTCCRbits 	__asm__ ("0x23") __attribute__((section("sfr")));
//extern volatile __TCCR0Abits_t 	TCCR0Abits 	__asm__ ("0x24") __attribute__((section("sfr")));
//extern volatile __TCCR0Bbits_t 	TCCR0Bbits 	__asm__ ("0x25") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	TCNT0bits 	__asm__ ("0x26") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	OCR0Abits 	__asm__ ("0x27") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	OCR0Bbits 	__asm__ ("0x28") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	GPIOR1bits 	__asm__ ("0x2A") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	GPIOR2bits 	__asm__ ("0x2B") __attribute__((section("sfr")));
//extern volatile __SPCRbits_t 	SPCRbits 	__asm__ ("0x2C") __attribute__((section("sfr")));
//extern volatile __SPSRbits_t 	SPSRbits 	__asm__ ("0x2D") __attribute__((section("sfr")));
//extern volatile __8bitreg_t 	SPDRbits 	__asm__ ("0x2E") __attribute__((section("sfr")));
//extern volatile __ACSRbits_t 	ACSRbits 	__asm__ ("0x30") __attribute__((section("sfr")));
//extern volatile __OCDRbits_t 	OCDRbits 	__asm__ ("0x31") __attribute__((section("sfr")));
//#define 	MONDRbits		OCDRbits
//#define 	__MONDRbits_t	__OCDRbits_t
//extern volatile __SMCRbits_t 	SMCRbits 	__asm__ ("0x33") __attribute__((section("sfr")));
//extern volatile __MCUSRbits_t 	MCUSRbits 	__asm__ ("0x34") __attribute__((section("sfr")));
//extern volatile __MCUCRbits_t 	MCUCRbits 	__asm__ ("0x35") __attribute__((section("sfr")));
//extern volatile __SPMCSRbits_t 	SPMCSRbits 	__asm__ ("0x37") __attribute__((section("sfr")));
//
//#else

extern volatile __8bitreg_t 	PINAbits  	__asm__ ("0x20") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	DDRAbits  	__asm__ ("0x21") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	PORTAbits 	__asm__ ("0x22") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	PINBbits  	__asm__ ("0x23") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	DDRBbits  	__asm__ ("0x24") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	PORTBbits 	__asm__ ("0x25") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	PINCbits  	__asm__ ("0x26") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	DDRCbits  	__asm__ ("0x27") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	PORTCbits 	__asm__ ("0x28") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	PINDbits  	__asm__ ("0x29") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	DDRDbits  	__asm__ ("0x2A") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	PORTDbits 	__asm__ ("0x2B") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	ADCPINbits  __asm__ ("0x20") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	ADCDDRbits  __asm__ ("0x21") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	ADCPORTbits __asm__ ("0x22") __attribute__((section("sfr")));
extern volatile __SPIPORTbits_t	SPIDDRbits  __asm__ ("0x24") __attribute__((section("sfr")));
extern volatile __SPIPORTbits_t	SPIPORTbits __asm__ ("0x25") __attribute__((section("sfr")));
extern volatile __TIFR0bits_t 	TIFR0bits 	__asm__ ("0x35") __attribute__((section("sfr")));
extern volatile __TIFR1bits_t 	TIFR1bits 	__asm__ ("0x36") __attribute__((section("sfr")));
extern volatile __TIFR2bits_t 	TIFR2bits 	__asm__ ("0x37") __attribute__((section("sfr")));
extern volatile __PCIFRbits_t 	PCIFRbits 	__asm__ ("0x3B") __attribute__((section("sfr")));
extern volatile __EIFRbits_t 	EIFRits 	__asm__ ("0x3C") __attribute__((section("sfr")));
extern volatile __EIMSKbits_t 	EIMSKbits 	__asm__ ("0x3D") __attribute__((section("sfr")));
extern volatile __GPIOR0bits_t 	GPIOR0bits 	__asm__ ("0x3E") __attribute__((section("sfr")));
extern volatile __EECRbits_t 	EECRbits 	__asm__ ("0x3F") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	EEDRbits 	__asm__ ("0x40") __attribute__((section("sfr")));
extern volatile __16bitreg_t 	EEARbits 	__asm__ ("0x41") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	EEARLbits 	__asm__ ("0x41") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	EEARHbits 	__asm__ ("0x42") __attribute__((section("sfr")));
extern volatile __GTCCRbits_t 	GTCCRbits 	__asm__ ("0x43") __attribute__((section("sfr")));
extern volatile __TCCR0Abits_t 	TCCR0Abits 	__asm__ ("0x44") __attribute__((section("sfr")));
extern volatile __TCCR0Bbits_t 	TCCR0Bbits 	__asm__ ("0x45") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	TCNT0bits 	__asm__ ("0x46") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	OCR0Abits 	__asm__ ("0x47") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	OCR0Bbits 	__asm__ ("0x48") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	GPIOR1bits 	__asm__ ("0x4A") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	GPIOR2bits 	__asm__ ("0x4B") __attribute__((section("sfr")));
extern volatile __SPCRbits_t 	SPCRbits 	__asm__ ("0x4C") __attribute__((section("sfr")));
extern volatile __SPSRbits_t 	SPSRbits 	__asm__ ("0x4D") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	SPDRbits 	__asm__ ("0x4E") __attribute__((section("sfr")));
extern volatile __ACSRbits_t 	ACSRbits 	__asm__ ("0x50") __attribute__((section("sfr")));
extern volatile __OCDRbits_t 	OCDRbits 	__asm__ ("0x51") __attribute__((section("sfr")));
#define 		MONDRbits		OCDRbits
#define 		__MONDRbits_t	__OCDRbits_t
extern volatile __SMCRbits_t 	SMCRbits 	__asm__ ("0x53") __attribute__((section("sfr")));
extern volatile __MCUSRbits_t 	MCUSRbits 	__asm__ ("0x54") __attribute__((section("sfr")));
extern volatile __MCUCRbits_t 	MCUCRbits 	__asm__ ("0x55") __attribute__((section("sfr")));
extern volatile __SPMCSRbits_t 	SPMCSRbits 	__asm__ ("0x57") __attribute__((section("sfr")));

//#endif

extern volatile __WDTCSRbits_t 	WDTCSRbits	__asm__ ("0x60") __attribute__((section("sfr")));
extern volatile __CLKPRbits_t 	CLKPRbits 	__asm__ ("0x61") __attribute__((section("sfr")));
extern volatile __PRRbits_t 	PRRbits 	__asm__ ("0x64") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	OSCCALbits	__asm__ ("0x66") __attribute__((section("sfr")));
extern volatile __PCICRbits_t 	PCICRbits 	__asm__ ("0x68") __attribute__((section("sfr")));
extern volatile __EICRAbits_t 	EICRAbits 	__asm__ ("0x69") __attribute__((section("sfr")));
extern volatile __PCMSK0bits_t 	PCMSK0bits 	__asm__ ("0x6B") __attribute__((section("sfr")));
extern volatile __PCMSK1bits_t 	PCMSK1bits 	__asm__ ("0x6C") __attribute__((section("sfr")));
extern volatile __PCMSK2bits_t 	PCMSK2bits	__asm__ ("0x6D") __attribute__((section("sfr")));
extern volatile __TIMSK0bits_t 	TIMSK0bits 	__asm__ ("0x6E") __attribute__((section("sfr")));
extern volatile __TIMSK1bits_t 	TIMSK1bits 	__asm__ ("0x6F") __attribute__((section("sfr")));
extern volatile __TIMSK2bits_t 	TIMSK2bits 	__asm__ ("0x70") __attribute__((section("sfr")));
extern volatile __PCMSK3bits_t 	PCMSK3bits 	__asm__ ("0x73") __attribute__((section("sfr")));
extern volatile __16bitreg_t 	ADCWbits 	__asm__ ("0x78") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	ADCLbits 	__asm__ ("0x78") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	ADCHbits 	__asm__ ("0x79") __attribute__((section("sfr")));
extern volatile __ADCSRAbits_t 	ADCSRAbits 	__asm__ ("0x7A") __attribute__((section("sfr")));
extern volatile __ADCSRBbits_t 	ADCSRBbits 	__asm__ ("0x7B") __attribute__((section("sfr")));
extern volatile __ADMUXbits_t 	ADMUXbits 	__asm__ ("0x7C") __attribute__((section("sfr")));
extern volatile __DIDR0bits_t 	DIDR0bits 	__asm__ ("0x7E") __attribute__((section("sfr")));
extern volatile __DIDR1bits_t 	DIDR1bits 	__asm__ ("0x7F") __attribute__((section("sfr")));
extern volatile __TCCR1Abits_t 	TCCR1Abits 	__asm__ ("0x80") __attribute__((section("sfr")));
extern volatile __TCCR1Bbits_t 	TCCR1Bbits 	__asm__ ("0x81") __attribute__((section("sfr")));
extern volatile __TCCR1Cbits_t 	TCCR1Cbits 	__asm__ ("0x82") __attribute__((section("sfr")));
extern volatile __16bitreg_t 	TCNT1bits 	__asm__ ("0x84") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	TCNT1Hbits 	__asm__ ("0x84") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	TCNT1Lbits 	__asm__ ("0x85") __attribute__((section("sfr")));
extern volatile __16bitreg_t 	ICR1bits 	__asm__ ("0x86") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	ICR1Hbits 	__asm__ ("0x86") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	ICR1Lbits 	__asm__ ("0x87") __attribute__((section("sfr")));
extern volatile __16bitreg_t 	OCR1Abits 	__asm__ ("0x88") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	OCR1AHbits 	__asm__ ("0x88") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	OCR1ALbits 	__asm__ ("0x89") __attribute__((section("sfr")));
extern volatile __16bitreg_t 	OCR1Bbits 	__asm__ ("0x8A") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	OCR1BHbits 	__asm__ ("0x8A") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	OCR1BLbits 	__asm__ ("0x8B") __attribute__((section("sfr")));
extern volatile __TCCR2Abits_t 	TCCR2Abits 	__asm__ ("0xB0") __attribute__((section("sfr")));
extern volatile __TCCR2Bbits_t 	TCCR2Bbits 	__asm__ ("0xB1") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	TCNT2bits 	__asm__ ("0xB2") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	OCR2Abits 	__asm__ ("0xB3") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	OCR2Bbits 	__asm__ ("0xB4") __attribute__((section("sfr")));
extern volatile __ASSRbits_t 	ASSRbits 	__asm__ ("0xB6") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	TWBRbits 	__asm__ ("0xB8") __attribute__((section("sfr")));
extern volatile __TWSRbits_t 	TWSRbits 	__asm__ ("0xB9") __attribute__((section("sfr")));
extern volatile __TWARbits_t 	TWARbits 	__asm__ ("0xBA") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	TWDRbits 	__asm__ ("0xBB") __attribute__((section("sfr")));
extern volatile __TWCRbits_t 	TWCRbits 	__asm__ ("0xBC") __attribute__((section("sfr")));
extern volatile __TWAMRbits_t 	TWAMRbits 	__asm__ ("0xBD") __attribute__((section("sfr")));
extern volatile __UCSR0Abits_t 	UCSR0Abits 	__asm__ ("0xC0") __attribute__((section("sfr")));
extern volatile __UCSR0Bbits_t 	UCSR0Bbits 	__asm__ ("0xC1") __attribute__((section("sfr")));
extern volatile __UCSR0Cbits_t 	UCSR0Cbits 	__asm__ ("0xC2") __attribute__((section("sfr")));
extern volatile __16bitreg_t 	UBRR0bits 	__asm__ ("0xC4") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	UBRR0Lbits 	__asm__ ("0xC4") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	UBRR0Hbits 	__asm__ ("0xC5") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	UDR0bits 	__asm__ ("0xC6") __attribute__((section("sfr")));
extern volatile __UCSR1Abits_t 	UCSR1Abits 	__asm__ ("0xC8") __attribute__((section("sfr")));
extern volatile __UCSR1Bbits_t 	UCSR1Bbits 	__asm__ ("0xC9") __attribute__((section("sfr")));
extern volatile __UCSR1Cbits_t 	UCSR1Cbits 	__asm__ ("0xCA") __attribute__((section("sfr")));
extern volatile __16bitreg_t	UBRR1bits 	__asm__ ("0xCC") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	UBRR1Hbits 	__asm__ ("0xCC") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	UBRR1Lbits 	__asm__ ("0xCD") __attribute__((section("sfr")));
extern volatile __8bitreg_t 	UDR1bits 	__asm__ ("0xCE") __attribute__((section("sfr")));


#endif /*REG_STRUCTS_H_*/
