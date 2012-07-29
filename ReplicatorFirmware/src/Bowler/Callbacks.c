/*
 * Callbacks.c
 *
 *  Created on: Jul 8, 2010
 *      Author: hephaestus
 */
#include "EthernetController.h"
#define _DBG				0x6762645f // '_dbg'  Set up the debugging
#if !defined(NUM_PID_GROUPS )
#define NUM_PID_GROUPS 8
#endif
static INT32_UNION PID_Temp;
static float time;
static int val;
BowlerPacket tmpData;
BYTE PacketPassThrough(BowlerPacket *Packet){
	BYTE board = Packet->use.data[0];
	BYTE dataSize =  Packet->use.head.DataLegnth-5;
	int i;
	switch(board){
	case 0xff:
		if(dataSize%NUM_PID_GROUPS !=0){
			println_E("Invalid data size: ");p_sl_E(dataSize);
			return FALSE;
		}
		for(i=0;i<Packet->use.head.DataLegnth+11;i++){
			tmpData.stream[i] = Packet->stream[i];
		}
		for(i=0;i<NUM_PID_GROUPS;i++){
			for(i=0;i<11;i++){
				 Packet->stream[i]=tmpData.stream[i];
			}
			Packet->use.data[0] = i;
			BYTE chunkSize = (dataSize/NUM_PID_GROUPS);
			for(i=0;i< chunkSize;i++){
				Packet->use.data[1+i]=tmpData.use.data[1+(i* chunkSize)];
			}
			BowlerSPITranceive(Packet,FALSE);
		}
		break;
	case 0xfe:
		for(i=0;i<Packet->use.head.DataLegnth+11;i++){
			tmpData.stream[i] = Packet->stream[i];
		}
		for(i=0;i<NUM_PID_GROUPS;i++){
			for(i=0;i<11;i++){
				 Packet->stream[i]=tmpData.stream[i];
			}
			Packet->use.data[0] = i;
			BYTE chunkSize = (dataSize);
			for(i=0;i< chunkSize;i++){
				Packet->use.data[1+i]=tmpData.use.data[1+i];
			}
			BowlerSPITranceive(Packet,FALSE);
		}
		break;
	default:
		if(board<NUM_PID_GROUPS){
			// data sent to one board
			BowlerSPITranceive(Packet,TRUE);
		}else{
			return FALSE;
		}
		break;
	}
	return TRUE;
}

BYTE UserGetRPCs(BowlerPacket *Packet){
	int i;
	switch (Packet->use.head.RPC){
	case APID:
		Packet->use.head.DataLegnth=4;
		for(i=0;i<NUM_PID_GROUPS;i++){
			PID_Temp.Val=getCurrentEncoderValue(i);
			Packet->use.data[0+(i*4)]=PID_Temp.byte.FB;
			Packet->use.data[1+(i*4)]=PID_Temp.byte.TB;
			Packet->use.data[2+(i*4)]=PID_Temp.byte.SB;
			Packet->use.data[3+(i*4)]=PID_Temp.byte.LB;
			Packet->use.head.DataLegnth+=4;
		}
		Packet->use.head.Method=BOWLER_POST;
		break;
	case _PID:
		BowlerSPITranceive(Packet,TRUE);
		break;
	case CPID:
		BowlerSPITranceive(Packet,TRUE);
		break;
	default:
		return PacketPassThrough(Packet);
	}
	return TRUE;
}
BYTE UserPostRPCs(BowlerPacket *Packet){
	int i;
	INT32_UNION v;
        INT32_UNION t;
	switch (Packet->use.head.RPC){
	case APID:
                t.byte.FB=Packet->use.data[0];
                t.byte.TB=Packet->use.data[1];
                t.byte.SB=Packet->use.data[2];
                t.byte.LB=Packet->use.data[3];
		for(i=0;i<NUM_PID_GROUPS;i++){
			v.byte.FB=Packet->use.data[4+(i*4)];
			v.byte.TB=Packet->use.data[5+(i*4)];
			v.byte.SB=Packet->use.data[6+(i*4)];
			v.byte.LB=Packet->use.data[7+(i*4)];
			SetPIDCurrent(i,v.Val,t.Val );
		}
		break;
	case _PID:
		BowlerSPITranceive(Packet,TRUE);
		break;
	case RPID:
		BowlerSPITranceive(Packet,TRUE);
		break;
	default:
		return PacketPassThrough(Packet);
	}
	return TRUE;
}
BYTE UserCriticalRPCs(BowlerPacket *Packet){
	int i;
	switch (Packet->use.head.RPC){
	case KPID:
		for(i=0;i<NUM_PID_GROUPS;i++){
			killPid(i);
		}
		break;
	case CPID:
		BowlerSPITranceive(Packet,TRUE);
		break;
	default:
		return PacketPassThrough(Packet);
	}
	return TRUE;
}


