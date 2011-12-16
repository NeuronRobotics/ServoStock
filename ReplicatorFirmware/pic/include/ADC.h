/*
 * ADC.h
 *
 *  Created on: Feb 12, 2010
 *      Author: hephaestus
 */

#ifndef ADC_H_
#define ADC_H_

void InitADC(void);
BOOL isLocked(void);
BOOL isActive(void);
float GetRawVoltage(void);
BYTE GetRawVoltageCode(BYTE bank);
float GetRail0Voltage(void);
float GetRail1Voltage(void);

#endif /* ADC_H_ */
