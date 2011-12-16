/*
 * Switches.h
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#ifndef SWITCHES_H_
#define SWITCHES_H_
#define FiveVoltADC		 4.5
#define RailDeadZone	 .3
#define RawVoltageMin	 6.2

BYTE IsRegulated(float voltage);
#if defined(LAST_DEV_BOARD)
	#define isRegulated_0() (_RD1)
	#define isRegulated_1() (_RD6)
#endif
#if defined(RELEASE_BOARD)
	#define isRegulated_0() IsRegulated(GetRail0Voltage())
	#define isRegulated_1() IsRegulated(GetRail1Voltage())
#endif

void unlockServos();
void lockServos();
void CheckSwitches(void);


#endif /* SWITCHES_H_ */
