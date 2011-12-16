/*
 * SPI.h
 *
 *  Created on: Apr 4, 2010
 *      Author: hephaestus
 */

#ifndef SPI_H_
#define SPI_H_
#define  SCK_TRIS			(_TRISG6)
#define  SDI_TRIS			(_TRISG7)
#define  SDO_TRIS			(_TRISG8)
void InitSPI(void);
void StopSPI(BYTE mode);
BOOL isSPI(BYTE mode);
BYTE GetByteSPI(BYTE b);
void SendPacketToSPI(BowlerPacket * Packet);
#endif /* SPI_H_ */
