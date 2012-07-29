
#ifndef MAIN_H
#define MAIN_H
#include <plib.h>
#include "EthernetController.h"
#include "Bowler/Bowler.h"
#include "AuxUartServer.h"
#include "boards.h"

#if !defined(NUM_PID_GROUPS)
	#define NUM_PID_GROUPS (8)
#endif
void LoadCorePacket(BowlerPacket * Packet);
void setDebug(BOOL d);

#endif //MAIN_H
