/**
 * @file AbstractPID.h
 *
 * Created on: Apr 9, 2010
 * @author Kevin Harrington
 */

#ifndef ABSTRACTPID_H_
#define ABSTRACTPID_H_
#include "Bowler_Helper.h"
#define IntegralSize  100.0

//bcs.pid
#define _PID				0x6469705f // '_pid'  Get/Set the pid setpoint
#define CPID				0x64697063 //  Configure PID
#define APID				0x64697061 // 'apid'  Get/Set all PID channels
#define RPID				0x64697072 // 'rpid'  Reset a PID channel
#define _VPD				0x6470765f // '_vpd'    PID velocity command
#define KPID				0x6469706b // 'kpid'  Kill all PID controllers

typedef enum _PidLimitType {

	NO_LIMIT  =(0xff),

	LOWERLIMIT=(0x00),

	INDEXEVENT=(0x01),

	UPPERLIMIT=(0x02),

	OVERCURRENT=(0x03),

	CONTROLLER_ERROR=(0x04)
}PidLimitType;

typedef struct  _PidLimitEvent{
	int group;
	PidLimitType type;
	float time;
	INT32 value;
	INT32 latchTickError;
//	BOOL stopOnIndex;
}PidLimitEvent;

/**
 * These are your Control Constants
 */
	typedef struct _AdsPID_ConFIG{
		float		P;
		float 		I;
		float		D;
	} AdsPID_ConFIG;
/**
 * This is the storage struct for all the information needed to run the PID calculation
 * Note that this has no assumptions on the type of inputs or type of outputs
 * It also has no assumptions on the time step it is run over. It stores previous time and
 * will calculate scaling based on that and the current time
 */
	typedef struct __attribute__((__packed__)) _AbsPID
	{
		AdsPID_ConFIG  	K;
		float 			SetPoint;
		float			IndexLatchValue;
		BOOL 			stopOnIndex;
		BOOL 			useIndexLatch;
		float			CurrentState;
		float			PreviousError;
		unsigned int	integralCircularBufferIndex;
		float  			IntegralCircularBuffer[((int)IntegralSize)];
		float	 		integralTotal;
		float			Output;
		// This must be in MS
		float			PreviousTime;
		unsigned char  	   channel;
		unsigned	Enabled 	:1;
		unsigned 	Polarity	:1;
		unsigned 	Async		:1;
		unsigned 				:5;
		INTERPOLATE_DATA interpolate;
		float lastPushedValue;
		float lastPushedTime;
	} AbsPID;

	typedef struct __attribute__((__packed__)) _DYIO_PID
	{
		unsigned char inputMode;
		unsigned char inputChannel;
		unsigned char outputMode;
		unsigned char outputChannel;
		unsigned char outVal;
	} DYIO_PID;

	typedef struct __attribute__((__packed__)) _PD_VEL
	{
		BOOL enabled;
		float unitsPerSeCond;
		INT32 lastPosition;
		float lastVelocity;
		float lastTime;
		float currentOutputVel;
	} PD_VEL;
/**
 * RunAbstractPIDCalc
 * @param state A pointer to the AbsPID struct to run the calculations on
 * @param CurrentTime a float of the time it is called in MS for use by the PID calculation
 */
void RunAbstractPIDCalc(AbsPID * state,float CurrentTime);
/**typedef struct __attribute__((__packed__)) _PD_VEL
{
	BOOL enabled;
	float unitsPerSeCond;
	INT32 lastPosition;
	float lastVelocity;
	float lastTime;
	float currentOutputVel;
} PD_VEL;
 * InitAbsPID
 * @param state A pointer to the AbsPID the initialize
 * @param KP the Proportional Constant
 * @param KI the Integral Constant
 * @param KD the Derivative Constant
 * @param time the starting time
 */
void InitAbsPIDWithPosition(AbsPID * state,float KP,float KI,float KD,float time,float currentPosition);
void InitAbsPID(AbsPID * state,float KP,float KI,float KD,float time);
/**
 * Handle a PID packet.
 * @return True if the packet was processed, False if it was not  PID packet
 */
unsigned char ProcessPIDPacket(BowlerPacket * Packet);
/**
 * @param groups a pointer the the array of PID groups
 * @param the number of PID groups
 * @param getPositionPtr function pointer to the get position function
 * @param setPositionPtr function pointer to the set position function
 * @param resetPositionPtr function pointer to the re-set position function
 * @param pidAsyncCallbackPtr function pointer to push an async value
 */
void InitilizePidController(AbsPID * groups,PD_VEL * vel,int numberOfGroups,
		float (*getPositionPtr)(int),
		void (*setOutputPtr)(int,float),
		int (*resetPositionPtr)(int,int),
		BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet),
		void (*onPidConfigurePtr)(int),
		PidLimitEvent * (*checkPIDLimitEventsPtr)(BYTE group));



BYTE SetPIDTimed(BYTE chan,INT32 val,float ms);
BYTE SetPID(BYTE chan,INT32 val);
int GetPIDPosition(BYTE chan);
void printPIDvals(AbsPID * pid);
BYTE ZeroPID(BYTE chan);
void RunPID(void);
void RunPDVel(BYTE chan);
void pushPID(BYTE chan, INT32 value, float time);
void pushPIDLimitEvent(PidLimitEvent * event);


#endif /* ABSTRACTPID_H_ */
