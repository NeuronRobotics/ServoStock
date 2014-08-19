
#ifndef MAIN_H
#define MAIN_H

#include "Bowler/Bowler.h"
#include "AuxUartServer.h"

#include "AS5055.h"
#include "ReplicatorHeader.h"
#include "Servo.h"
#include "StepperSim.h"
#include "ForgeHeater.h"
#include "CartesianController.h"
#include "delta.h"
#include "servoCalibration.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct _DeltaConfig{
	float RodLength;
	float BaseRadius;
	float EndEffectorRadius;
	float MaxZ;
	float MinZ;
}DeltaConfig;

uint8_t SPITransceve(uint8_t b);

boolean asyncCallback(BowlerPacket *Packet);

NAMESPACE_LIST * getBcsCartesianNamespace();
AbsPID * getFlashPidGroupDataTable();
boolean initFlashLocal();
void writeFlashLocal();

void bowlerSystem();


#endif //MAIN_H
