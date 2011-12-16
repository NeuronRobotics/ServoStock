/**
 * @filePPMReader.h
 *
 *  Created on: Feb 18, 2011
 * @author Kevin Harrington
 */

#ifndef PPMREADER_H_
#define PPMREADER_H_

#define NUM_PPM_CHAN 6
#define INVALID_PPM_LINK 0xff
void pushPPMPacket(void);
void runPPMEvent(void);
void RunPPMCheck(void);
void clearPPM(BYTE chan);
void startPPM(BYTE chan);
void GetPPMDataToPacket(BowlerPacket * Packet);
void ConfigPPM(BowlerPacket * Packet);
void GetPPMDataToArray(BYTE * data);

#endif /* PPMREADER_H_ */
