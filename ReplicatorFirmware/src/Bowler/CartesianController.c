#include "main.h"
#define SIZE_OR_PACKET_BUFFER 400
PACKET_FIFO_STORAGE  packetFifo;
BowlerPacket buffer[SIZE_OR_PACKET_BUFFER];
BowlerPacket linTmpPack;
BowlerPacket packetTemp;
INTERPOLATE_DATA intCartesian[3];


float scale = -1/(ticksPerDegree*gearRatio);
float extrusionScale = -10/(ticksPerDegree);

BYTE setXYZ(float x, float y, float z);
void interpolateZXY();
float getLinkAngle(int index);
float setLinkAngle(int index, float value);

BOOL done = TRUE;
BOOL full = FALSE;
int  lastPushedBufferSize =0;

static RunEveryData pid ={0,100};

BOOL isCartesianInterpolationDone(){
    return done;
}

void initializeCartesianController(){
    initializeDelta();
    float cx=0,cy=0,cz=0;
    getCurrentPosition(&cx, &cy, &cz);
    setInterpolateXYZ(cx, cy, cz, 0);
    InitPacketFifo(&packetFifo,buffer,SIZE_OR_PACKET_BUFFER);
}

void pushBufferEmpty(){
    	prep(& packetTemp);
	packetTemp.use.head.Method=BOWLER_ASYN;
	packetTemp.use.head.MessageID = 1;
	packetTemp.use.head.RPC = GetRPCValue("_sli");
	INT32_UNION tmp;
        tmp.Val=lastPushedBufferSize;
        packetTemp.use.data[0]=tmp.byte.FB;
        packetTemp.use.data[1]=tmp.byte.TB;
        packetTemp.use.data[2]=tmp.byte.SB;
        packetTemp.use.data[3]=tmp.byte.LB;
        packetTemp.use.head.DataLegnth=4+4;
        asyncCallback(&packetTemp);
}

void cartesianAsync(){
    if(RunEvery(&pid)){
        int tmp =FifoGetPacketSpaceAvailible(&packetFifo);
        if(tmp!= lastPushedBufferSize){
            lastPushedBufferSize=tmp;
            pushBufferEmpty();
            full = FALSE;
        }
    }
}

void processLinearInterpPacket(BowlerPacket * Packet){
    INT32_UNION tmp;
    float tmpData [5];
    int i;
    tmp.byte.FB=Packet->use.data[0];
    tmp.byte.TB=Packet->use.data[1];
    tmp.byte.SB=Packet->use.data[2];
    tmp.byte.LB=Packet->use.data[3];
    tmpData[0] = ((float)tmp.Val);
    for(i=1;i<5;i++){
        tmp.byte.FB=Packet->use.data[(i*4)+0];
        tmp.byte.TB=Packet->use.data[(i*4)+1];
        tmp.byte.SB=Packet->use.data[(i*4)+2];
        tmp.byte.LB=Packet->use.data[(i*4)+3];
        tmpData[i] = ((float)tmp.Val)/1000;
    }
    Print_Level l = getPrintLevel();
    setPrintLevelInfoPrint();
    setInterpolateXYZ(tmpData[1], tmpData[2], tmpData[3],tmpData[0]);
    setPrintLevel(l);
    SetPIDTimed(EXTRUDER0_INDEX, tmpData[4]/extrusionScale,tmpData[0]);
}

BOOL onCartesianPost(BowlerPacket *Packet){
    Print_Level l = getPrintLevel();
    switch(Packet->use.head.RPC){
        case _SLI:
            FifoAddPacket(&packetFifo,Packet);
            Packet->use.head.Method = BOWLER_STATUS;
            INT32_UNION tmp;
            tmp.Val=FifoGetPacketSpaceAvailible(&packetFifo);
            Packet->use.data[0]=tmp.byte.FB;
            Packet->use.data[1]=tmp.byte.TB;
            Packet->use.data[2]=tmp.byte.SB;
            Packet->use.data[3]=tmp.byte.LB;
            Packet->use.head.DataLegnth=4+4;
            if(tmp.Val == 0){
                full=TRUE;
            }
            
            setPrintLevelInfoPrint();
            println_I("Cached linear Packet ");
            setPrintLevel(l);
            return TRUE;
        case PRCL:
            setPrintLevelInfoPrint();
            println_I("Cancel Print");
            setPrintLevel(l);
            while(FifoGetPacketCount(&packetFifo)>0){
                FifoGetPacket(&packetFifo,&linTmpPack);
            }
            initializeCartesianController();
            READY(Packet,35,35);
            return TRUE;

    }
    return FALSE;
}
BOOL onCartesianGet(BowlerPacket *Packet){
    return FALSE;
}
BOOL onCartesianCrit(BowlerPacket *Packet){
    return FALSE;
}

