/*
 * AsyncManager.h
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */

#ifndef ASYNCMANAGER_H_
#define ASYNCMANAGER_H_

void ProcessAsyncData(BowlerPacket * Packet);
int GetAnalogValFromAsync(BYTE pin);
void SetValFromAsync(int pin, int value);
int GetDigitalValFromAsync(BYTE pin);
void RunAsync(void);
void StopAsync(void);
void StartAsync(void);
void SyncSessionTime(float time);


#define		NOTEQUAL 		0
#define		DEADBAND 		1
#define		THRESHHOLD 		2
#define		AUTOSAMP 		3


#define		ASYN_BOTH 		0
#define		ASYN_RISING 	1
#define		ASYN_FALLING 	2


typedef struct _AdvancedAsyncData{
	INT32			previousVal;
	INT32			currentVal;
	RunEveryData 	time;
	BYTE		type;
	struct{
		INT32 	val;
	}deadBand;
	struct{
		INT32 	val;
		BYTE edge;
	}threshhold;
}AdvancedAsyncData;

BOOL pushAsyncReady( BYTE pin);
void startAdvancedAsyncDefault(BYTE pin);
void setAsyncLocal(BYTE channel,BOOL async);
void configAdvancedAsync(BowlerPacket * Packet);

#endif /* ASYNCMANAGER_H_ */
