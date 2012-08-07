#include "main.h"

#define SERVO_BOUND 		1
INTERPOLATE_DATA velocity[numPidMotor];
BYTE position[numPidMotor];
void runLinearInterpolationServo(BYTE blockStart,BYTE blockEnd);
BYTE pinOn(BYTE pin);
void pinOff(BYTE pin);


/**
 * Start the servo hardware
 */
void initServos(){

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
	DelayPreServo();
	//loop 255 times and turn off all servos as their set position is equal to the loop counter
	for (j=0;j<256;j++){
		//check all servo positions
		for (xIndex=start; xIndex < stop ;xIndex++){
			if (j == position[xIndex] ){
				//turn off if it is time to turn off
				pinOff(xIndex);
			}
		}
		// Small delay to pad the loop
		//_delay_us(1);
		//Nop();Nop();Nop();  Nop();Nop();Nop();  Nop();Nop();Nop();   Nop();Nop();
	}
	for (xIndex=start; xIndex < stop ;xIndex++){
            pinOff(xIndex);
	}
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

BYTE pinOn(BYTE pin){
    //SetDIO(pin,ON);
    return 1;
}

void pinOff(BYTE pin){
	//SetDIO(pin,OFF);
}

void DelayPreServo(void){
    Delay10us(90);
}