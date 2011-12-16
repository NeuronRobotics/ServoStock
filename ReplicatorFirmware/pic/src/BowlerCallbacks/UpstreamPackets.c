/**
 * @file UpstreamPackets.c
 *
 * Created on: Dec 4, 2010
 * @author hephaestus
 */


#include "UserApp.h"

static BowlerPacket packetTemp;
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));

void PushAllAsync(int * state){
	SetColor(0,1,0);
	INT32_UNION s;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_POST;
	packetTemp.use.head.RPC=GetRPCValue("gacv");
	packetTemp.use.head.DataLegnth=(NUM_PINS*4)+4;
	packetTemp.use.head.MessageID=37;
	int i;
	for(i=0;i<NUM_PINS;i++){
		s.Val= state[i];
		packetTemp.use.data[(i*4)+0]=s.byte.FB;
		packetTemp.use.data[(i*4)+1]=s.byte.TB;
		packetTemp.use.data[(i*4)+2]=s.byte.SB;
		packetTemp.use.data[(i*4)+3]=s.byte.LB;
	}
	//println("Sending: ");printPacket(&packetTemp);
	PutBowlerPacket(& packetTemp);
}
void PushCounterChange(BYTE pin,LONG state){
	SetColor(0,1,0);
	INT32_UNION s;
	s.Val= state;
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_POST;
	packetTemp.use.head.RPC=GetRPCValue("gchv");
	packetTemp.use.data[0]=pin;
	packetTemp.use.data[1]=s.byte.FB;
	packetTemp.use.data[2]=s.byte.TB;
	packetTemp.use.data[3]=s.byte.SB;
	packetTemp.use.data[4]=s.byte.LB;
	packetTemp.use.head.DataLegnth=9;
	packetTemp.use.head.MessageID=5;
	PutBowlerPacket(& packetTemp);
}
void PushADCval(BYTE pin,UINT16 val){
	if(val>1024 || val<0)
		return;
	UINT16_UNION an;
	an.Val=val;
	SetColor(0,1,0);
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_POST;
	packetTemp.use.head.RPC=GetRPCValue("gchv");
	packetTemp.use.data[0]=pin;
	packetTemp.use.data[1]=an.byte.SB;
	packetTemp.use.data[2]=an.byte.LB;
	packetTemp.use.head.DataLegnth=7;
	packetTemp.use.head.MessageID=5;
	PutBowlerPacket(& packetTemp);
}
void PushDIval(BYTE pin,BYTE val){
	if(val>1 || val<0)
		return;
	SetColor(0,1,0);
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_POST;
	packetTemp.use.head.RPC=GetRPCValue("gchv");
	packetTemp.use.data[0]=pin;
	packetTemp.use.data[1]=val;
	packetTemp.use.head.DataLegnth=6;
	packetTemp.use.head.MessageID=5;
	PutBowlerPacket(& packetTemp);
}

void UpstreamPushPowerChange(void){
	SetColor(0,1,0);
	LoadCorePacket(& packetTemp);
	POWER(& packetTemp);
	packetTemp.use.head.MessageID=44;
	PutBowlerPacket(& packetTemp);
	UpdateAVRLED();
}

void POWER(BowlerPacket * packet){
	UINT16_UNION raw;
	packet->use.head.Method=BOWLER_POST;
	packet->use.head.RPC=GetRPCValue("_pwr");
	packet->use.data[0]=isRegulated_0();
	packet->use.data[1]=isRegulated_1();
	raw.Val=(WORD)(GetRawVoltage()*1000);
	packet->use.data[2]=raw.byte.SB;
	packet->use.data[3]=raw.byte.LB;
	packet->use.head.DataLegnth=8;
}

void pushPPMPacket(void){
	SetColor(0,1,0);
	GetPPMDataToPacket(& packetTemp);
	packetTemp.use.head.MessageID=45;
	PutBowlerPacket(& packetTemp);
}


