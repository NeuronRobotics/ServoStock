/*********************************************************************
 *
 *            UDP Header File
 *
 *********************************************************************
 * FileName:        eUDP.h
 * Description: 	UDP implementation header
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * $Id: eUDP.h,v 1.2 2006/10/24 16:39:07 C12923 Exp $
 *
*/

#ifndef UDP_H
#define UDP_H


#define UDP_VERIFY_CHECKSUM     0       // if verification of UDP checksums needed


typedef WORD UDP_PORT;
typedef int UDP_SOCKET;

typedef struct _UDP_HEADER
{
    WORD		SourcePort;
    WORD		DestinationPort;
    WORD		Length;
    WORD		Checksum;
} UDP_HEADER;

int UDPExtractData( NET_PKT *RxPkt, BYTE* bfr, int len );
int UDPTransmit( BYTE* buf, int len, struct MCSocket* pSocket, DWORD remoteIP, WORD remotePort );
void UDP_RxHandler( NET_PKT *RxPkt );


#endif
