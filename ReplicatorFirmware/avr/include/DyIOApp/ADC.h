/*
 * ADC.h
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#ifndef ADC_H_
#define ADC_H_

BYTE InitADC(BYTE pin);
void ClearADC(BYTE pin);
UINT16 GetADC(BYTE pin);
#endif /* ADC_H_ */
