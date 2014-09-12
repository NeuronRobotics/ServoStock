
#ifndef MAIN_H
#define MAIN_H

//#define Rev4
#define Rev4

#include "Bowler/Bowler.h"
#include "AuxUartServer.h"

#include "AS5055.h"
#include "ServoStock.h"
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



uint8_t SPITransceve(uint8_t b);

boolean asyncCallback(BowlerPacket *Packet);

void bowlerSystem();


#endif //MAIN_H
