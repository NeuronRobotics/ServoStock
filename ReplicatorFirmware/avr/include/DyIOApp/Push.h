/*
 * Push.h
 *
 *  Created on: Sep 24, 2010
 *      Author: hephaestus
 */

#ifndef PUSH_H_
#define PUSH_H_
void PushSerial(void);
void PushAllAdcVal();
void PushAllDiVal();
void PushADCval(BYTE pin,UINT16 val);
void PushDIval(BYTE pin,BYTE val);
#endif /* PUSH_H_ */
