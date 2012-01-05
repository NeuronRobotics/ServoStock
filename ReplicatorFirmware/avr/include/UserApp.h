/*
 * UserApp.h
 *
 *  Created on: Jan 2, 2010
 *      Author: hephaestus
 */

#ifndef USERAPP_H_
#define USERAPP_H_

//#define WPIRBE

#include "Bowler/Bowler.h"
#include "DyIOApp/HardwareProfile.h"

#include "DyIO/DyIO_def.h"
#include "DyIOApp/Power.h"
#include "DyIOApp/Servo.h"
#include "DyIOApp/AVR_IO.h"
#include "DyIOApp/ADC.h"
#include "DyIOApp/PWM.h"
#include "DyIOApp/EEPROM.h"
#include "DyIOApp/UARTPassThrough.h"
#include "DyIOApp/DCMotorDriver.h"
#include "DyIOApp/Push.h"

#include "DyIOApp/SPISlave.h"
#if defined(USE_AS_LIBRARY)
#include "DyIOApp/DyIOLib.h"
#endif

void UserInit(void);
void UserRun(void);
void AsynAck(void);

BOOL checkAnalog();
UINT16 getAnv(BYTE pin);
BOOL getDig(BYTE pin);
BOOL checkDigital();
void initPinState(BYTE i);


#endif /* USERAPP_H_ */
