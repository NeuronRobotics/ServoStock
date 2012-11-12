
#ifndef MAIN_H
#define MAIN_H
#include <plib.h>
#include "Bowler/Bowler.h"
#include "AuxUartServer.h"

#include "AS5055.h"
#include "ReplicatorHeader.h"
#include "Servo.h"
#include "StepperSim.h"
#include "ForgeHeater.h"
#include "CartesianController.h"
#include "delta.h"

#define servoCalebrateValue 121
#define ticksPerRev         (4096.0)
#define ticksPerDegree      (ticksPerRev/360.0)
#define gearRatio           (7.0)
#define calibrationAngle    (25.0)
#define servoHomeValue      (ticksPerDegree*calibrationAngle*gearRatio)

#if !defined(NUM_PID_GROUPS)
	#define NUM_PID_GROUPS (8)
#endif
void LoadCorePacket(BowlerPacket * Packet);
void setDebug(BOOL d);

#endif //MAIN_H
