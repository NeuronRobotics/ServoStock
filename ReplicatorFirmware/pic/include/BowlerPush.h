/*
 * Push.h
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#ifndef PUSH_H_
#define PUSH_H_
void LoadDefaultValues();
void LoadCorePacket(BowlerPacket * pack);
void pushError(BYTE zone,BYTE trace);

BYTE GetChannelValueCoProc(BYTE PIN);

void PushAllAsync(int * state);
void PushADCChange(BYTE pin,WORD state);
void PushDIOChange(BYTE pin,BYTE state);
void PushCounterChange(BYTE pin,LONG state);
BOOL GetSerialStream(BowlerPacket * packet);

void POWER(BowlerPacket * packet);
void SetCoProcLED(BOOL a, BOOL b, int batt);
void DownstreamPowerChange(void);
void UpstreamPushPowerChange(void);
void GetAllModes(BowlerPacket * pack);\

void PushCoProcAsync(void);

void PushADCval(BYTE pin,UINT16 val);
void PushDIval(BYTE pin,BYTE val);


#endif /* PUSH_H_ */
