/*
 * Counter.h
 *
 *  Created on: Feb 7, 2010
 *      Author: hephaestus
 */

#ifndef COUNTER_H_
#define COUNTER_H_

#define CHAN0P0			_RE7
#define CHAN0P1			_RD8
#define CHAN1P0			_RE6
#define CHAN1P1			_RD9
#define CHAN2P0			_RE5
#define CHAN2P1			_RD10
#define CHAN3P0			_RE4
#define CHAN3P1			_RD11

#define CHAN0P0_tris	_TRISE7
#define CHAN0P1_tris	_TRISD8
#define CHAN1P0_tris	_TRISE6
#define CHAN1P1_tris	_TRISD9
#define CHAN2P0_tris	_TRISE5
#define CHAN2P1_tris	_TRISD10
#define CHAN3P0_tris	_TRISE4
#define CHAN3P1_tris	_TRISD11
#define OFF 			0
#define ON 				1

typedef struct __attribute__((__packed__)) _COUNTER
{
	LONG SETPOINT;
	LONG CURRENT;
	BYTE STEP_INDEX;
	BYTE TimeOffset;
	BYTE TimeStep;
	BOOL OutputEnabled;
	BOOL Homed;
	INTERPOLATE_DATA interpolate;
} COUNTER;

typedef union __attribute__((__packed__)) _COUNTER_PINS
{
	struct{
		BYTE INT;
		BYTE DIR;
		BYTE HOME;
	};
	BYTE b[3];

} COUNTER_PINS;

void runCounterGroup(BYTE group);
void setPinsByGroup(BYTE chan,BYTE pin1,BYTE pin2);
#define NUM_COUNTER_GROUPS 4

void InitCounterPins(void);
void ClearCounter(BYTE pin);
BOOL StartCounterInput(BYTE pin);
void initCounterAsync(BYTE chan,INT32 val);
BOOL StartCounterOutput(BYTE pin);
void RunCounter(void);
BOOL SetCounterInput(BYTE chan,LONG val);
LONG GetCounterByGroup(BYTE chan);
LONG GetCounterByChannel(BYTE chan);
BOOL SetCounterOutput(BYTE chan,LONG val, UINT32 ms);
LONG GetCounterOutput(BYTE chan);
void SetupCounterTimer(void);

BYTE channelToCounterGroup(BYTE pin);
BYTE getCounterIntChannnel(BYTE group);
BYTE getCounterDirChannnel(BYTE group);
BYTE getCounterHomeChannnel(BYTE group);

void findCounterPins(BYTE * pins,BYTE pin);

#endif /* COUNTER_H_ */
