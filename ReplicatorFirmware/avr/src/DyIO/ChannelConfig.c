/*
 * ChannelConfig.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"

BOOL ConfigChannel(BowlerPacket * Packet){
	BYTE mode = GetChannelMode(Packet->use.data[0]);
	if ((mode == IS_UART_TX) || (mode == IS_UART_RX)){
		UINT32_UNION baudrate;
		baudrate.byte.FB = Packet->use.data[1];
		baudrate.byte.TB = Packet->use.data[2];
		baudrate.byte.SB = Packet->use.data[3];
		baudrate.byte.LB = Packet->use.data[4];
#if defined(DEBUG)
		return TRUE;
#endif
		return ConfigureUART(baudrate.Val);
	}else{
		return FALSE;
	}

}
