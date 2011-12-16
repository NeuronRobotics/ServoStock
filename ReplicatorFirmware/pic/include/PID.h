/*
 * PID.h
 *
 *  Created on: Feb 6, 2010
 *      Author: hephaestus
 */

#ifndef PID_H_
#define PID_H_

#define NUM_PID_GROUPS 8
#define NOT_USED_IN_PID 0xff
void GetConfigDyPID(BowlerPacket * Packet);
BYTE ConfigDyPID(BowlerPacket * Packet);
void InitPID(void);

void trigerPIDLimit(BYTE chan,PidLimitType type,INT32  tick);

BYTE GetPIDGroup(BYTE channel);
void pushPPMPacket(void);

#endif /* PID_H_ */
