/*
 * SerialPassThrough.c
 *
 *  Created on: Nov 2, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

void SendToSerialPassThrough(BowlerPacket * Packet){
	if(Packet->use.head.DataLegnth<=(MiniPacketDataSize+4)){
		SendPacketToCoProc(Packet);
		return;
	}
	ERR(Packet,48,0);
}
