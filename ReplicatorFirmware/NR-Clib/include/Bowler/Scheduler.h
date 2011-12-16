/**
 *
 * Copyright 2009 Neuron Robotics, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef SCHEDULER_H_
#define SCHEDULER_H_
/**
 * GetTImeTicks
 * @return The number of timer ticks since the chip started running
 */
UINT64 GetTimeTicks(void);

/**
 * StartScheduler
 * This is run before the user code starts and initiates the timer based clock
 */
void StartScheduler(void);

/**
 * SchedulerGetStep
 * @param chan This is the channel to test if it is time for it to run. This value is from 0-5
 * @return This is a boolean that returns true if the channel is scheduled to run.
 * The time slices are 3.3 ms each, and there are 6 of them in total. That means each slice runs every 20Ms.
 * Basic architecture is 6 blocks of 3.3 Ms each.
 * The GetStep function will check if it is within that channel's time slice AND that slice has not run yet this cycle.
 * If it is in the time slice and it has not run, the function returns true
 * If it is in the time slice, and the slice has run, the it returns false
 * If it is not in the time slice, it returns false
 */
unsigned char SchedulerGetStep(unsigned char chan);
/**
 * Private function used by Bowler Stack.
 */
unsigned char ClearForCom(void);

/**
 * Retrurns TRUE if the timer has timed out
 */
unsigned char GetTimeoutState(void);
void TimeoutCounterReset(void);
/**
 * Start a timeout session, pass in MS to wait
 */
void TimeoutCounterInit(float timeout);
void TimeoutCounterStop(void);

/**
 * Data storage for scheduling events.
 */

typedef struct __attribute__((__packed__)) _RUN_EVERY{
	//The start time for the schedule
	float MsTime;
	//The time from the start time to loop over
	float setPoint;
} RUN_EVERY,RunEveryData;

/**
 * RunEvery
 * This function returns not 0 if it has been at least as long as the "setPoint" field says since the last time it returned not 0.
 * All timeing is handeled internally
 * @param data Pointer to a data storage table
 * @return float of MS after the assigned time that this function is running. A value of 0 means it has not been long enough
 */
float RunEvery(RunEveryData * data);

#endif /* SCHEDULER_H_ */
