#include "main.h"

#define SERVO_BOUND 		1
INTERPOLATE_DATA velocity[numPidMotor+1];
int position[numPidMotor+1];
int sort[numPidMotor+1];
int lastValue;
int sortedIndex = 0;
BYTE start=0;
BYTE stop=numPidMotor;


ServoState state = LOW;

void runSort(){
    int i=0,k=0,x;
    int current;
    for(k=0;k<numPidMotor;k++){
        sort[k]=numPidMotor;
    }
    for(x=0;x<numPidMotor;x++){
        current = 256;
        for(i=0;i<numPidMotor;i++){
            int used= FALSE;
            for(k=0;k<numPidMotor;k++){
                if(sort[k]==i){
                    used=TRUE;
                }
            }
            if(position[i]<current && !used){
                sort[x]=i;
                current = position[i];
            }
        }
    }
}

void setServoTimer(int value){
    if(value<1)
        value = 1;
    if(value>=0xfffe)
        value = 0xfffe;
    PR2 = value;
    ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_5);
}

void setTimerLowTime(){
    setServoTimer(300*15);
    state = LOW;
}

void setTimerPreTime(){
    setServoTimer(358);
    state = PRETIME;
}

void setTimerServoTicks(int value){
    setServoTimer((int)((float)value*1.4));
    state = TIME;
}

#define MIN_SERVO 2

int currentServo,currentValue,diff,nextServo,nextValue;
void __ISR(_TIMER_2_VECTOR, ipl5) Timer2Handler(void)
{
        //mPORTDToggleBits(BIT_3);
	StartCritical();
        int j;
        switch(state){
            case LOW:
                runLinearInterpolationServo(start,stop);
                runSort();
                for (j=start;j<stop;j++){
                    pinOn(j);
                }
                lastValue = 0;
                sortedIndex=0;
                setTimerPreTime();
                break;
            case PRETIME:
                currentServo = sort[sortedIndex];
                currentValue = position[currentServo];
                diff = currentValue - lastValue;
                if(diff>MIN_SERVO){
                    setTimerServoTicks(diff);
                    break;
                }
            case TIME:
                currentServo = sort[sortedIndex];
                currentValue = position[currentServo];
                pinOff(currentServo);
                lastValue = currentValue;

                sortedIndex++;

                if(sortedIndex == numPidMotor){
                    state = FINISH;
                }else{
                    do{//Loop throug to see if there is more then one value ready to turn off
                        nextServo = sort[sortedIndex];
                        nextValue = position[nextServo];
                        diff = nextValue - lastValue;
                        if(!(diff > MIN_SERVO)){
                            //Stop next value and increment
                            pinOff(nextServo);
                            lastValue = nextValue;
                            sortedIndex++;
                        }
                    }while(!(diff > MIN_SERVO) && sortedIndex != numPidMotor);
                    if(diff>MIN_SERVO && sortedIndex != numPidMotor){
                        setTimerServoTicks(diff);
                        break;
                    }
                }
            case FINISH:
                setTimerLowTime();
                break;
        }
        EndCritical();
}

/**
 * Start the servo hardware
 */
void initServos(){

    ENC_SERVO_INIT();

    if(getPrintLevel() == NO_PRINT){
        CloseUART1();
    }
    int i;
    for(i=0;i<numPidMotor;i++){
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

    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_256, 1);
    setTimerLowTime();
}

/**
 * Set a setpoint for a servo with an intrerpolated time
 */
void setServo(BYTE PIN, BYTE val,float time){
    if(time<30)
            time=0;
    velocity[PIN].setTime=time;
    velocity[PIN].set=(float)val;
    velocity[PIN].start=(float)position[PIN];
    velocity[PIN].startTime=getMs();
    if (val==position[PIN]){
            velocity[PIN].setTime=0;
    }
}

/**
 * get the current position of the servo
 */
BYTE getServoPosition(BYTE PIN){
    return position[PIN];
}

void runLinearInterpolationServo(BYTE blockStart,BYTE blockEnd){
	BYTE i;
	for (i=blockStart;i<blockEnd;i++){
		float ip = interpolate(&velocity[i],getMs());
		if(ip>(255- SERVO_BOUND)){
			ip=(255- SERVO_BOUND);
		}
		if(ip<SERVO_BOUND){
			ip=SERVO_BOUND;
		}
		int tmp = (int)ip;
		position[i]= (BYTE) tmp;
	}

}

void SetDIO(BYTE PIN, BOOL state){
    switch(PIN){
    case 0:
            ENC0_SERVO = state;
            break;
    case 1:
            ENC1_SERVO = state;
            break;
    case 2:
        if(getPrintLevel() == NO_PRINT)
            ENC2_SERVO = state;
            break;
    case 3:
        if(getPrintLevel() == NO_PRINT)
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
    }
}

BYTE pinOn(BYTE pin){
    SetDIO(pin,1);
    return 1;
}

void pinOff(BYTE pin){
    SetDIO(pin,0);
}



void DelayPreServoPulse(void){
    Delay10us(90);
}

//void delayLoop(){
//    int loop = 16;
//    while(loop--);
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//}

/**
 * Run the pulse for all pins
 */
//void runServos(){
//    return;
//	//disableDebug();
//	UINT16 j;
//	BYTE xIndex;
//	//return;
//
//
//	runLinearInterpolationServo(start,stop);
//
//	BYTE num=0;
//	for (j=start;j<stop;j++){
//		num+=pinOn(j);
//	}
//	//run minimal .75 ms pulse
//	DelayPreServoPulse();
//	//loop 255 times and turn off all servos as their set position is equal to the loop counter
//	for (j=0;j<256;j++){
//		//check all servo positions
//		for (xIndex=start; xIndex < stop ;xIndex++){
//			if (j == position[xIndex] ){
//				//turn off if it is time to turn off
//				pinOff(xIndex);
//			}
//		}
//                delayLoop();
//	}
////	for (xIndex=start; xIndex < stop ;xIndex++){
////            pinOff(xIndex);
////	}
//}



