#include "main.h"

#define SERVO_BOUND 		1
INTERPOLATE_DATA velocity[numPidMotor];
int position[numPidMotor];
void runLinearInterpolationServo(BYTE blockStart,BYTE blockEnd);
BYTE pinOn(BYTE pin);
void pinOff(BYTE pin);
void DelayPreServoPulse(void);


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

/**
 * Run the pulse for all pins
 */
void runServos(){
	//disableDebug();
	UINT16 j;
	BYTE xIndex;
	//return;
	BYTE start=0;
	BYTE stop=numPidMotor;

	runLinearInterpolationServo(start,stop);

	BYTE num=0;
	for (j=start;j<stop;j++){
		num+=pinOn(j);
	}
	//run minimal .75 ms pulse
	DelayPreServoPulse();
	//loop 255 times and turn off all servos as their set position is equal to the loop counter
	for (j=0;j<256;j++){
		//check all servo positions
		for (xIndex=start; xIndex < stop ;xIndex++){
			if (j == position[xIndex] ){
				//turn off if it is time to turn off
				pinOff(xIndex);
			}
		}
                delayLoop();
	}
//	for (xIndex=start; xIndex < stop ;xIndex++){
//            pinOff(xIndex);
//	}
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