#include "main.h"
#if defined(__32MX795F512L__)
    #define SIZE_OF_PACKET_BUFFER 400
#elif defined(__32MX440F128H__)
    #define SIZE_OF_PACKET_BUFFER 40
#endif




PACKET_FIFO_STORAGE  packetFifo;
BowlerPacket buffer[SIZE_OF_PACKET_BUFFER];
BowlerPacket linTmpPack;
BowlerPacket packetTemp;
INTERPOLATE_DATA intCartesian[3];

float scale = -1.0/(ticksPerDegree*gearRatio);
float extrusionScale = 1/(((float)ticksPerRev)/100.00);

BYTE setXYZ(float x, float y, float z);
void interpolateZXY();
float getLinkAngle(int index);
float setLinkAngle(int index, float value, float ms);

float xCurrent,yCurrent,zCurrent,eCurrent;
BOOL full = FALSE;


int  lastPushedBufferSize =0;
float lastXYZE[4];

static RunEveryData pid ={0,100};


//Default values for ServoStock
HardwareMap hwMap ={
    {0,1.0},//axis 0
    {1,1.0},//axis 1
    {2,1.0},//axis 2
    {
        {3,1.0},// Motor
        {11,1.0}// Heater
    },//Extruder 0
    {
        {AXIS_UNUSED,1.0},
        {AXIS_UNUSED,1.0}
    },//Extruder 1
    {
        {AXIS_UNUSED,1.0},
        {AXIS_UNUSED,1.0}
    },//Extruder 2
//    &servostock_calcForward,
    &servostock_calcInverse
};


BOOL isCartesianInterpolationDone(){
    int i;
    for(i=0;i<4;i++){
        if( isPIDInterpolating(linkToHWIndex(i))||
            !isPIDArrivedAtSetpoint(i, 10)
          ){
//            println_I("\n\nLINK not done moving index=");p_int_E(linkToHWIndex(i));
//            print_E(" isInterpolating");p_int_E(isPIDInterpolating(linkToHWIndex(i)));
//            print_E(" has arrived =");p_int_E(isPIDArrivedAtSetpoint(i, 100));
            return FALSE;
        }

    }
    return TRUE;
}

void initializeCartesianController(){
    initializeDelta();
    //getCurrentPosition(&lastXYZE[0], &lastXYZE[1], &lastXYZE[2]);
    setInterpolateXYZ(lastXYZE[0], lastXYZE[1], lastXYZE[2], 0);
    InitPacketFifo(&packetFifo,buffer,SIZE_OF_PACKET_BUFFER);
    //TODO load configuration from Flash
#if defined(CALIBRATE)
        println_I("#Calibrating...");
        setServo(linkToHWIndex(0), servoCalebrateValue,0);
        setServo(linkToHWIndex(1), servoCalebrateValue,0);
        setServo(linkToHWIndex(2), servoCalebrateValue,0);
        linkValue[0]=0;
        linkValue[1]=0;
        linkValue[2]=0;
#else
        //homingAllLinks = FALSE;
        //setPidIsr(TRUE);
        //l = getPrintLevel();
        pidReset(hwMap.Extruder0.index,0);
        pidReset(hwMap.Alpha.index,0);
        pidReset(hwMap.Beta.index,0);
        pidReset(hwMap.Gama.index,0);
#endif
    SetPID(hwMap.Heater0.index,0);
#if defined(CALIBRATE_SERVO)
    println_I("Calibrating Servo");
    runServoCalibration(EXTRUDER0_INDEX);

#endif

}

