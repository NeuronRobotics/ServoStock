/*
 * User_Bowler_RPC_Process.c
 *
 *  Created on: Nov 29, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"
void setAsync(BYTE channel,BOOL async);
//extern DATA_STRUCT DATA;
static BYTE temp0;
//static BYTE temp1;
//static BYTE temp2;
//static BYTE temp3;
//static INT32_UNION PID_Temp;
//static BYTE chan;
int i;
extern DATA_STRUCT DATA __attribute__ ((section (".scs_global_var")));
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));
static UINT16_UNION timeUnion;
BYTE UserGetRPCs(BowlerPacket *Packet){
	int zone = 1;
	char tmpName[17];
	int i;
	BYTE rev[3];

	switch (Packet->use.head.RPC){
	case GCHM:
		temp0=Packet->use.data[0];
		Packet->use.data[1]=GetChannelMode(temp0);
		Packet->use.head.DataLegnth=6;
		Packet->use.head.Method=BOWLER_POST;
		break;
	case GACM:
		Packet->use.head.Method=BOWLER_POST;
		for (i=0;i<24;i++){
			Packet->use.data[i]=GetChannelMode(i);
		}
		Packet->use.head.DataLegnth=4+24;
		break;
	case GCHV:
		if(!GetChannelValue(Packet)){
			ERR(Packet,zone,0);
		}
		break;
	case _PWR:
		POWER(Packet);
		break;
	case _REV:
		SendPacketToCoProc(Packet);
		Packet->use.head.DataLegnth=4+3;
		if((Packet->use.data[0]==MAJOR_REV) && (Packet->use.data[1]==MINOR_REV) && (Packet->use.data[2]==FIRMWARE_VERSION) ){
			SetColor(0,0,1);
		}else{
			SetColor(1,0,0);
		}
//		FlashGetFwRev(rev);
//		for (i=0;i<3;i++){
//			Packet->use.data[i]=rev[i];
//		}
		Packet->use.data[0]=MAJOR_REV;
		Packet->use.data[1]=MINOR_REV;
		Packet->use.data[2]=FIRMWARE_VERSION;
		FlashGetBlRev(rev);
		for (i=0;i<3;i++){
			Packet->use.data[i+3]=rev[i];
		}
		Packet->use.head.DataLegnth=4+6;
		break;
	case INFO:
		FlashGetName(tmpName);
		i=0;
		while(tmpName[i]!=0){
			Packet->use.data[i]=tmpName[i];
			i++;
			buttonCheck(15);
		}
		Packet->use.data[i]='\0';
		Packet->use.head.Method=BOWLER_POST;
		Packet->use.head.DataLegnth=4+i+1;
		break;
	case ASYN:
		Packet->use.head.Method=BOWLER_POST;
		Packet->use.data[1]=IsAsync(Packet->use.data[0]);
		Packet->use.head.DataLegnth=4+2;
		break;

	case DPID:
		GetConfigDyPID(Packet);
		break;
	case SAFE:
		Packet->use.head.Method=BOWLER_POST;
		Packet->use.data[0]=getHeartBeatLock();
		timeUnion.Val = getHeartBeatTime();
		Packet->use.data[1]=timeUnion.byte.SB;
		Packet->use.data[2]=timeUnion.byte.LB;
		Packet->use.head.DataLegnth=4+3;
		break;
	default:
		if(CartesianControllerGetPacket(Packet) == FALSE && (ProcessPIDPacket(Packet)==FALSE)){
			SyncSessionTime(getMs());
			SendPacketToCoProc(Packet);
		}
		break;
	}
	SyncSessionTime(getMs());
	return TRUE;
}
BYTE UserPostRPCs(BowlerPacket *Packet){
	int zone = 2;
	//INT32 val;
	//float time;
	switch (Packet->use.head.RPC){
	case SCHM:
		//println("got>>\n");printPacket(Packet);
		SetChannelMode(Packet);
		break;
	case SACM:
		SetAllChannelMode(Packet);
		break;
	case SCHV:
		if(SetChannelValue(Packet))
			READY(Packet,zone,2);
		else
			ERR(Packet,zone,2);
		break;
	case SACV:
		SetAllChannelValue(Packet);
		break;

	case ASYN:
		Packet->use.head.Method=BOWLER_POST;
		setAsync(Packet->use.data[0],Packet->use.data[1]);
		Packet->use.head.DataLegnth=4;
		break;
	case SAFE:
		timeUnion.byte.SB=Packet->use.data[1];
		timeUnion.byte.LB=Packet->use.data[2];
		setHeartBeatState(Packet->use.data[0],timeUnion.Val);
		READY(Packet,zone,7);
		break;
	default:
		if(CartesianControllerPostPacket(Packet) == FALSE && (ProcessPIDPacket(Packet)==FALSE)){
			SyncSessionTime(getMs());
			SendPacketToCoProc(Packet);
		}
		break;
	}
	SyncSessionTime(getMs());
	return TRUE;
}
BYTE UserCriticalRPCs(BowlerPacket *Packet){
	int zone = 3;
	char tmpName[17];
	int i;
	switch (Packet->use.head.RPC){
	case CCHN:
		SendPacketToCoProc(Packet);
		break;
	case DPID:
		if(ConfigDyPID(Packet)){
			READY(Packet,zone,1);
		}else
			ERR(Packet,zone,1);
		break;
	case _MAC:
		//SendPacketToCoProc(Packet);
		for (i=0;i<6;i++){
			MyMAC.v[i]=Packet->use.data[i];
		}
		if(FlashSetMac(MyMAC.v)){
			READY(Packet,zone,2);
		}else
			ERR(Packet,zone,2);
		break;
	case ASYN:
		setAsync(Packet->use.data[0],TRUE);
		configAdvancedAsync(Packet);
		break;
	case SCHV:
		DATA.PIN[Packet->use.data[0]].ServoPos=Packet->use.data[1];
		SendPacketToCoProc(Packet);
		break;
	case INFO:
		if ((Packet->use.head.DataLegnth>4+16)||(Packet->use.head.DataLegnth<=4)){
			ERR(Packet,zone,3);
			break;
		}else
			for(i=0;i<17;i++){
				tmpName[i]='\0';
			}
			println("Setting name: ");
			Packet->use.data[Packet->use.head.DataLegnth-4]='\0';
			print((const char *)Packet->use.data);
			print(" Num Bytes:");
			p_ul(Packet->use.head.DataLegnth-4);
			for(i=0;i<Packet->use.head.DataLegnth-4;i++){
				tmpName[i]=Packet->use.data[i];
			}
		FlashSetName(tmpName);
		READY(Packet,zone,4);
		break;
	default:
		if(CartesianControllerCriticalPacket(Packet) == FALSE && (ProcessPIDPacket(Packet)==FALSE)){
			SyncSessionTime(getMs());
			SendPacketToCoProc(Packet);
		}
		break;
	}
	SyncSessionTime(getMs());
	return TRUE;
}

