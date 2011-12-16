/*
 * PIC_IO.h
 *
 *  Created on: Mar 5, 2010
 *      Author: hephaestus
 */

#ifndef PIC_IO_H_
#define PIC_IO_H_

BYTE SetCoProcMode(BYTE PIN,BYTE mode);
void SetChannelValueCoProc(BYTE PIN,BYTE state);
BYTE GetChannelValueCoProc(BYTE PIN);
WORD GetADC(BYTE PIN);
BOOL GetSerialStream(BowlerPacket * packet);
BOOL Get16Async(UINT16 * data);
BOOL Get8Async(UINT16 * data);
void CheckRev(void);
void SyncModes(void);

#endif /* PIC_IO_H_ */
