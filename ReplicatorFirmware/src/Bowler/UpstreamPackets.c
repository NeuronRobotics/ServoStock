#include "main.h"
static float lastPacketTime[NUM_PID_GROUPS];
static INT32 lastPacketVal[NUM_PID_GROUPS];
static BowlerPacket packetTemp;

/*
void pushPIDLimitMine(BYTE chan,BYTE index,INT32  tick){
	//SetColor(0,1,0);
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.MessageID = 4;
	packetTemp.use.head.RPC = GetRPCValue("pidl");
	packetTemp.use.head.DataLegnth = 4+1+1+4+4;
	packetTemp.use.data[0]=chan;
	packetTemp.use.data[1]=index;
	INT32_UNION tmp;
	tmp.Val=tick;
	packetTemp.use.data[2]=tmp.byte.FB;
	packetTemp.use.data[3]=tmp.byte.TB;
	packetTemp.use.data[4]=tmp.byte.SB;
	packetTemp.use.data[5]=tmp.byte.LB;
	tmp.Val=getMs();
	packetTemp.use.data[6]=tmp.byte.FB;
	packetTemp.use.data[7]=tmp.byte.TB;
	packetTemp.use.data[8]=tmp.byte.SB;
	packetTemp.use.data[9]=tmp.byte.LB;

	SetCRC(&packetTemp);
	disableDebug();
	putStream(packetTemp.stream,GetPacketLegnth(& packetTemp));
	EthTx(& packetTemp);
	
}
*/

void pushPIDMine(BYTE chan, INT32 value){
	println_I("Pushing async for board: ");p_sl_I(chan);print_I(" value: ");p_sl_I(value);
	//SetColor(0,1,0);
	LoadCorePacket(& packetTemp);
	packetTemp.use.head.Method=BOWLER_ASYN;
	packetTemp.use.head.MessageID = 3;
	packetTemp.use.head.RPC = GetRPCValue("_pid");
	packetTemp.use.head.DataLegnth = 4+1+4+4+4;
	packetTemp.use.data[0]=chan;
	INT32_UNION tmp;
	tmp.Val=value;
	packetTemp.use.data[1]=tmp.byte.FB;
	packetTemp.use.data[2]=tmp.byte.TB;
	packetTemp.use.data[3]=tmp.byte.SB;
	packetTemp.use.data[4]=tmp.byte.LB;
	tmp.Val=getMs();
	packetTemp.use.data[5]=tmp.byte.FB;
	packetTemp.use.data[6]=tmp.byte.TB;
	packetTemp.use.data[7]=tmp.byte.SB;
	packetTemp.use.data[8]=tmp.byte.LB;

	float diffTime = getMs()-lastPacketTime[chan];
	float diffVal  = value - lastPacketVal[chan];

	tmp.Val = (INT32) (diffVal/diffTime);
	packetTemp.use.data[9]=tmp.byte.FB;
	packetTemp.use.data[10]=tmp.byte.TB;
	packetTemp.use.data[11]=tmp.byte.SB;
	packetTemp.use.data[12]=tmp.byte.LB;

	lastPacketVal[chan] =value;
	lastPacketTime[chan]=getMs();
	SetCRC(&packetTemp);
        //EthTx(& packetTemp);
	//putStream(packetTemp.stream,GetPacketLegnth(& packetTemp));
        push(& packetTemp);
}

void pushEncoders(void){
	INT32_UNION PID_Temp;
	packetTemp.use.head.DataLegnth=4;
	packetTemp.use.head.RPC = GetRPCValue("apid");
        int i;
	for(i=0;i<NUM_PID_GROUPS;i++){
		PID_Temp.Val=getCurrentEncoderValue(i);
		packetTemp.use.data[0+(i*4)]=PID_Temp.byte.FB;
		packetTemp.use.data[1+(i*4)]=PID_Temp.byte.TB;
		packetTemp.use.data[2+(i*4)]=PID_Temp.byte.SB;
		packetTemp.use.data[3+(i*4)]=PID_Temp.byte.LB;
		packetTemp.use.head.DataLegnth+=4;
	}
	packetTemp.use.head.Method=BOWLER_ASYN;
	push(&packetTemp);
}

void push(BowlerPacket * Packet){
    EthTx(Packet);
    putStream(Packet->stream,GetPacketLegnth(Packet));
}
