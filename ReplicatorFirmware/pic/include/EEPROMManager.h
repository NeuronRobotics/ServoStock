/*
 * EEPROMManager.h
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */

#ifndef EEPROMMANAGER_H_
#define EEPROMMANAGER_H_

#define NAMESTART 0
#define LOCKSTART 17
#define DATASTART 22
#define DATAVALID 37
#include "Bowler/AbstractPID.h"
typedef struct  _pid_vales
{
	union{
		struct{
			unsigned 					:5;
			unsigned		Async		:1;
			unsigned		Polarity	:1;
			unsigned		Enabled 	:1;
			unsigned 		char inputMode;
			unsigned 		char inputChannel;
			unsigned 		char outputMode;
			unsigned 		char outputChannel;
			AdsPID_ConFIG 	K;
		};
		BYTE stream[5+sizeof(AdsPID_ConFIG )];
	};
} pid_vales;

typedef union _EESTORAGE
{
	struct
	{
		BYTE lockByte;
		pid_vales pid[NUM_PID_GROUPS];
		BYTE end;
	};
} EESTORAGE;

void readPPMLink(BYTE * vals);
void writePPMLink(BYTE * vals);

void LoadEEstore(void);
void WritePIDvalues(AbsPID * pid, DYIO_PID * dy);
void LoadPIDvals(AbsPID * pid, DYIO_PID * dy);

BOOL GetName(char * name);
void SetName(char * name);
BOOL GetLockCode(char * name);
void SetLockCode(char * code);
void SetEEPRomData(BYTE start,BYTE stop,BYTE * data);
void GetEEPRomData(BYTE start,BYTE stop,BYTE * data);


#endif /* EEPROMMANAGER_H_ */
