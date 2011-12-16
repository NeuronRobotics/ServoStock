/*
 * AVRInterface.h
 *
 *  Created on: May 23, 2010
 *      Author: acamilo
 */

#ifndef AVRINTERFACE_H_
#define AVRINTERFACE_H_
void PowerCycleAVR();
void HoldAVRReset(void);
void ReleaseAVRReset(void);

BOOL writeAVRTempFlashPageLowByte(BYTE data, BYTE address);
BOOL writeAVRTempFlashPageHighByte(BYTE data, BYTE address);

#endif /* AVRINTERFACE_H_ */