BOOL onCartesianPacket(BowlerPacket *Packet){
    Print_Level l = getPrintLevel();
    setPrintLevelInfoPrint();
    println_I("Packet Checked by Cartesian Controller");
    BOOL ret = FALSE;
    switch(Packet->use.head.Method){
        case BOWLER_POST:
            ret = onCartesianPost(Packet);
            break;
        case BOWLER_GET:
            ret = onCartesianGet(Packet);
            break;
        case BOWLER_CRIT:
            ret = onCartesianCrit(Packet);
            break;
    }
    setPrintLevel(l);
    return ret;
}


void interpolateZXY(){
    float x=0,y=0,z=0;
    float ms= getMs();
    x = interpolate((INTERPOLATE_DATA *)&intCartesian[0],ms);
    y = interpolate((INTERPOLATE_DATA *)&intCartesian[1],ms);
    z = interpolate((INTERPOLATE_DATA *)&intCartesian[2],ms);
    if(!isCartesianInterpolationDone())
        setXYZ( x, y, z);
    BOOL move = FALSE;
    int i;
    for(i=0;i<3;i++){
        if(move==FALSE && intCartesian[i].setTime > 0){
            move = TRUE;
        }
    }
    if(!move){
        if(!isCartesianInterpolationDone()){
            done = TRUE;
        }
    }
    if(isCartesianInterpolationDone() && FifoGetPacketCount(&packetFifo)>0){
        if(FifoGetPacket(&packetFifo,&linTmpPack)){
            processLinearInterpPacket(&linTmpPack);
        }
    }
}

BYTE setInterpolateXYZ(float x, float y, float z,float ms){
    int i=0;
    if(ms<.01)
        ms=0;
    float start = getMs();
    intCartesian[0].set=x;
    intCartesian[1].set=y;
    intCartesian[2].set=z;
    
    float cx=0,cy=0,cz=0;

    getCurrentPosition(&cx, &cy, &cz);
    intCartesian[0].start=cx;
    intCartesian[1].start=cy;
    intCartesian[2].start=cz;
    println_I("\n\nSetting new position x=");p_fl_E(x);print_E(" y=");p_fl_E(y);print_E(" z=");p_fl_E(z);print_E(" Time MS=");p_fl_E(ms);
    println_I("Current  position cx=");p_fl_E(cx);print_E(" cy=");p_fl_E(cy);print_E(" cz=");p_fl_E(cz);
    println_I("Current  angles t1=");p_fl_E(getLinkAngle(0));print_E(" t2=");p_fl_E(getLinkAngle(1));print_E(" t3=");p_fl_E(getLinkAngle(2));

    for(i=0;i<3;i++){
	intCartesian[i].setTime=ms;
	
	intCartesian[i].startTime=start;
    }
    if(ms==0){
        setXYZ( x,  y,  z);
    }else{
        done = FALSE;
    }

}

BYTE setXYZ(float x, float y, float z){
    float t0=0,t1=0,t2=0;
    if(delta_calcInverse( x,  y, z,  &t0, &t1, &t2)==0){
        println_I("New target angles t1=");p_fl_E(t0);print_E(" t2=");p_fl_E(t1);print_E(" t3=");p_fl_E(t2);
        setLinkAngle(0,t0);
        setLinkAngle(1,t1);
        setLinkAngle(2,t2);
        done = FALSE;
    }else{
        println_E("Interpolate failed, can't reach: x=");p_fl_E(x);print_E(" y=");p_fl_E(y);print_E(" z=");p_fl_E(z);
    }
}

int linkToHWIndex(int index){
   int localIndex=0;
    switch(index){
        case 0:
            localIndex = LINK0_INDEX;
            break;
        case 1:
            localIndex = LINK1_INDEX;
            break;
        case 2:
            localIndex = LINK2_INDEX;
            break;
    }
    return localIndex;
}

int getCurrentPosition(float * x, float * y, float * z){
   return delta_calcForward(    getLinkAngle(0),
                                getLinkAngle(1),
                                getLinkAngle(2),
                                x, y, z);
}

float getLinkAngle(int index){
    int localIndex=linkToHWIndex(index);
    return GetPIDPosition(localIndex)*scale;
}

float setLinkAngle(int index, float value){
    int localIndex=linkToHWIndex(index);
    float v = value/scale;
    if(v>1650){
        println_E("Upper Capped link ");p_sl_E(index);print_E(", attempted: ");p_fl_E(value);
        v=1650;
    }
    if(v<-6500){
        v=-6500;
        println_E("Lower Capped link ");p_sl_E(index);print_E(", attempted: ");p_fl_E(value);
    }
    return SetPID(localIndex,v);
}