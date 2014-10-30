#include "main.h"

//static PD_VEL vel[numPidTotal];
static PidLimitEvent limits[numPidTotal];

static AbsPID pidGroupsLocal[numPidTotal];

float getPositionMine(int group);
void setOutputMine(int group, float val);
int resetPositionMine(int group, int target);

void onPidConfigureMine(int);
PidLimitEvent * checkPIDLimitEventsMine(uint8_t group);

void initPIDLocal() {
    setPidIsr(false);
    uint8_t i;
    //uint16_t loop;
    for (i = 0; i < numPidTotal; i++) {
        println_I("Loading PID ");p_int_I(i);
        pidGroupsLocal[i].vel.enabled = false;
        limits[i].type = NO_LIMIT;
        pidGroupsLocal[i].config.Enabled = false;
        pidGroupsLocal[i].config.Async = 0;
        pidGroupsLocal[i].config.IndexLatchValue = 0;
        pidGroupsLocal[i].config.stopOnIndex = 0;
        pidGroupsLocal[i].config.useIndexLatch = 0;
        pidGroupsLocal[i].config.K.P = .1;
        pidGroupsLocal[i].config.K.I = 0;
        pidGroupsLocal[i].config.K.D = 0;
        pidGroupsLocal[i].config.V.P = .1;
        pidGroupsLocal[i].config.V.D = 0;
        pidGroupsLocal[i].config.Polarity = 1;
        pidGroupsLocal[i].config.stop = 0;
        pidGroupsLocal[i].config.upperHistoresis = 0;
        pidGroupsLocal[i].config.lowerHistoresis = 0;
        pidGroupsLocal[i].config.offset = 0.0;
        pidGroupsLocal[i].config.calibrationState = CALIBRARTION_Uncalibrated;
        pidGroupsLocal[i].interpolate.set=0;
        pidGroupsLocal[i].interpolate.setTime=0;
        pidGroupsLocal[i].interpolate.start=0;
        pidGroupsLocal[i].interpolate.startTime=0;
        println_I("Interpolation check ");
        interpolate(&pidGroupsLocal[i].interpolate,getMs());
    }

    InitilizePidController(pidGroupsLocal,
            numPidTotal,
            &getPositionMine,
            &setOutputMine,
            &resetPositionMine,
            &onPidConfigureMine,
            &checkPIDLimitEventsMine);
    while (!initFlashLocal());
    setPidIsr(true);
}

boolean runPidIsr = false;

boolean getRunPidIsr() {
    return runPidIsr;
}

void setPidIsr(boolean v) {
    runPidIsr = v;
}

boolean asyncCallback(BowlerPacket *Packet) {
    //println_I("Async>>");printPacket(Packet,INFO_PRINT);
    PutBowlerPacket(Packet); // This only works with USB and UART
    return isUSBActave();
}

void onPidConfigureMine(int group) {
    writeFlashLocal();
}

void trigerPIDLimit(uint8_t chan, PidLimitType type, int32_t tick) {
    limits[chan].group = chan;
    limits[chan].type = type;
    limits[chan].value = tick;
    limits[chan].time = getMs();
}

PidLimitEvent * checkPIDLimitEventsMine(uint8_t group) {
    return & limits[group];
}

int resetPositionMine(int group, int current) {
    println_I("Resetting PID Local ");
    p_int_I(group);
    print_I(" to ");
    p_int_I(current);
    print_I(" from ");
    p_fl_I(getPositionMine(group));
    if (group < numPidMotors) {
        //setCurrentValue(group, current);
    } else {
        //resetHeater(group, current);
    }
    return getPositionMine(group);
}

float getPositionMine(int group) {
    float val = 0;
    if (group < numPidMotors) {
        //if(pidGroups[group].config.Enabled || vel[group].enabled)
        val = getRecentEncoderReading(group);
    } else {
        val = getHeaterTempreture(group);
    }

    return val;
}

void setOutputMine(int group, float v) {
    if (group < numPidMotors) {
        int val = (int) (v);

        val += 127; // center for servos

        if (val > 255)
            val = 255;
        if (val < 0)
            val = 0;

        //        if(group == EXTRUDER0_INDEX && !isUpToTempreture()){
        //            //Saftey so as not to try to feed into a cold extruder
        //            setServo(group,getServoStop(group),0);
        //            return;
        //        }
        //println_I("Setting output value=");p_fl_I(val);print_I(" on ");p_int_I(group);
        setServo(group, val, 0);
    } else {
        setHeater(group, v);
    }
}

boolean isUpToTempreture() {
    return true;
    //   return bound(pidGroups[HEATER0_INDEX].SetPoint,
    //           getHeaterTempreture(HEATER0_INDEX),
    //           25,
    //           25)&& pidGroups[HEATER0_INDEX].SetPoint>100;
}
