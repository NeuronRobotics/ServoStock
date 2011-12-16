
#include "UserApp.h"

#if defined(__AVR_ATmega324P__)
	static BowlerPacketMini Packet;
#else
	static BowlerPacket Packet;
#endif
void server(){
	Bowler_Server((BowlerPacket *) &Packet,FALSE);
}

#define analogTime  30

void runDyIOMain(void){

	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1
	//println("Stack initialized");
	UserInit();// User code init
	//int i;
	RunEveryData asyncSched = {0,analogTime};
	float now;
	while (1){
		UserRun();

		if(FlagAsync == FLAG_OK ){
			if(checkDigital())
				server();
		}else{
			//println("Skipping D async");
		}
		server();
		if(FlagAsync == FLAG_OK ){
			if (RunEvery(&asyncSched)>0){
				if(checkAnalog())
					server();
			}else{
				now = getMs();
				if(!((asyncSched.MsTime >= 0) && (asyncSched.MsTime <= now))){
					println("Reseting async time, was=");p_fl(asyncSched.MsTime);print(" is=");p_fl(now);
					asyncSched.setPoint = analogTime;
					asyncSched.MsTime=now;
					server();
				}

			}
		}else{
			//println("Skipping A async");
		}
		server();

	}
}
