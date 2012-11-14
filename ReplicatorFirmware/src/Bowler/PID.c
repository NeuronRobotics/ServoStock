#include "main.h"


static AbsPID 			pidGroups[numPidTotal];
static PD_VEL 			vel[numPidTotal];
static PidLimitEvent            limits[numPidTotal];


float getPositionMine(int group);
void setOutputMine(int group, float val);
int resetPositionMine(int group, int target);
BOOL asyncCallback(BowlerPacket *Packet);
void onPidConfigureMine(int);
PidLimitEvent * checkPIDLimitEventsMine(BYTE group);

void initPIDLocal(){
   	BYTE i;
	//WORD loop;
	for (i=0;i<numPidTotal;i++){
		pidGroups[i].Enabled=FALSE;
		pidGroups[i].channel = i;
                pidGroups[i].K.P=.1;
                pidGroups[i].K.I=0;
                pidGroups[i].K.D=0;
                pidGroups[i].Polarity=1;
		vel[i].enabled=FALSE;
		limits[i].type=NO_LIMIT;
                if(i==LINK0_INDEX || i== LINK1_INDEX || i== LINK2_INDEX){
                    pidGroups[i].Polarity=0;
                    pidGroups[i].K.P=.03;
                    pidGroups[i].K.I=0.0;
                    pidGroups[i].K.D=0.03;
                }
                if(i==EXTRUDER0_INDEX){
                    pidGroups[i].K.P=.1;
                    pidGroups[i].K.I=0;
                    pidGroups[i].K.D=0;
                    pidGroups[i].Polarity=1;
                }
                if(i>=numPidMotors){
                    //These are the PID gains for the tempreture system
                    pidGroups[i].K.P=10;
                    pidGroups[i].K.I=0;
                    pidGroups[i].K.D=0;
                    pidGroups[i].Polarity=1;
                }
                if(i==HEATER0_INDEX){
                    pidGroups[i].K.P=10;
                    pidGroups[i].K.I=0;
                    pidGroups[i].K.D=0;
                    pidGroups[i].Polarity=1;
                }

	}

	InitilizePidController( pidGroups,
                                vel,
                                numPidTotal,
                                &getPositionMine,
                                &setOutputMine,
                                &resetPositionMine,
                                &asyncCallback,
                                &onPidConfigureMine,
                                &checkPIDLimitEventsMine); 
       setPidIsr(FALSE);

}

BOOL runPidIsr = FALSE;

BOOL getRunPidIsr(){
    return runPidIsr;
}

void setPidIsr(BOOL v){
    runPidIsr=v;
}




BOOL asyncCallback(BowlerPacket *Packet){
    PutBowlerPacket(Packet);// This only works with USB and UART
    return isUSBActave();
}

void onPidConfigureMine(int group){
    if(group==LINK0_INDEX || group== LINK1_INDEX || group== LINK2_INDEX){
        //Synchronized gains for all 3 links, needed for stability
        float p = pidGroups[group].K.P;
        float i = pidGroups[group].K.I;
        float d = pidGroups[group].K.D;
        setPIDConstants(LINK0_INDEX,p,i,d);
        setPIDConstants(LINK1_INDEX,p,i,d);
        setPIDConstants(LINK2_INDEX,p,i,d);
    }
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
    println_I("Resetting PID Local ");p_ul_I(group);print_I(" to ");p_ul_I(current);print_I(" from ");p_fl_I(getPositionMine(group));
    if(group<numPidMotors){
        setCurrentValue(group, current);
    }else{
        resetHeater(group, current);
    }
    return getPositionMine(group);
}

float getPositionMine(int group){
    float val=0;
    if(group<numPidMotors){
        val = readEncoder(group);
    }else{
        val = getHeaterTempreture(group);
    }

    return val;
}

void setOutputMine(int group, float v){
    if(group<numPidMotors){
        int val = (int)(v);
        val += 128;
        if (val>200)
                val=200;
        if(val<50)
                val=50;

	int set = (int)val;

        setServo(group,set,0);
    }else{
       setHeater( group,  v);
    }
}