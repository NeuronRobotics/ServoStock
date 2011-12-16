/*
 * Bowler_Server.h
 *
 *  Created on: Jun 18, 2010
 *      Author: hephaestus
 */

#ifndef BOWLER_SERVER_H_
#define BOWLER_SERVER_H_
/**
 * Initialize the server
 */
void Bowler_Init(void);
/**
 * Run an instance of the server
 */
BYTE Bowler_Server(BowlerPacket * Packet, BOOL debug);

#endif /* BOWLER_SERVER_H_ */
