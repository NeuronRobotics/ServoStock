/*
 * Power.h
 *
 *  Created on: Feb 6, 2010
 *      Author: hephaestus
 */

#ifndef POWER_H_
#define POWER_H_

#define RAW_POWER 1
#define REGULATED 0

WORD GetRailVoltage(void);
BYTE GetSwitchPosition(BYTE chan);


#endif /* POWER_H_ */
