#include "main.h"


static AbsPID 			pidGroups[NUM_PID_GROUPS];
static PD_VEL 			vel[NUM_PID_GROUPS];
static PidLimitEvent            limits[NUM_PID_GROUPS];


float getPositionMine(int group);
void setOutputMine(int group, float val);
int resetPositionMine(int group, int target);
BOOL asyncCallback(BowlerPacket *Packet);
void onPidConfigureMine(int);
PidLimitEvent * checkPIDLimitEventsMine(BYTE group);

void initPIDLocal(){
   	BYTE i;
	//WORD loop;
	for (i=0;i<NUM_PID_GROUPS;i++){
		pidGroups[i].Enabled=1;
		pidGroups[i].channel = i;
                pidGroups[i].K.P=1.1;
                pidGroups[i].K.I=0;
                pidGroups[i].K.D=0;
                pidGroups[i].Polarity=1;

		vel[i].enabled=FALSE;
		limits[i].type=NO_LIMIT;
	}

	InitilizePidController( pidGroups,
							vel,
							NUM_PID_GROUPS,
							&getPositionMine,
							&setOutputMine,
							&resetPositionMine,
							&asyncCallback,
							&onPidConfigureMine,
							&checkPIDLimitEventsMine);
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
	LONG pos = AS5055readAngle(group);
	return ((float)pos);
}

void setOutputMine(int group, float v){
	Print_Level l = getPrintLevel();
	setPrintLevelNoPrint();
	int val = (int)(v);


        val += 128;
        if (val>255)
                val=255;
        if(val<0)
                val=0;
	
	int set = (int)val;


        setServo(group,set,0);
	setPrintLevel(l);
}