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
//static INT32_UNION PID_Temp;
//static float time;
//static int val;
BowlerPacket tmpData;

uint8_t UserGetRPCs(BowlerPacket *Packet){
    if(processPIDGet(Packet))
        return TRUE;
    if(onCartesianPacket(Packet))
        return TRUE;
    return FALSE;
}
uint8_t UserPostRPCs(BowlerPacket *Packet){
    if(processPIDPost(Packet))
        return TRUE;
    if(onCartesianPacket(Packet))
        return TRUE;
    return FALSE;
}
uint8_t UserCriticalRPCs(BowlerPacket *Packet){
    if(processPIDCrit(Packet))
        return TRUE;
    if(onCartesianPacket(Packet))
        return TRUE;
    return FALSE;
}


