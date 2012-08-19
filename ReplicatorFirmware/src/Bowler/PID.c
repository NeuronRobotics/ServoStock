#include "main.h"


static AbsPID 			pidGroups[numPidMotor];
static PD_VEL 			vel[numPidMotor];
static PidLimitEvent            limits[numPidMotor];


float getPositionMine(int group);
void setOutputMine(int group, float val);
int resetPositionMine(int group, int target);
BOOL asyncCallback(BowlerPacket *Packet);
void onPidConfigureMine(int);
PidLimitEvent * checkPIDLimitEventsMine(BYTE group);

void initPIDLocal(){
   	BYTE i;
	//WORD loop;
	for (i=0;i<numPidMotor;i++){
		pidGroups[i].Enabled=FALSE;
		pidGroups[i].channel = i;
                pidGroups[i].K.P=.1;
                pidGroups[i].K.I=2;
                pidGroups[i].K.D=0;
                pidGroups[i].Polarity=1;
		vel[i].enabled=FALSE;
		limits[i].type=NO_LIMIT;
                if(i==LINK0_INDEX || i== LINK1_INDEX || i== LINK2_INDEX){
                  pidGroups[i].Polarity=0;
                  pidGroups[i].Enabled=TRUE;
                }
	}



	InitilizePidController( pidGroups,
                                vel,
                                numPidMotor,
                                &getPositionMine,
                                &setOutputMine,
                                &resetPositionMine,
                                &asyncCallback,
                                &onPidConfigureMine,
                                &checkPIDLimitEventsMine);
       for (i=0;i<numPidMotor;i++){
           if(i==LINK0_INDEX || i== LINK1_INDEX || i== LINK2_INDEX)
             SetPID(i,readEncoder(i));
       }

}


BOOL asyncCallback(BowlerPacket *Packet){
    PutBowlerPacket(Packet);// This only works with USB and UART
    return isUSBActave();
}

void onPidConfigureMine(int group){
    //do nothing
}

void trigerPIDLimit(BYTE chan,PidLimitType type,INT32  tick){
	limits[chan].group=chan;
	limits[chan].type=type;
	limits[chan].value=tick;
	limits[chan].time=getMs();
}

PidLimitEvent * checkPIDLimitEventsMine(BYTE group){
	return & limits[group];
}


int resetPositionMine(int group, int current){
    setCurrentValue(group, current);
    return readEncoder(group);
}

float getPositionMine(int group){
	return readEncoder(group);
}

void setOutputMine(int group, float v){
	int val = (int)(v);
        val += 126;
        if (val>255)
                val=255;
        if(val<0)
                val=0;
	
	int set = (int)val;
        setServo(group,set,0);

}