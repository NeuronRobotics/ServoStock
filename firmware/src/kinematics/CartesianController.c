#include "main.h"
#if defined(__32MX795F512L__)
    #define SIZE_OF_PACKET_BUFFER 400
#elif defined(__32MX440F128H__)
    #define SIZE_OF_PACKET_BUFFER 60
#endif

void updateCurrentPositions();
float getLinkScale(int index);

static int homingAllLinks = FALSE;

PACKET_FIFO_STORAGE  packetFifo;
BowlerPacket buffer[SIZE_OF_PACKET_BUFFER];
BowlerPacket linTmpPack;
BowlerPacket packetTemp;
INTERPOLATE_DATA intCartesian[3];

//float scale = -1.0*mmPerTick;
float extrusionScale = 1/(((float)ticksPerRev)/100.00);

float xCurrent,yCurrent,zCurrent,eCurrent;
BOOL full = FALSE;
BOOL configured=FALSE;


int  lastPushedBufferSize =0;
float lastXYZE[4];

static RunEveryData pid ={0,500};

static BOOL keepCartesianPosition =FALSE;
int interpolationCounter=0;
BOOL runKinematics=FALSE;


//Default values for ServoStock
//HardwareMap hwMap ={
//    {0,-1.0*mmPerTick ,"Alpha"},//axis 0
//    {1,-1.0*mmPerTick ,"Beta"},//axis 1
//    {2,-1.0*mmPerTick ,"Gama"},//axis 2
//    {
//        {3,1.0,"Extruder"},// Motor
//        {11,1.0,"Heater"}// Heater
//    },//Extruder 0
//    {
//        {AXIS_UNUSED,1.0,""},
//        {AXIS_UNUSED,1.0,""}
//    },//Extruder 1
//    {
//        {AXIS_UNUSED,1.0,""},
//        {AXIS_UNUSED,1.0,""}
//    },//Extruder 2
//    (forwardKinematics *)&servostock_calcForward,
//    (inverseKinematics *)&servostock_calcInverse
//};

//Default values for ServoStock
HardwareMap hwMap ={
    {0,1.0/ticksPerDegree ,"left"},//axis 0
    {1,-1.0/ticksPerDegree ,"right"},//axis 1
    {2,-1.0/ticksPerDegree ,"tilt"},//axis 2
    {
        {7,1.0,"Extruder"},// Motor
        {11,1.0,"Heater"}// Heater
    },//Extruder 0
    {
        {AXIS_UNUSED,1.0,""},
        {AXIS_UNUSED,1.0,""}
    },//Extruder 1
    {
        {AXIS_UNUSED,1.0,""},
        {AXIS_UNUSED,1.0,""}
    },//Extruder 2
    (forwardKinematics *)&frog_calcForward,
    (inverseKinematics *)&frog_calcInverse
};

char * getName(int index){
    switch(index){
        case 0:
           return hwMap.Alpha.name;
        case 1:
            return hwMap.Beta.name;
        case 2:
            return hwMap.Gama.name;
        case 3:
            return hwMap.Extruder0.name;
        case 4:
            return hwMap.Heater0.name;
    }
}

BOOL onRunKinematicsSet(BowlerPacket *Packet){
    runKinematics=Packet->use.data[0];// Boolean to run the kinematics or not
}


BOOL onConfigurationGet(BowlerPacket *Packet){
    Packet->use.head.DataLegnth=4;
    BYTE index=  Packet->use.data[0];// joint space requested index

    Packet->use.data[0] = linkToHWIndex(index);// the PID link maped
    Packet->use.head.DataLegnth++;
    Packet->use.data[1] = 5;// 5 active axis
    Packet->use.head.DataLegnth++;
    set32bit(Packet,getPidGroupDataTable()[Packet->use.data[0]].config.IndexLatchValue,2);
    Packet->use.head.DataLegnth+=4;
    set32bit(Packet,-100000,6);
    Packet->use.head.DataLegnth+=4;
    set32bit(Packet,100000,10);
    Packet->use.head.DataLegnth+=4;
    set32bit(Packet,getLinkScale(index)*1000,14);
    Packet->use.head.DataLegnth+=4;

    int i=0;
    int offset=Packet->use.head.DataLegnth-4;
    while(getName(index)[i]){
       Packet->use.data[offset+i]=getName(index)[i];
       i++;
       Packet->use.head.DataLegnth++;
    }
    Packet->use.data[offset+i]=0;
    Packet->use.head.DataLegnth++;
    return TRUE;

}

