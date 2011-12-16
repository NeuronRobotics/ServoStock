/*
 * UARTPassThrough.c
 *
 *  Created on: Apr 3, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

extern DATA_STRUCT DATA;

#if defined(__AVR_ATmega324P__)
	#define UART_PASS_BUFF_SIZE 5
#else
	#define UART_PASS_BUFF_SIZE 100
#endif


static BYTE privateRXUART[UART_PASS_BUFF_SIZE];
static BYTE_FIFO_STORAGE store;

BOOL validBaud(UINT32 baud);

void InitUART(void){
	UINT32 baudrate = EEReadBaud();
	if (validBaud(baudrate) == FALSE){
		baudrate = 19200;
		validBaud(baudrate);
	}

	SetPinTris(16,OUTPUT);
	SetPinTris(17,INPUT);
	SetDIO(17,ON);

	/* set the framing to 8N1 */
	UCSR1C = ((1<< UCSZ10)|(1<< UCSZ11));
	/* rx interrupts enabled, rx and tx enabled, 8-bit data */
	UCSR1B =( _BV(RXCIE1) | _BV(RXEN1) | _BV(TXEN1));
	UCSR1A = 0x00;
	//println("Uart Initialization: ");
	InitByteFifo(&store,privateRXUART,UART_PASS_BUFF_SIZE);
}
void StopUartPassThrough(BYTE pin){
	if (DATA.FUNCTION[pin].HAS_UART == FALSE){
		return;
	}
	UCSR1B=0;
	//InitByteFifo(&store,privateRXUART,sizeof(privateRXUART));
	switch(GetChannelMode(pin)){
		case IS_UART_TX:
		case IS_UART_RX:
			configPinMode(16,IS_DI,INPUT,ON);
			configPinMode(17,IS_DI,INPUT,ON);
	}
}

BOOL ConfigureUART(UINT32 baudrate){
	return validBaud(baudrate);
}

BOOL validBaud(UINT32 baud){
	switch(baud){
	case   2400:
		UBRR1=479;
		break;
	case   4800:
		UBRR1=239;
		break;
	case   9600:
		UBRR1=119;
		break;
	case  14400:
		UBRR1=79;
		break;
	case  19200:
		UBRR1=59;
		break;
	case  28800:
		UBRR1=39;
		break;
	case  38400:
		UBRR1=29;
		break;
	case  57600:
		UBRR1=19;
		break;
	case  76800:
		UBRR1=14;
		break;
	case 115200:
		UBRR1=9;
		break;
	case 230400:
		UBRR1=4;
		break;
	default:
		return FALSE;
	}
	EEWriteBaud(baud);
	return TRUE;
}

/**
 * Private helpers
 */
ISR(USART1_RX_vect){
	//BYTE read;
	//while ((UCSR0A & 0x80) == 0 );
	//read = UDR1;
	//AddBytePassThrough(read);
	BYTE err;
	FifoAddByte(&store,UDR1,&err);
}

void UARTGetArrayPassThrough(BYTE *packet,UINT16 size){
	FifoGetByteStream(&store,packet,size);
}

UINT16 Get_UART_Byte_CountPassThrough(void){
	return FifoGetByteCount(&store);
}

