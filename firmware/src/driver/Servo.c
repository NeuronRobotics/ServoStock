#include "main.h"

#define SERVO_BOUND 		0

#define NUM_SERVO 8

#define dataTableSize (NUM_SERVO)

//INTERPOLATE_DATA velocity[dataTableSize];
int position[dataTableSize];
int positionTemp[dataTableSize];
int sort[dataTableSize];
int lastValue=0;
int sortedIndex = 0;

void delayLoop();

ServoState servoStateMachineCurrentState = LOW;

void runSort(){
    int i=0,k=0,x;
    int current;
    for(k=0;k<dataTableSize;k++){
        sort[k]=dataTableSize;
    }
    for(x=0;x<dataTableSize;x++){
        positionTemp[x]=position[x];
    }
    for(x=0;x<dataTableSize;x++){
        current = 256;
        for(i=0;i<dataTableSize;i++){
            int used= FALSE;
            for(k=0;k<dataTableSize;k++){
                if(sort[k]==i){
                    used=TRUE;
                }
            }
            if(positionTemp[i]<current && !used){
                sort[x]=i;

                current = positionTemp[i];
            }
        }
    }

}

void printSortedData(){
    int x;
    print_I("Servo Data \r\n[ ");

    for(x=0;x<dataTableSize;x++){
        p_int_I(positionTemp[x]);print_I(" , ");
    }
    print_I(" ] ");

    print_I("\r\n[ ");

    for(x=0;x<dataTableSize;x++){
        p_int_I(sort[x]);print_I(" , ");
    }
    print_I(" ] ");

    print_I("\r\n[ ");

    for(x=0;x<dataTableSize;x++){
        p_int_I(positionTemp[sort[x]]);print_I(" , ");
    }
    print_I(" ] ");
}

void setServoTimer(int value){
    if(value<1)
        value = 1;
    if(value>0xfffe)
        value = 0xfffe;
    //PR2 = value;
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_256, value);
    ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_7);
}

void setTimerLowTime(){
    setServoTimer(300*18);
    servoStateMachineCurrentState = LOW;
}

void setTimerPreTime(){
    setServoTimer(285);
    servoStateMachineCurrentState = PRETIME;
}

void setTimerServoTicks(int value){
    setServoTimer((int)((float)value*1.4));
    servoStateMachineCurrentState = TIME;
}

#define MIN_SERVO 1


boolean setUpNextServo(){

    int diff = positionTemp[sort[sortedIndex]] - lastValue;
    lastValue = positionTemp[sort[sortedIndex]];
    if(diff<0){
        setPrintLevelErrorPrint();
        println_E("Servo.c: Something is wrong!! Current minus last value is less then 0");
        while(1);
    }

    if(diff>MIN_SERVO){
        setTimerServoTicks(diff);
        return TRUE;
    }
    //Fall through for pin shut off
    servoStateMachineCurrentState = TIME;
    return FALSE;
}

void stopCurrentServo(){
    pinOff(sort[sortedIndex]);
    sortedIndex++;
    if(sortedIndex == dataTableSize){
        servoStateMachineCurrentState = FINISH;
        //fall through to finish
    }
}

void servoTimerEvent()
{
        //mPORTDToggleBits(BIT_3);
	//StartCritical();
        stopServos();
        int j;
        switch(servoStateMachineCurrentState){
            case LOW:
                updateAllEncoders();
                if(getRunPidIsr()){
                    RunPIDControl();
                    //Print_Level l = getPrintLevel();
                    interpolateZXY();
                    //setPrintLevelNoPrint();
                    
                }
                //runLinearInterpolationServo(start,stop);
                runSort();
                for (j=0;j<NUM_SERVO;j++){
                    pinOn(j);
                }
                lastValue = 0;
                sortedIndex=0;
                //1ms delay for all servos
                setTimerPreTime();
                return;
            case PRETIME:
                if(setUpNextServo())
                    return;
            case TIME:
                stopCurrentServo();
                if(servoStateMachineCurrentState == TIME){
                    if(setUpNextServo() == FALSE){
                        //fast stop for channels with the same value
                        servoTimerEvent();
                    }
                }
                //If there are still more channels to be turned off after the recoursion, break
                if(servoStateMachineCurrentState != FINISH)
                    return;

            case FINISH:
                setTimerLowTime();
                return;
        }
        //EndCritical();
}

void __ISR(_TIMER_2_VECTOR, ipl7) Timer2Handler(void){
    servoTimerEvent();
}

void stopServos(){
    CloseTimer2();
}

/**
 * Start the servo hardware
 */
void initServos(){

    SERVO_HW_INIT();

    if(getPrintLevel() == NO_PRINT){
        CloseUART1();
    }
    int i;
    for(i=0;i<dataTableSize;i++){
        pinOff(i);
        setServo(i,128,0);
    }
//    runLinearInterpolationServo(start,stop);
//    runSort();
//    for(i=0;i<numPidMotor;i++){
//       println_I("Servo Positions: ");p_sl_I(getServoPosition(i));
//    }
//    for(i=0;i<numPidMotor;i++){
//       println_I("Sorted Servo Positions index: ");p_sl_I(sort[i]); print_I(" value: ");p_sl_I(position[sort[i]]);
//    }


    setTimerLowTime();
}

/**
 * Set a setpoint for a servo with an intrerpolated time
 */
void setServo(uint8_t PIN, uint8_t val,float time){
    if(time<30)
            time=0;
//    velocity[PIN].setTime=time;
//    velocity[PIN].set=(float)val;
//    velocity[PIN].start=(float)position[PIN];
//    velocity[PIN].startTime=getMs();
//    if (val==position[PIN]){
//            velocity[PIN].setTime=0;
//    }
    position[PIN]=val;
    Print_Level l = getPrintLevel();

    //println_I("\tSrv ");p_int_I(PIN); print_I(" v=");p_int_I(val);
    setPrintLevel(l);
}

/**
 * get the current position of the servo
 */
uint8_t getServoPosition(uint8_t PIN){
    return position[PIN];
}

//void runLinearInterpolationServo(uint8_t blockStart,uint8_t blockEnd){
//	uint8_t i;
//	for (i=blockStart;i<blockEnd;i++){
//		//float ip = interpolate(&velocity[i],getMs());
//                float ip = position[i];
//		if(ip>(255- SERVO_BOUND)){
//			ip=(255- SERVO_BOUND);
//		}
//		if(ip<SERVO_BOUND){
//			ip=SERVO_BOUND;
//		}
//		int tmp = (int)ip;
//
//                position[i]= (BYTE) tmp;
//
//	}
//
//}

void SetDIO(uint8_t PIN, boolean state){
    switch(PIN){
    case 0:
            ENC0_SERVO = state;
            break;
    case 1:
            ENC1_SERVO = state;
            break;
    case 2:
        //if(getPrintLevel() == NO_PRINT)
            ENC2_SERVO = state;
            break;
    case 3:
        //if(getPrintLevel() == NO_PRINT)
            ENC3_SERVO = state;
            break;
    case 4:
            ENC4_SERVO = state;
            break;
    case 5:
            ENC5_SERVO = state;
            break;
    case 6:
            ENC6_SERVO = state;
            break;
    case 7:
            ENC7_SERVO = state;
            break;
    default:
            break;
    }
}

uint8_t pinOn(uint8_t pin){
    SetDIO(pin,1);
    return 1;
}

void pinOff(uint8_t pin){
    SetDIO(pin,0);
}



void DelayPreServoPulse(void){
    Delay10us(90);
}

void delayLoop(){
    int loop = 16;
    while(loop--);
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
}