BOOL isCartesianInterpolationDone(){
    updateCurrentPositions();
    float targets[3] = {xCurrent,yCurrent,zCurrent};
    int setpointBound = 200;
    float mmPositionResolution = 10;
    int i;
    for(i=0;i<4;i++){
        if(i<3){
            if(!bound(intCartesian[i].set,targets[i],mmPositionResolution,mmPositionResolution)){
                //println_W("Interpolation not done on to: ");p_fl_W(intCartesian[i].set);print_W(" is = ");p_fl_W(targets[i]);
                return FALSE;
            }
        }
        if( (isPIDArrivedAtSetpoint(linkToHWIndex(i), setpointBound) == FALSE) && (i==3) ){
            println_W("LINK not done moving index = ");p_int_W(linkToHWIndex(i));
            print_W(" currently is = ");    p_fl_W(getPidGroupDataTable()[linkToHWIndex(i)].CurrentState);
            print_W(" heading towards = "); p_fl_W(getPidGroupDataTable()[linkToHWIndex(i)].SetPoint);
            return FALSE;
        }

    }
    return TRUE;
}

void initializeCartesianController(){
    InitPacketFifo(&packetFifo,buffer,SIZE_OF_PACKET_BUFFER);
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

void updateCurrentPositions(){
        if(hwMap.fK_callback(
                                getLinkAngle(0),
                                getLinkAngle(1),
                                getLinkAngle(2),
                                &xCurrent,
                                &yCurrent,
                                &zCurrent)!=0){
        println_E("Inverse Failed!!")  ;
        return;
    }
}

void checkPositionChange(){
    int i;
    float tmp[4];
    updateCurrentPositions();

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
        if(runKinematics){
            //checkPositionChange();
        }

    }
}

void processLinearInterpPacket(BowlerPacket * Packet){
    if(Packet->use.head.RPC == _SLI){
        //INT32_UNION tmp;
        float tmpData [5];
        int i;

        tmpData[0] = ((float)get32bit(Packet,1));
        for(i=1;i<5;i++){

            tmpData[i] = ((float)get32bit(Packet,(i*4)+1))/1000;
        }
        setInterpolateXYZ(tmpData[1], tmpData[2], tmpData[3],tmpData[0]);
        float extr =tmpData[4]/extrusionScale;
        //println_I("Current Extruder MM=");p_fl_W(tmpData[4]);print_I(", Ticks=");p_fl_W(extr)
        SetPIDTimed(hwMap.Extruder0.index, extr,tmpData[0]);
     }
}

BOOL onClearPrinter(BowlerPacket *Packet){
    Print_Level l =getPrintLevel();
    setPrintLevelInfoPrint();
    cancelPrint();
    READY(Packet,35,35);
    setPrintLevel(l);
    return TRUE;
}

BOOL onCartesianPost(BowlerPacket *Packet){

            if(FifoGetPacketSpaceAvailible(&packetFifo)>0){
                if(Packet->use.data[0]==1){
                    processLinearInterpPacket(Packet);
                }else{
                    println_I("Cached linear Packet ");p_int_I(FifoGetPacketSpaceAvailible(&packetFifo));
                    FifoAddPacket(&packetFifo,Packet);
                }
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

            }else{
                println_I("###ERROR BUFFER FULL!!");p_int_I(FifoGetPacketSpaceAvailible(&packetFifo));

                ERR(Packet,33,33);
            }
            return TRUE;
}

