#include "main.h"

typedef struct _SERVO_CALIBRATION
{
    int upperHistoresis;
    int lowerHistoresis;
    int stop;
    BOOL calibrating;
    BOOL calibrated;
} SERVO_CALIBRATION;
#define historesisINIT 1
#define defaultServoCenter 128
static SERVO_CALIBRATION servoCal[numPidMotors];

enum CAL_STATE servoCalibration(int group);
void calcCenter(int group);

static RunEveryData servoCalibrationTest ={0,200};

enum CAL_STATE
{
    forward  = 0,
    backward = 1,
    done     = 2
} state;



void incrementHistoresis(int group){
    servoCal[group].upperHistoresis++;
    calcCenter( group);
}
void decrementHistoresis(int group){
    servoCal[group].lowerHistoresis--;
    calcCenter( group);
}

void calcCenter(int group){
    int diff = (servoCal[group].upperHistoresis+servoCal[group].lowerHistoresis)/2;
    servoCal[group].stop = defaultServoCenter+diff;
    println_I("New center at ");p_int_I(servoCal[group].stop);
    print_I(" upper: ");p_int_I(servoCal[group].stop+servoCal[group].upperHistoresis);
    print_I(" lower: ");p_int_I(servoCal[group].stop+servoCal[group].lowerHistoresis);
}

void checkCalibration(int group){
    if(servoCal[group].calibrated != TRUE){
       servoCal[group].upperHistoresis=0;
       servoCal[group].lowerHistoresis=0;
       servoCal[group].stop=defaultServoCenter;
       servoCal[group].calibrated = TRUE ;
    }
}

int getUpperServoHistoresis(int group){
    checkCalibration(group);
    return servoCal[group].upperHistoresis;
}
int getLowerServoHistoresis(int group){
    checkCalibration(group);
    return servoCal[group].lowerHistoresis;
}
int getServoStop(int group){
    checkCalibration(group);
    return servoCal[group].stop;
}

void runServoCalibration(int group){
    println_I("\r\n\nStart calibration #");p_int_I(group);
    
    servoCal[group].lowerHistoresis = historesisINIT*-1;
    servoCal[group].upperHistoresis = historesisINIT;
    servoCal[group].stop = defaultServoCenter;
    println_I("\tReset PID");
    pidReset(group,0);// Zero encoder reading
    println_I("\tDisable PID");
    SetPIDEnabled(group, FALSE);
    state =  backward;
    println_I("\tSetting slow move");
    setOutputMine(group, -1.0f);
    servoCalibrationTest.MsTime=getMs();
    println_I("\tStart wait loop");
    while(servoCalibration(group)!=done){
        //wait for calibration to finish
        bowlerSystem();
    }
    pidReset(group,0);
    calcCenter( group);
    println_I("END calibration\n\n\r");
}

enum CAL_STATE servoCalibration(int group){

    if(RunEvery(&servoCalibrationTest)>0){
        
        float boundVal = 5.0;
        float extr=(float)readEncoder(group);
        if( bound(0, extr, boundVal, boundVal)){// check to see if the encoder has moved
            //we have not moved
            println_I("Encoder NOT moved ");p_fl_I(extr);
            if(state == forward){
                incrementHistoresis( group );
            }else if (state == backward){
                decrementHistoresis( group );
            }
        }else{
            println_I("Encoder moved ");p_fl_I(extr);
            if(state == backward){
                servoCal[group].lowerHistoresis--;
                println_I("Backward Calibrated for link# ");p_int_I(group);
                state = forward;
                setCurrentValue(group, 0);
            }else{
                servoCal[group].upperHistoresis++;
                println_I("Calibration done for link# ");p_int_I(group);
                state = done;
            }
        }
        if(state == forward){
            setOutputMine(group, 1.0f);
        }else if (state == backward){
            setOutputMine(group, -1.0f);
        }
    }

    return state;
}