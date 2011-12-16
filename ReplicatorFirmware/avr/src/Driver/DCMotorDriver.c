/**
 * @file DCMotorDriver.c
 *
 *  Created on: Sep 9, 2010
 * @author Kevin Harrington
 */
#include "UserApp.h"

extern DATA_STRUCT DATA;

BYTE pwm,dir;

void setPwmDir(BYTE pin){
	if(pin>7){
		dir=pin;
		pwm=dir-4;
	}else{
		pwm=pin;
		dir=pwm+4;
	}
}

BOOL InitDCMotor(BYTE pin){
	if (DATA.FUNCTION[pin].HAS_DC_MOTOR == FALSE){
		return FALSE;
	}
	setPwmDir(pin);

	configPinMode(pwm,IS_DC_MOTOR_VEL,OUTPUT,OFF);
	configPinMode(dir,IS_DC_MOTOR_DIR,OUTPUT,OFF);

	SetDCMotor(pwm,128);

	return TRUE;
}

void ClearDCMotor(BYTE pin){
	if (DATA.FUNCTION[pin].HAS_DC_MOTOR == FALSE){
		return;
	}
	setPwmDir(pin);
	if((GetChannelMode(pwm)==IS_DC_MOTOR_VEL)&&(GetChannelMode(dir)==IS_DC_MOTOR_DIR)){
		ClearPWM(pwm);
		//DATA.PIN[pwm].State=IS_DI;
		//DATA.PIN[dir].State=IS_DI;
		EEWriteMode(pwm,IS_DI);
		EEWriteMode(dir,IS_DI);
	}


}
BYTE GetDCMotor(BYTE pin){
	if (DATA.FUNCTION[pin].HAS_DC_MOTOR == FALSE){
		return 0;
	}
	setPwmDir(pin);
	return DATA.PIN[pwm].ServoPos;
}
void SetDCMotor(BYTE pin,BYTE vel){
	if (DATA.FUNCTION[pin].HAS_DC_MOTOR == FALSE){
		return;
	}
	setPwmDir(pin);

	int tmp = vel;
		tmp-=128;
	DATA.PIN[pwm].ServoPos = vel;

	if(tmp>0){
		SetDIO(dir,0);
		SetPWM(pwm,tmp<<1);
	}else{
		SetDIO(dir,1);
		SetPWM(pwm,(tmp*-1)<<1);
	}
}
