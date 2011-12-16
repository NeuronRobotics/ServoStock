/*
 *
 * Copyright 2009 Neuron Robotics, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "UserApp.h"

static BYTE zone;

BYTE UserGetRPCs(BowlerPacket *Packet){
	zone = 4;
	UINT16 i;
	UINT16  start;
	UINT16 end;
	//UINT16_UNION adc;
	switch (Packet->use.head.RPC){
	case GCHM:
		Packet->use.data[1]=EEReadMode(Packet->use.data[0]);
		Packet->use.head.DataLegnth=6;
		Packet->use.head.Method=BOWLER_POST;
		break;
	case GACM:
		for (i=0;i<24;i++){
			Packet->use.data[i]=EEReadMode(i);
		}
		Packet->use.head.DataLegnth=4+24;
		Packet->use.head.Method=BOWLER_POST;
		break;
	case GCHV:
		AsynAck();
		if(!GetChannelValue(Packet)){
			ERR(Packet,zone,0);
		}
		break;
	case EEPD:
		start = Packet->use.data[0];
		end = Packet->use.data[1];
		Packet->use.head.Method=BOWLER_POST;
		if (end >= start){
			for (i=start;i<end;i++){
				Packet->use.data[i-start]=EEReadData(i);
			}
			Packet->use.head.DataLegnth= 4+end-start;
		}else
			ERR(Packet,zone,1);
		break;
	case _REV:
		Packet->use.data[0]=MAJOR_REV;
		Packet->use.data[1]=MINOR_REV;
		Packet->use.data[2]=FIRMWARE_VERSION;
		Packet->use.head.DataLegnth=4+3;
		break;
//	case DASN:
//		AsynAck();
//		for (i=0;i<24;i++){
//			Packet->use.data[i]=GetChanVal(i);
//		}
//		Packet->use.head.DataLegnth = 4 + 24;
//		Packet->use.head.Method=BOWLER_POST;
//		Packet->use.head.RPC=GetRPCValue("_rdy");
//		break;
//	case AASN:
//		AsynAck();
//		for (i=0;i<8;i++){
//			adc.Val=GetChanVal(i+8);
//			if (adc.Val>1023)
//				adc.Val=1023;
//			Packet->use.data[(i*2)  ]=adc.byte.SB;
//			Packet->use.data[(i*2)+1]=adc.byte.LB;
//		}
//		Packet->use.head.DataLegnth = 4 + (8*2);
//		Packet->use.head.Method=BOWLER_POST;
//		Packet->use.head.RPC=GetRPCValue("_rdy");
//		break;
	case SAVE:
		Packet->use.head.Method=BOWLER_POST;
		Packet->use.head.DataLegnth = 4 + NUM_PINS;
		for (i=0;i<NUM_PINS;i++){
			Packet->use.data[i]=EEReadValue(i);
		}
		break;
	default:
#if defined(USE_AS_LIBRARY)
		return DyIOLibOnPacket(Packet);
#else
		return FALSE;
#endif
	}
	return TRUE;
}
BYTE UserPostRPCs(BowlerPacket *Packet){
	zone = 5;
	UINT16_UNION v;
	UINT16 start;
	UINT16  end;
	UINT16 i;
	switch (Packet->use.head.RPC){
	case SCHM:
		if(SetChannelMode(Packet)==FALSE){
			ERR(Packet,zone,0);
		}
		break;
	case SACM:
		if(!SetAllChannelMode(Packet)){
			ERR(Packet,zone,1);
		}
		break;
	case SCHV:
		if(SetChannelValue(Packet)){
			READY(Packet,zone,2);
			break;
		}
		else
			ERR(Packet,zone,2);
		break;
	case SACV:
		if(SetAllChannelValue(Packet)){
			READY(Packet,zone,37);
		}else{
			ERR(Packet,zone,3);
		}
		break;
	case _PWR:
		v.byte.SB = Packet->use.data[2];
		v.byte.LB = Packet->use.data[3];
		SetPowerState0(Packet->use.data[2],Packet->use.data[0]);
		SetPowerState1(Packet->use.data[3],Packet->use.data[1]);
		//Packet->use.head.MessageID=44;
		break;
	case EEPD:
		start = Packet->use.data[0];
		end = Packet->use.data[1];
		if (end >= start){
			for (i=0;i<(end-start);i++){
				EEWriteData(i+start,Packet->use.data[i+2]);
			}
		}else
			ERR(Packet,zone,4);
		break;
	default:
#if defined(USE_AS_LIBRARY)
		return DyIOLibOnPacket(Packet);
#else
		return FALSE;
#endif
	}
	return TRUE;
}
BYTE UserCriticalRPCs(BowlerPacket *Packet){
	zone = 6;
	BYTE pin,val,conf;
	switch (Packet->use.head.RPC){
	case CCHN:
		conf = ConfigChannel(Packet);
		if(conf==FALSE){
			ERR(Packet,zone,conf);
		}else
			READY(Packet,zone,conf);
		break;
	case _MAC:
		if(ProvisionMAC(Packet->use.data)){
			READY(Packet,zone,1);
			break;
		}
		else
			ERR(Packet,zone,1);
		break;
	case SCHV:
		pin = Packet->use.data[0];
		val = Packet->use.data[1];
		if(SetChannelValue(Packet)){
			if(SaveValue(pin,val))
				READY(Packet,zone,2);
			else
				ERR(Packet,zone,2);
		}
		else
			ERR(Packet,zone,3);
		break;
	case POVR:
		setPowerOverride(Packet->use.data[0]);
		READY(Packet,zone,3);
		break;
	default:
#if defined(USE_AS_LIBRARY)
		return DyIOLibOnPacket(Packet);
#else
		return FALSE;
#endif
	}
	return TRUE;
}

