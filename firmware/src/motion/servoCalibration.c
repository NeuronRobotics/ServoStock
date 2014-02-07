#include "main.h"

typedef struct _SERVO_CALIBRATION
{
    int upperHistoresis;
    int lowerHistoresis;
    int stop;
    BOOL calibrating;
    BOOL calibrated;
} SERVO_CALIBRATION;
#define historesisINIT 0
#define defaultServoCenter 128
static SERVO_CALIBRATION servoCal[numPidMotors];

enum CAL_STATE servoCalibration(int group);
void calcCenter(int group);

static RunEveryData servoCalibrationTest ={0,1000};

enum CAL_STATE
{
    forward  = 0,
    backward = 1,
    done     = 2
} state;



void incrementHistoresis(int group){
    servoCal[group].upperHistoresis+=1;
    //calcCenter( group);
}
void decrementHistoresis(int group){
    servoCal[group].lowerHistoresis-=1;
}


void calcCenter(int group){
    int diff = (servoCal[group].upperHistoresis+servoCal[group].lowerHistoresis)/2;
    //servoCal[group].stop = defaultServoCenter+diff;
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
    DelayMs(100);
    println_E("\r\n\nStart calibration #");p_int_E(group);
    
    servoCal[group].lowerHistoresis = historesisINIT*-1;
    servoCal[group].upperHistoresis = historesisINIT;
    servoCal[group].stop = defaultServoCenter;
    println_I("\tReset PID");
    pidReset(group,0);// Zero encoder reading
    println_I("\tDisable PID Output");
    SetPIDEnabled(group, TRUE);
    SetPIDCalibrateionState(group, CALIBRARTION_hysteresis);
  
    state =  backward;
    println_I("\tSetting slow move");
    setOutputMine(group, -1.0f);
    servoCalibrationTest.MsTime=getMs();
    println_I("\tStart wait loop");
    while(servoCalibration(group)!=done){
        //wait for calibration to finish
        bowlerSystem();
    }
    
    
    SetPIDCalibrateionState(group, CALIBRARTION_DONE);
    println_I("New center at ");p_int_I(servoCal[group].stop);
    print_I(" upper: ");p_int_I(servoCal[group].stop+servoCal[group].upperHistoresis);
    print_I(" lower: ");p_int_I(servoCal[group].stop+servoCal[group].lowerHistoresis);
    println_E("END calibration\n\n\r");
}

enum CAL_STATE servoCalibration(int group){

    if(RunEvery(&servoCalibrationTest)>0){
        
        float boundVal = 6.0;
        float extr=GetPIDPosition(group);
        if(state == forward){
            incrementHistoresis( group );
        }else if (state == backward){
            decrementHistoresis( group );
        }
        if( bound(0, extr, boundVal, boundVal)){// check to see if the encoder has moved
            //we have not moved
            println_I("NOT moved ");p_fl_I(extr);
            int historesisBound = 50;
            if(servoCal[group].lowerHistoresis<-historesisBound && state == backward){
                println_E("Backward Motor seems damaged, more then counts of historesis ");
                state = forward;
            }
            if( servoCal[group].upperHistoresis>historesisBound && state == forward){
                println_E("Forward Motor seems damaged, more then counts of historesis ");
                state = done;
            }
        }else{
            println_E("Moved ");p_fl_E(extr);
            if(state == backward){
                servoCal[group].lowerHistoresis--;
                println_I("Backward Calibrated for link# ");p_int_I(group);
                state = forward;
            }else{
                servoCal[group].upperHistoresis++;
                println_I("Calibration done for link# ");p_int_I(group);
                state = done;
                //calcCenter( group);
            }
            pidReset(group,0);
            setOutputMine(group, 0);
            DelayMs(100);
        }
        if(state == forward){
            setOutputMine(group, 1.0f);
        }else if (state == backward){
            setOutputMine(group, -1.0f);
        }
    }

    return state;
}
