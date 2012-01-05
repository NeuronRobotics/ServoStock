/**
 * PID.c
 *
 *  Created on: Aug 8, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"

static AbsPID 			pidGroups[NUM_PID_GROUPS];
static DYIO_PID 		dyPid[NUM_PID_GROUPS];
static PD_VEL 			vel[NUM_PID_GROUPS];
static PidLimitEvent	limits[NUM_PID_GROUPS];
extern DATA_STRUCT DATA __attribute__ ((section (".scs_global_var")));

#define DYPID_NON_USED 0xff

float getPositionMine(int group);
void setOutputMine(int group, float val);
int resetPositionMine(int group, int target);
//void pidAsyncCallbackMine();
void onPidConfigureMine(int);
PidLimitEvent * checkPIDLimitEventsMine(BYTE group);



static RunEveryData force[NUM_PID_GROUPS];

void fail(){
	while(TRUE){
		SetColor(1,1,0);
		buttonCheck(1);
	}
}

void initPIDChans(BYTE group){

	if(dyPid[group].inputChannel==DYPID_NON_USED || dyPid[group].outputChannel==DYPID_NON_USED)
		return;

	switch(dyPid[group].inputMode & 0x7F){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		dyPid[group].inputChannel = getCounterIntChannnel( channelToCounterGroup(dyPid[group].inputChannel));
		StartCounterInput(dyPid[group].inputChannel);
	}

	println("Setting Modes for PID");
	SetCoProcMode(dyPid[group].inputChannel,dyPid[group].inputMode|0x80);
	SetCoProcMode(dyPid[group].outputChannel,dyPid[group].outputMode);
	SyncModes();

	if(dyPid[group].inputMode== IS_ANALOG_IN){
		pidGroups[group].SetPoint=GetAnalogValFromAsync(dyPid[group].inputChannel);
	}else{
		pidGroups[group].SetPoint=0;
	}
}

void InitPID(void){

	BYTE i;
	//WORD loop;
	for (i=0;i<NUM_PID_GROUPS;i++){
		//DyPID values
		dyPid[i].inputChannel=DYPID_NON_USED;
		dyPid[i].outputChannel=DYPID_NON_USED;
		dyPid[i].inputMode=0;
		dyPid[i].outputMode=0;

		pidGroups[i].Enabled=FALSE;
		pidGroups[i].channel = i;
		vel[i].enabled=FALSE;
		limits[i].type=NO_LIMIT;

		LoadPIDvals(&pidGroups[i],&dyPid[i]);
		if(		dyPid[i].inputChannel==DYPID_NON_USED ||
				dyPid[i].outputChannel==DYPID_NON_USED  ||
				dyPid[i].outputChannel==dyPid[i].inputChannel)
		{
			dyPid[i].inputChannel=DYPID_NON_USED;
			dyPid[i].outputChannel=DYPID_NON_USED;
			WritePIDvalues(&pidGroups[i],&dyPid[i]);
		}
		printPIDvals(&pidGroups[i]);
		force[i].MsTime=0;
		force[i].setPoint=200;
		if(pidGroups[i].Enabled){
			initPIDChans(i);
			println("Resetting PID channel from init");
			ZeroPID(i);
		}

		pidGroups[i].Enabled=FALSE;
	}

	InitilizePidController( pidGroups,
							vel,
							NUM_PID_GROUPS,
							&getPositionMine,
							&setOutputMine,
							&resetPositionMine,
							&PutBowlerPacket,
							&onPidConfigureMine,
							&checkPIDLimitEventsMine);

}

void GetConfigDyPID(BowlerPacket * Packet){
	BYTE chan = Packet->use.data[0];
	Packet->use.data[1]=dyPid[chan].inputChannel;// =Packet->use.data[1];
	Packet->use.data[2]=dyPid[chan].inputMode ;//Packet->use.data[2];
	Packet->use.data[3]=dyPid[chan].outputChannel;//Packet->use.data[3];
	Packet->use.data[4]=dyPid[chan].outputMode;//Packet->use.data[4];
	Packet->use.head.DataLegnth=4+5;
	Packet->use.head.Method=BOWLER_POST;

}
BYTE ConfigDyPID(BowlerPacket * Packet){
	BYTE chan = Packet->use.data[0];
	dyPid[chan].inputChannel =Packet->use.data[1];
	dyPid[chan].inputMode =Packet->use.data[2];
	dyPid[chan].outputChannel =Packet->use.data[3];
	dyPid[chan].outputMode =Packet->use.data[4];

	initPIDChans(chan);

	WritePIDvalues(&pidGroups[chan],&dyPid[chan]);
	return TRUE;
}



BYTE GetPIDGroup(BYTE channel){
	BYTE mode = GetChannelMode(channel);
	BYTE i;
	switch(mode){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
	case IS_ANALOG_IN:
		for(i=0;i<NUM_PID_GROUPS;i++){
			if(dyPid[i].inputChannel == channel){
				if(pidGroups[i].Enabled || vel[i].enabled )
					return i;
			}
		}
		break;
	case IS_SERVO:
	case IS_DC_MOTOR_DIR:
	case IS_DC_MOTOR_VEL:
	case IS_PWM:
		for(i=0;i<NUM_PID_GROUPS;i++){
			if(dyPid[i].outputChannel == channel){
				if(pidGroups[i].Enabled || vel[i].enabled)
					return i;
			}
		}
		break;
	default:
		break;
	}
	return NOT_USED_IN_PID;
}

void onPidConfigureMine(int group){
	WritePIDvalues(&pidGroups[group],&dyPid[group]);
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
	if(dyPid[group].inputChannel==DYPID_NON_USED)
			return current;
	if(dyPid[group].inputMode == IS_COUNTER_INPUT_INT){
		SetCounterInput(dyPid[group].inputChannel,current);
	}else if(dyPid[group].inputMode == IS_ANALOG_IN){
		current=GetAnalogValFromAsync(dyPid[group].inputChannel);
	}
	return current;
}

float getPositionMine(int group){
	if(dyPid[group].inputChannel==DYPID_NON_USED||
			((pidGroups[group].Enabled == FALSE) && (vel[group].enabled==FALSE)))
		return 0;

	LONG pos = 0;
	//print("\nGetting PID value from group: ");p_ul(chan->channel);print(" of mode: ");printMode(chan->inputMode);print(" From channel: ");p_ul(chan->inputChannel);print("\n");
	switch(dyPid[group].inputMode){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		pos=GetCounterByChannel( dyPid[group].inputChannel );
		break;
	case IS_ANALOG_IN:
		pos=GetAnalogValFromAsync(dyPid[group].inputChannel);
		break;
	}
	return ((float)pos);
}

void setOutputMine(int group, float val){
	if( dyPid[group].outputChannel==DYPID_NON_USED||
			((pidGroups[group].Enabled == FALSE) && (vel[group].enabled==FALSE)))
		return;

	BYTE center = DATA.PIN[dyPid[group].outputChannel].ServoPos;
	val*=(pidGroups[group].Polarity)?1:-1;
	val += center;
	if (val>190.0)
		val=190.0;
	if(val<25.0)
		val=25.0;
	int set = (int)val;
	if (dyPid[group].outVal==set){
		//if(!(RunEvery(&force[chan->channel])>0))
			return;
	}else{
		print(" Setting PID output, was ");p_sl(dyPid[group].outVal);print(" is now: ");p_sl(set);print(" on DyIO chan: ");p_sl(dyPid[group].outputChannel);print(", ");
	}
	dyPid[group].outVal=set;
	SetChannelValueCoProc(dyPid[group].outputChannel,dyPid[group].outVal);
}


