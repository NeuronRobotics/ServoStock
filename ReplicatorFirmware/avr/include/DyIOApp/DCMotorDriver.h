/**
 * @file DCMotorDriver.h
 *
 *  Created on: Sep 9, 2010
 * @author Kevin Harrington
 */

#ifndef DCMOTORDRIVER_H_
#define DCMOTORDRIVER_H_

BOOL InitDCMotor(BYTE pin);
void ClearDCMotor(BYTE pin);
BYTE GetDCMotor(BYTE pin);
void SetDCMotor(BYTE pin,BYTE vel);

#endif /* DCMOTORDRIVER_H_ */
