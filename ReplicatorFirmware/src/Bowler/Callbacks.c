/*
 * Callbacks.c
 *
 *  Created on: Jul 8, 2010
 *      Author: hephaestus
 */
#include "main.h"
#define _DBG				0x6762645f // '_dbg'  Set up the debugging
#if !defined(NUM_PID_GROUPS )
#define NUM_PID_GROUPS 8
#endif
static INT32_UNION PID_Temp;
static float time;
static int val;
BowlerPacket tmpData;

BYTE UserGetRPCs(BowlerPacket *Packet){
    return processPIDGet(Packet);
}
BYTE UserPostRPCs(BowlerPacket *Packet){
    return processPIDPost(Packet);
}
BYTE UserCriticalRPCs(BowlerPacket *Packet){
    return processPIDCrit(Packet);
}


