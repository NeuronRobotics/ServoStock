/*
 * DyIOLib.h
 *
 *  Created on: Nov 30, 2010
 *      Author: hephaestus
 */

#ifndef DYIOLIB_H_
#define DYIOLIB_H_
#include "Bowler/Bowler.h"
/**
 * For any new commands, the packet will be passed to this function
 * @return If the function was able to process the packet
 */
BOOL DyIOLibOnPacket(BowlerPacket * Packet);
/**
 * This function is called once every iteration of the main loop
 */
void RunUserCode(void);
/**
 * This is called once at the start of the application
 */
void InitializeUserCode(void);

#endif /* DYIOLIB_H_ */
