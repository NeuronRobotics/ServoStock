
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
#include "servoCalibration.h"

BYTE SPITransceve(BYTE b);

BOOL asyncCallback(BowlerPacket *Packet);

NAMESPACE_LIST * getBcsCartesianNamespace();
AbsPID * getFlashPidGroupDataTable();
BOOL initFlashLocal();
void writeFlashLocal();

void bowlerSystem();


#endif //MAIN_H
