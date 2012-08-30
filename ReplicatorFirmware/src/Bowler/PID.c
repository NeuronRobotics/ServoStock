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
                pidGroups[i].K.P=.07;
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
       setPidIsr(FALSE);
}

BOOL runPidIsr = FALSE;

BOOL getRunPidIsr(){
    return runPidIsr;
}

void setPidIsr(BOOL v){
    runPidIsr=v;
    if(runPidIsr){
        OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, 358*5);
        ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_4);
        Print_Level l = getPrintLevel();
        setPrintLevelInfoPrint();
        println_I("Starting PID ISR");
        setPrintLevel(l);
    }else{
        CloseTimer3();
        Print_Level l = getPrintLevel();
        setPrintLevelInfoPrint();
        println_I("Closing PID ISR");
        setPrintLevel(l);
    }
}

void __ISR(_TIMER_3_VECTOR, ipl4) Timer3Handler(void){
    if(getRunPidIsr()){
        Print_Level l = getPrintLevel();
        setPrintLevelNoPrint();
        RunPIDControl();
        setPrintLevel(l);
    }
    mT3ClearIntFlag();
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
    println_I("Resetting PID Local");
    setCurrentValue(group, current);
    return readEncoder(group);
}

float getPositionMine(int group){
	return readEncoder(group);
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