/*
 * Switches.c
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

static BYTE switched;
static BYTE bankState[2];
static float lastVolt=0;
static float volt;


void CheckSwitches(void){
	switched=0;
	volt = GetRawVoltage();
	BOOL up = FALSE;

	//println("Voltage on raw:");
	//p_fl(volt);

	//println("Voltage on bank0:");
	//p_fl(GetRail0Voltage());

	//println("Voltage on bank1:");
	//p_fl(GetRail1Voltage());

	BYTE reg = isRegulated_0();
	if (bankState[0] != reg ){
		bankState[0]=reg;
		up=TRUE;
	}


	reg = isRegulated_1();
	if (bankState[1] != reg){
		bankState[1] = reg;
		up=TRUE;
	}

	//if(! (bankState[1] == 1 && bankState[0] ==1 ) ){
		if ((lastVolt>RawVoltageMin) && (volt<RawVoltageMin)){
			up=TRUE;
			lastVolt = volt;
		}
		if ((lastVolt<RawVoltageMin) && (volt>RawVoltageMin)){
			up=TRUE;
			lastVolt = volt;
		}
	//}
	if(up){
		print("\nPushing upstream Power Packet bank 0: ");p_ul(bankState[0]);print(" bank 1: ");p_ul(bankState[1]);print(" \nPower Code 0: ");p_ul(GetRawVoltageCode(0));print(" \nPower Code 1 : ");p_ul(GetRawVoltageCode(1));print(" \nRaw: ");p_fl(GetRawVoltage());
		UpstreamPushPowerChange();
	}
}

BYTE IsRegulated(float voltage){
	float raw = GetRawVoltage()+.11;//adding the voltage drop across the diaode
	if((voltage < raw+.01)&&(voltage > raw-.01))
		return FALSE;
	if ((voltage<(5.25))&&(voltage>(4.4))){//USB spec is 5.25v to 4.4v.
		return TRUE;
	}
	return FALSE;
}
