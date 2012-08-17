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
		pidGroups[i].Enabled=TRUE;
		pidGroups[i].channel = i;
                pidGroups[i].K.P=.01;
                pidGroups[i].K.I=10;
                pidGroups[i].K.D=.1;
                pidGroups[i].Polarity=1;
		vel[i].enabled=FALSE;
		limits[i].type=NO_LIMIT;
                if(i==LINK0_INDEX || i== LINK1_INDEX || i== LINK2_INDEX){
                  pidGroups[i].Polarity=0;
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
           printPIDvals(i);
       }
       println_I("Break");
       for (i=0;i<numPidMotor;i++){
           SetPID(i,readEncoder(i));
       }
       for (i=0;i<numPidMotor;i++){
           printPIDvals(i);
       }
}


BOOL asyncCallback(BowlerPacket *Packet){
    PutBowlerPacket(Packet);// This only works with USB and UART
    return TRUE;
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

	return current;
}

float getPositionMine(int group){
	LONG pos = readEncoder(group);
	return ((float)pos);
}

void setOutputMine(int group, float v){
	int val = (int)(v);
        val += 128;
        if (val>255)
                val=255;
        if(val<0)
                val=0;
	
	int set = (int)val;
        setServo(group,set,0);

}