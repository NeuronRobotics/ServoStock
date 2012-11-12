#include "main.h"

INTERPOLATE_DATA intCartesian[3];

float scale = -1/(ticksPerDegree*gearRatio);

BYTE setXYZ(float x, float y, float z);
void interpolateZXY();
float getLinkAngle(int index);
float setLinkAngle(int index, float value);

BOOL done = FALSE;

void initializeCartesianController(){
    initializeDelta();
    float cx=0,cy=0,cz=0;
    getCurrentPosition(&cx, &cy, &cz);
    setInterpolateXYZ(cx, cy, cz, 0);
}


void interpolateZXY(){
    float x=0,y=0,z=0;
    float ms= getMs();
    x = interpolate((INTERPOLATE_DATA *)&intCartesian[0],ms);
    y = interpolate((INTERPOLATE_DATA *)&intCartesian[1],ms);
    z = interpolate((INTERPOLATE_DATA *)&intCartesian[2],ms);
    BOOL move = FALSE;
    int i;
    for(i=0;i<3;i++){
        if(move==FALSE && intCartesian[i].setTime > 0){
            move = TRUE;
            done = FALSE;
        }
    }
    if(move){
       setXYZ( x, y, z);
    }else{
        if(done == FALSE){
            done = TRUE;
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
    println_I("\n\nSetting new position x=");p_fl_E(x);print_E(" y=");p_fl_E(y);print_E(" z=");p_fl_E(z);
    println_I("Current  position cx=");p_fl_E(cx);print_E(" cy=");p_fl_E(cy);print_E(" cz=");p_fl_E(cz);
    println_I("Current  angles t1=");p_fl_E(getLinkAngle(0));print_E(" t2=");p_fl_E(getLinkAngle(1));print_E(" t3=");p_fl_E(getLinkAngle(2));

    for(i=0;i<3;i++){
	intCartesian[i].setTime=ms;
	
	intCartesian[i].startTime=start;
    }
    if(ms==0){
        setXYZ( x,  y,  z);
    }
}

BYTE setXYZ(float x, float y, float z){
    float t0=0,t1=0,t2=0;
    if(delta_calcInverse( x,  y, z,  &t0, &t1, &t2)==0){
        //println_I("New target angles t1=");p_fl_E(t0);print_E(" t2=");p_fl_E(t1);print_E(" t3=");p_fl_E(t2);
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