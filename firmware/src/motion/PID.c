#include "main.h"



static AbsPID 			pidGroups[numPidTotal];
static PD_VEL 			vel[numPidTotal];
static PidLimitEvent            limits[numPidTotal];



float getPositionMine(int group);
void setOutputMine(int group, float val);
int resetPositionMine(int group, int target);

void onPidConfigureMine(int);
PidLimitEvent * checkPIDLimitEventsMine(BYTE group);

void initPIDLocal(){
   	BYTE i;
	//WORD loop;
	for (i=0;i<numPidTotal;i++){
            vel[i].enabled=FALSE;
            limits[i].type=NO_LIMIT;
	}
	InitilizePidController( pidGroups,
                                vel,
                                numPidTotal,
                                &getPositionMine,
                                &setOutputMine,
                                &resetPositionMine,
                                //&asyncCallback,
                                &onPidConfigureMine,
                                &checkPIDLimitEventsMine);
        while(!initFlashLocal());


       setPidIsr(TRUE);

}

BOOL runPidIsr = FALSE;

BOOL getRunPidIsr(){
    return runPidIsr;
}

void setPidIsr(BOOL v){
    runPidIsr=v;
}


BOOL asyncCallback(BowlerPacket *Packet){
    //println_I("Async>>");printPacket(Packet,INFO_PRINT);
    PutBowlerPacket(Packet);// This only works with USB and UART
    return isUSBActave();
}

void onPidConfigureMine(int group){
    writeFlashLocal();
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
    println_I("Resetting PID Local ");p_int_I(group);print_I(" to ");p_int_I(current);print_I(" from ");p_fl_I(getPositionMine(group));
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
        if(pidGroups[group].config.Enabled || vel[group].enabled)
            val = readEncoder(group);
    }else{
        val = getHeaterTempreture(group);
    }

    return val;
}

void setOutputMine(int group, float v){
    if(group<numPidMotors){
        int val = (int)(v);

        val+=127;// center for servos

        if (val>255)
                val=255;
        if(val<0)
                val=0;
        
//        if(group == EXTRUDER0_INDEX && !isUpToTempreture()){
//            //Saftey so as not to try to feed into a cold extruder
//            setServo(group,getServoStop(group),0);
//            return;
//        }

        setServo(group,val,0);
    }else{
       setHeater( group,  v);
    }
}

BOOL isUpToTempreture(){
    return TRUE;
//   return bound(pidGroups[HEATER0_INDEX].SetPoint,
//           getHeaterTempreture(HEATER0_INDEX),
//           25,
//           25)&& pidGroups[HEATER0_INDEX].SetPoint>100;
}
