
#ifndef MAIN_H
#define MAIN_H
#include <plib.h>
#include "EthernetController.h"
#include "Bowler/Bowler.h"
#include "AuxUartServer.h"
#include "boards.h"
#include "ReplicatorHeader.h"

#if !defined(NUM_PID_GROUPS)
	#define NUM_PID_GROUPS (12)
#endif
void LoadCorePacket(BowlerPacket * Packet);
void setDebug(BOOL d);

#endif //MAIN_H
