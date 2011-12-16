/*
 * AVR_IO.h
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#ifndef AVR_IO_H_
#define AVR_IO_H_

void SetPinTris(BYTE PIN,BYTE state);
void SetDIO(BYTE PIN,BYTE state);
BYTE GetDIO(BYTE PIN);

#endif /* AVR_IO_H_ */