void cancelPrint(){
    Print_Level l = getPrintLevel();

    println_W("Cancel Print");
    setPrintLevel(l);
    InitPacketFifo(&packetFifo,buffer,SIZE_OF_PACKET_BUFFER);
    //setInterpolateXYZ(0, 0, getmaxZ(), 0);
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

void printCartesianData(){
updateCurrentPositions();
   println_W("Current  position cx=");p_fl_W(xCurrent);

    print_W(" cy=");p_fl_W(yCurrent);
    print_W(" cz=");p_fl_W(zCurrent);
    println_W("Current  angles Alpha=");p_fl_W(getLinkAngle(0));
    print_W(" Beta=");p_fl_W(getLinkAngle(1));
    print_W(" Gamma=");p_fl_W(getLinkAngle(2));

    println_W("Raw  angles Alpha=");p_fl_W(getLinkAngleNoScale(0));
    print_W(" Beta=");p_fl_W(getLinkAngleNoScale(1));
    print_W(" Gamma=");p_fl_W(getLinkAngleNoScale(2));

}

void interpolateZXY(){

    interpolationCounter=0;
    if(!configured){
        HomeLinks();
        return;
    }
    if(!runKinematics){
        return;
    }
    keepCartesianPosition=TRUE;
    if(keepCartesianPosition){
        float x=0,y=0,z=0;
        float ms= getMs();

        x = interpolate((INTERPOLATE_DATA *)&intCartesian[0],ms);
        y = interpolate((INTERPOLATE_DATA *)&intCartesian[1],ms);
        z = interpolate((INTERPOLATE_DATA *)&intCartesian[2],ms);
        if(isCartesianInterpolationDone() == FALSE){
            println_W("Start Time=");p_fl_W(ms);
            println_W("Interp \r\n\tx=");p_fl_W(x);print_W(" \tc=");p_fl_W(xCurrent);   print_W(" \tT=");p_fl_W(intCartesian[0].setTime);print_W(" \tElapsed=");p_fl_W(ms-intCartesian[0].startTime);

            print_W("\r\n\ty=");p_fl_W(y);print_W(" \tc=");p_fl_W(yCurrent);                print_W(" \tT=");p_fl_W(intCartesian[1].setTime);print_W(" \tElapsed=");p_fl_W(ms-intCartesian[1].startTime);

            print_W("\r\n\tz=");p_fl_W(z);print_W(" \tc=");p_fl_W(zCurrent);                print_W(" \tT=");p_fl_W(intCartesian[2].setTime);print_W(" \tElapsed=");p_fl_W(ms-intCartesian[2].startTime);


            setXYZ( x, y, z, 0);
        }else{
            if( FifoGetPacketCount(&packetFifo)>0){
                println_W("Loading new packet ");
                if(FifoGetPacket(&packetFifo,&linTmpPack)){
                    processLinearInterpPacket(&linTmpPack);
                }
            }else{
                keepCartesianPosition=FALSE;
            }
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
    updateCurrentPositions();
    intCartesian[0].start=xCurrent;
    intCartesian[1].start=yCurrent;
    intCartesian[2].start=zCurrent;



    println_W("\n\nSetting new position x=");p_fl_W(x);print_W(" y=");p_fl_W(y);print_W(" z=");p_fl_W(z);print_W(" Time MS=");p_fl_W(ms);
    println_W("Current  position cx=");p_fl_W(xCurrent);
    
    print_W(" cy=");p_fl_W(yCurrent);
    print_W(" cz=");p_fl_W(zCurrent);
    println_W("Current  angles Alpha=");p_fl_W(getLinkAngle(0));print_W(" Beta=");p_fl_W(getLinkAngle(1));print_W(" Gamma=");p_fl_W(getLinkAngle(2));
    runKinematics=TRUE;
    for(i=0;i<3;i++){
	intCartesian[i].setTime=ms;
	intCartesian[i].startTime=start;
    }
    if(ms==0){
        setXYZ( x,  y,  z,0);
    }else{
        keepCartesianPosition=TRUE;
        start=getMs();
        x = interpolate((INTERPOLATE_DATA *)&intCartesian[0],start);
        y = interpolate((INTERPOLATE_DATA *)&intCartesian[1],start);
        z = interpolate((INTERPOLATE_DATA *)&intCartesian[2],start);
        setXYZ( x,  y,  z,0);
    }

}

BYTE setXYZ(float x, float y, float z,float ms){
    updateCurrentPositions();
    float t0=0,t1=0,t2=0;
    if(hwMap.iK_callback( x,  y, z,  &t0, &t1, &t2)==0){
        println_I("New target angles t1=");p_fl_I(t0);print_I(" t2=");p_fl_I(t1);print_I(" t3=");p_fl_I(t2);
        setLinkAngle(0,t0,ms);
        setLinkAngle(1,t1,ms);
        setLinkAngle(2,t2,ms);
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
        case 4:
            localIndex = hwMap.Heater0.index;
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
        case 4:
            return hwMap.Heater0.scale;
    }
}
float getLinkAngleNoScale(int index){
    int localIndex=linkToHWIndex(index);
    return GetPIDPosition(localIndex);
}

float getLinkAngle(int index){

    return getLinkAngleNoScale(index)*getLinkScale(index);
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
    println_I("Setting position from cartesian controller ");p_int_I(index);print_I(" to ");p_fl_I(v);
    return SetPIDTimed(localIndex,v,ms);
}


void startHomingLinks(){
    println_W("Homing links for kinematics");

    homingAllLinks =TRUE;

    startHomingLink(linkToHWIndex(0), CALIBRARTION_home_down);
    startHomingLink(linkToHWIndex(1), CALIBRARTION_home_down);
    startHomingLink(linkToHWIndex(2), CALIBRARTION_home_down);
    println_W("Started Homing...");
}

void HomeLinks(){
    if(homingAllLinks){
       if ( GetPIDCalibrateionState(linkToHWIndex(0))==CALIBRARTION_DONE&&
            GetPIDCalibrateionState(linkToHWIndex(1))==CALIBRARTION_DONE&&
            GetPIDCalibrateionState(linkToHWIndex(2))==CALIBRARTION_DONE
               ){
          homingAllLinks = FALSE;
          configured = TRUE;
          println_W("All linkes reported in");
          pidReset(hwMap.Extruder0.index,0);
          int i;
          float Alpha,Beta,Gama;
          servostock_calcInverse(0, 0, getmaxZ(), &Alpha, &Beta, &Gama);
          for(i=0;i<3;i++){
             pidReset(linkToHWIndex(i), (Alpha+getRodLength()/3)/getLinkScale(i));
              //pidReset(linkToHWIndex(i), 0);
          }
          initializeCartesianController();
          cancelPrint();
       }


    }
}