void pushBufferEmpty(){
    	LoadCorePacket(& packetTemp);
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

void loadCurrentPosition(BowlerPacket * Packet){
        LoadCorePacket(Packet);
	Packet->use.head.Method=BOWLER_STATUS;
	Packet->use.head.MessageID = 1;
	Packet->use.head.RPC = GetRPCValue("ctps");
	INT32_UNION tmp;
        tmp.Val=lastPushedBufferSize;
        Packet->use.data[0]=tmp.byte.FB;
        Packet->use.data[1]=tmp.byte.TB;
        Packet->use.data[2]=tmp.byte.SB;
        Packet->use.data[3]=tmp.byte.LB;

        tmp.Val=SIZE_OF_PACKET_BUFFER;
        Packet->use.data[4]=tmp.byte.FB;
        Packet->use.data[5]=tmp.byte.TB;
        Packet->use.data[6]=tmp.byte.SB;
        Packet->use.data[7]=tmp.byte.LB;

        Packet->use.head.DataLegnth=4+4+4;
}

void checkPositionChange(){
    int i;
    float tmp[4];
    tmp[0]=xCurrent;
    tmp[1]=yCurrent;
    tmp[2]=zCurrent;
    tmp[3] = getLinkAngle(3);
    if(     tmp[0]!=lastXYZE[0]||
            tmp[1]!=lastXYZE[1]||
            tmp[2]!=lastXYZE[2]||
            tmp[3]!=lastXYZE[3]){
        for(i=0;i<4;i++){
           lastXYZE[i] =tmp[i];
        }

//        println_I("Current Voltage of sensor");p_fl_E(getAdcVoltage(mapHeaterIndex(HEATER0_INDEX),10));
//        print_E(" Temp = ");p_fl_E(getHeaterTempreture(HEATER0_INDEX));
//        print_E(" Raw ADC = ");p_int_E(getAdcRaw(mapHeaterIndex(HEATER0_INDEX),10));

//        println_I("Current  position X=");p_fl_E(lastXYZE[0]);
//        print_E(" Y=");p_fl_E(lastXYZE[1]);
//        print_E(" Z=");p_fl_E(lastXYZE[2]);
//        print_E(" extr=");p_fl_E(lastXYZE[3]);
        INT32_UNION PID_Temp;
        LoadCorePacket(& packetTemp);
        packetTemp.use.head.DataLegnth=4;
        packetTemp.use.head.RPC = GetRPCValue("cpos");
        int i;
        for(i=0;i<4;i++){
                PID_Temp.Val=lastXYZE[i];
                packetTemp.use.data[0+(i*4)]=PID_Temp.byte.FB;
                packetTemp.use.data[1+(i*4)]=PID_Temp.byte.TB;
                packetTemp.use.data[2+(i*4)]=PID_Temp.byte.SB;
                packetTemp.use.data[3+(i*4)]=PID_Temp.byte.LB;
                packetTemp.use.head.DataLegnth+=4;
        }
        packetTemp.use.head.Method=BOWLER_ASYN;
        FixPacket(&packetTemp);
	asyncCallback(& packetTemp);
    }
}

void cartesianAsync(){
    if(RunEvery(&pid)){
        int tmp =FifoGetPacketSpaceAvailible(&packetFifo);
        if(tmp!= lastPushedBufferSize){
            lastPushedBufferSize=tmp;
            pushBufferEmpty();
            full = FALSE;
        }
        checkPositionChange();

    }
}

void processLinearInterpPacket(BowlerPacket * Packet){
    if(Packet->use.head.RPC == _SLI){
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
        float extr =tmpData[4]/extrusionScale;
        println_I("Current Extruder MM=");p_fl_E(tmpData[4]);print_I(", Ticks=");p_fl_E(extr);
        setPrintLevel(l);
        SetPIDTimed(hwMap.Extruder0.index, extr,tmpData[0]);
     }
}

BOOL onCartesianPost(BowlerPacket *Packet){
    Print_Level l = getPrintLevel();
    switch(Packet->use.head.RPC){
        case _SLI:
            if(FifoGetPacketSpaceAvailible(&packetFifo)>0){
                FifoAddPacket(&packetFifo,Packet);
                Packet->use.head.Method = BOWLER_STATUS;
                INT32_UNION tmp;
                tmp.Val=FifoGetPacketSpaceAvailible(&packetFifo);
                Packet->use.data[0]=tmp.byte.FB;
                Packet->use.data[1]=tmp.byte.TB;
                Packet->use.data[2]=tmp.byte.SB;
                Packet->use.data[3]=tmp.byte.LB;

                tmp.Val=SIZE_OF_PACKET_BUFFER;
                Packet->use.data[4]=tmp.byte.FB;
                Packet->use.data[5]=tmp.byte.TB;
                Packet->use.data[6]=tmp.byte.SB;
                Packet->use.data[7]=tmp.byte.LB;

                Packet->use.head.DataLegnth=4+4+4;
                if(tmp.Val == 0){
                    full=TRUE;
                }

                setPrintLevelInfoPrint();
                //println_I("Cached linear Packet ");p_int_I(FifoGetPacketSpaceAvailible(&packetFifo));
                setPrintLevel(l);
            }else{
                setPrintLevelInfoPrint();
                println_I("###ERROR BUFFER FULL!!");p_int_I(FifoGetPacketSpaceAvailible(&packetFifo));
                setPrintLevel(l);
                ERR(Packet,33,33);
            }
            return TRUE;
        case PRCL:
            cancelPrint();
            READY(Packet,35,35);
            return TRUE;

    }
    return FALSE;
}

void cancelPrint(){
    Print_Level l = getPrintLevel();
    setPrintLevelInfoPrint();
    println_I("Cancel Print");
    setPrintLevel(l);
    while(FifoGetPacketCount(&packetFifo)>0){
        FifoGetPacket(&packetFifo,&linTmpPack);
    }
    return;
    setInterpolateXYZ(0, 0, 112, 2000);
    ZeroPID(hwMap.Extruder0.index);
    SetPIDTimed(hwMap.Heater0.index,0,0);
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
    //println_I("Packet Checked by Cartesian Controller");
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
    if(!isCartesianInterpolationDone()){
        setXYZ( x, y, z);
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

    intCartesian[0].start=xCurrent;
    intCartesian[1].start=yCurrent;
    intCartesian[2].start=zCurrent;



    println_I("\n\nSetting new position x=");p_fl_E(x);print_E(" y=");p_fl_E(y);print_E(" z=");p_fl_E(z);print_E(" Time MS=");p_fl_E(ms);
    println_I("Current  position cx=");p_fl_E(xCurrent);
    
    print_E(" cy=");p_fl_E(yCurrent);
    print_E(" cz=");p_fl_E(zCurrent);
    //println_I("Current  angles t1=");p_fl_E(getLinkAngle(0));print_E(" t2=");p_fl_E(getLinkAngle(1));print_E(" t3=");p_fl_E(getLinkAngle(2));

    for(i=0;i<3;i++){
	intCartesian[i].setTime=ms;
	intCartesian[i].startTime=start;
    }
    if(ms==0){
        setXYZ( x,  y,  z);
    }

}

BYTE setXYZ(float x, float y, float z){
    xCurrent=x;
    yCurrent=y;
    zCurrent=z;
    float t0=0,t1=0,t2=0;
    if(hwMap.iK_callback( x,  y, z,  &t0, &t1, &t2)==0){
        println_I("New target angles t1=");p_fl_E(t0);print_E(" t2=");p_fl_E(t1);print_E(" t3=");p_fl_E(t2);
        setLinkAngle(0,t0,0);
        setLinkAngle(1,t1,0);
        setLinkAngle(2,t2,0);
    }else{
        println_E("Interpolate failed, can't reach: x=");p_fl_E(x);print_E(" y=");p_fl_E(y);print_E(" z=");p_fl_E(z);
    }
}

int linkToHWIndex(int index){
   int localIndex=0;
    switch(index){
        case 0:
            localIndex = hwMap.Alpha.index;
            break;
        case 1:
            localIndex = hwMap.Beta.index;
            break;
        case 2:
            localIndex = hwMap.Gama.index;
            break;
        case 3:
            localIndex = hwMap.Extruder0.index;
            break;
    }
    return localIndex;
}
float getLinkScale(int index){
    switch(index){
        case 0:
           return hwMap.Alpha.scale;
        case 1:
            return hwMap.Beta.scale;
        case 2:
            return hwMap.Gama.scale;
        case 3:
            return hwMap.Extruder0.scale;
    }
}


float getLinkAngle(int index){
    int localIndex=linkToHWIndex(index);
    return GetPIDPosition(localIndex)*getLinkScale(index);
}

float setLinkAngle(int index, float value, float ms){
    int localIndex=linkToHWIndex(index);
    float v = value/getLinkScale(index);
    if( index ==0||
        index ==1||
        index ==2
      ){
//        if(v>1650){
//            println_E("Upper Capped link ");p_int_E(index);print_E(", attempted: ");p_fl_E(value);
//            v=1650;
//        }
//        if(v<-6500){
//            v=-6500;
//            println_E("Lower Capped link ");p_int_E(index);print_E(", attempted: ");p_fl_E(value);
//        }
    }
    println_I("Setting position from cartesian controller");
    return SetPIDTimed(localIndex,v,ms);
}

static int homingAllLinks = FALSE;
static int linkValue[3]={0,0,0};
static RunEveryData calibrationTest ={0,1000};
void startHomingLink(int group, PidCalibrationType type);

void startHomingLinks(){
    println_I("Homing links for kinematics");

    homingAllLinks =TRUE;

    startHomingLink(linkToHWIndex(0), CALIBRARTION_home_up);
    startHomingLink(linkToHWIndex(1), CALIBRARTION_home_up);
    startHomingLink(linkToHWIndex(2), CALIBRARTION_home_up);
    println_I("Started Homing...");
}

void startHomingLink(int group, PidCalibrationType type){
    float speed=1.0;
    if(type == CALIBRARTION_home_up)
       speed*=1.0;
    else if (type == CALIBRARTION_home_down)
        speed*=-1.0;
    else{
        println_E("Invalid homing type");
        return;
    }
    SetPIDCalibrateionState(group, type);
    setOutputMine(group, speed);
    SetPIDCalibrateionState(group, CALIBRARTION_DONE);

}

void startHomingLink(int group, PidCalibrationType type){
    float speed=1.0;
    if(type == CALIBRARTION_home_up)
       speed*=1.0;
    else if (type == CALIBRARTION_home_down)
        speed*=-1.0;
    else{
        println_E("Invalid homing type");
        return;
    }
    SetPIDCalibrateionState(group, type);
    setOutputMine(group, speed);
    SetPIDCalibrateionState(group, CALIBRARTION_DONE);
}

void HomeLinks(){
    if(homingAllLinks){
        if(RunEvery(&calibrationTest)>0){
            float boundVal = 2.0;
            float l0=(float)readEncoder(linkToHWIndex(0));
            float l1=(float)readEncoder(linkToHWIndex(1));
            float l2=(float)readEncoder(linkToHWIndex(2));
            if( bound((float)linkValue[0], l0, boundVal, boundVal)&&
                bound((float)linkValue[1], l1, boundVal, boundVal)&&
                bound((float)linkValue[2], l2, boundVal, boundVal)
              ){
                homingAllLinks = FALSE;
                println_E("\n\nStopped At:\n\r\tLink 0 value:");p_int_E(l0);
                println_E("\tLink 1 value:");p_int_E(l1);
                println_E("\tLink 2 value:");p_int_E(l2);
                println_E("Previous:\n\r\tLink 0 value:");p_int_E(linkValue[0]);
                println_E("\tLink 1 value:");p_int_E(linkValue[1]);
                println_E("\tLink 2 value:");p_int_E(linkValue[2]);
                pidReset(linkToHWIndex(0),(INT32)servoHomeValue);
                pidReset(linkToHWIndex(1),(INT32)servoHomeValue);
                pidReset(linkToHWIndex(2),(INT32)servoHomeValue);
                pidReset(linkToHWIndex(3),0);
                println_E("Calibration Done!");
                setServo(linkToHWIndex(0), 128,0);
                setServo(linkToHWIndex(1), 128,0);
                setServo(linkToHWIndex(2), 128,0);
                setPidIsr(TRUE);
                initializeCartesianController();
                cancelPrint();
            }else{
                linkValue[0]=l0;
                linkValue[1]=l1;
                linkValue[2]=l2;
            }
        }
    }
}
