/*
 * CoProcCom.h
 *
 *  Created on: Nov 21, 2009
 *      Author: hephaestus
 */

#ifndef COPROCCOM_H_
#define COPROCCOM_H_
void addCoProcByte(BYTE b);
BOOL isProcessing();
void initCoProcCom(void);
void SendPacketToCoProc(BowlerPacket * Packet);

void GetPacketUARTCoProc(BYTE *packet,WORD size);
WORD Get_UART_Byte_CountCoProc(void);
BOOL SendPacketUARTCoProc(BYTE * packet,WORD size);



#endif /* COPROCCOM_H_ */
