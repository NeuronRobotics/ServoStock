/*
 * UARTPassThrough.h
 *
 *  Created on: Apr 3, 2010
 *      Author: hephaestus
 */

#ifndef UARTPASSTHROUGH_H_
#define UARTPASSTHROUGH_H_

void InitUART(void);

BOOL ConfigureUART(UINT32 baudrate);
void StopUartPassThrough(BYTE pin);

void AddBytePassThrough(BYTE b);
void UARTGetArrayPassThrough(BYTE *packet,UINT16 size);
UINT16 Get_UART_Byte_CountPassThrough(void);

#endif /* UARTPASSTHROUGH_H_ */
