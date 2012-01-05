/*
 * UserMain.c
 *
 *  Created on: Nov 29, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"
void RunVel(void);

extern DATA_STRUCT DATA;

BOOL pwr=FALSE;

RunEveryData pid={0,30};
RunEveryData vel={0,100};
RunEveryData syncVolt={0,1000};
RunEveryData ppm={0,200};
static BOOL heartBeatLock = TRUE;
static int heartBeatLockTime = 1;


void UserRun(void){
//	StartCritical();
//	EndCritical();
	float now = getMs();
	if((now-getLastPacketTime()) > heartBeatLockTime){
		if(heartBeatLock){
			lockServos();
		}
	}else{
		unlockServos();
	}

	if (RunEvery(&ppm)>0)
		RunPPMCheck();
	//BYTE i;
	buttonCheck(7);

	//SetGreen(FLAG_BUSY);
	RTS_HO_IO=FLAG_BUSY;
	if ((RunEvery(&syncVolt)>0)){
		UpdateAVRLED();
	}
	CheckSwitches();

	if(pwr){
		DownstreamPowerChange();
		pwr = FALSE;
	}

	RunAsync();

	disableDebug();
	if (RunEvery(&pid)>0){
		RunPID();
	}
#if defined(USE_VELOCITY)
	if (RunEvery(&vel)>0){
		RunVel();
	}
#endif
	enableDebug();

	CartesianControllerCoOp();

	SetColor((isLocked() )?1:0,(isActive() && !isLocked())?1:0,1);

}

void UpdateAVRLED(void){
	pwr=TRUE;
}

void setHeartBeatState( BOOL hb, int time){
	heartBeatLock = hb;
	heartBeatLockTime=time*2;
}

int getHeartBeatTime(){
	return heartBeatLockTime;
}
BOOL getHeartBeatLock(){
	return heartBeatLock;
}
