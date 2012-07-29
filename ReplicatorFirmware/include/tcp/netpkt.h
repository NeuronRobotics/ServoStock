/*********************************************************************
 *
 *            Packet Buffer Header File
 *
 *********************************************************************
 * FileName:        NetPkt.h
 * Description: 	internal packet buffer definition
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
 * $Id: NetPkt.h,v 1.4 2006/10/24 16:39:06 C12923 Exp $
 *
*/

#ifndef __NET_PKT_H__
#define __NET_PKT_H__


typedef enum
{
	// packet queueing masks
	ARP_QUE_MASK		= 0x01,		// packet part of the ARP queue
	MACTX_QUE_MASK		= 0x02,		// part of MAC TX queue
	CNXN_QUE_MASK		= 0x04,		// part of Conexion queue
	RXMSG_QUE_MASK		= 0x08,		// part of RX message queue
	//
	PKT_QUEUES_MASK		= (ARP_QUE_MASK|MACTX_QUE_MASK|CNXN_QUE_MASK|RXMSG_QUE_MASK),		// any queue mask
	// rx/tx packet flags
	PKT_FLAG_RX		= 0x10,		// it's an Rx packet
	PKT_FLAG_TX		= 0x20,		// it's an TX packet
	PKT_TX_AUTO_DEALLOC	= 0x40,		// TX packet can perform auto de-allocate after transfer
	PKT_FLAG_ZC_ALLOC	= 0x80		// zero copy allocation needed

	// flags that are not stored in the buffer
	// used for allocation type

	
}NET_PKT_FLAGS;		// net packet flags

typedef enum
{
	BUFF_MGR_ALLOC		= 0x01,		// packet/buffer allocated by the stack manager, not by the user
	BUFF_ZC_ALLOC		= 0x02,		// buffer part of a zero copy operation:
						//    for TX: a user supplied buffer
						//    for RX: a buffer that was supplied to the Eth Controller and is sticky
	BUFF_ZC_WACK		= 0x04,		// ZC buffer waitig for the RX acknowledge
       	
	
	//
}NET_PKT_BUFF_FLAGS;		//  packet/buffer flags
       	

typedef struct 
{
	sBuffDcpt	bDcpt;
	short int	bFlags;			// NET_PKT_BUFF_FLAGS value
} __attribute__ ((__packed__)) pktMgrDcpt;	// a packet manager descriptor


typedef struct NetPacket
{
	struct NetPacket *pNext;
	BYTE*	pTransportLayer;
	BYTE*	pNetworkLayer;
#ifdef _STACK_USE_ZC
	pktMgrDcpt	PktDcpt[2];		// - for TX: 
	                                        //           if ZC is not supported/requested
						//                NET_PKT is allocated to contain the whole packet
						//                the 1st buffer descriptor pBuff=NET_PKT.pPktLoad, nBytes=PktLen;
       						//                the 2nd buffer descriptor pBuff=0, nBytes=0;
						//           else (ZC)
						//                NET_PKT is allocated to contain the headers (ETH, IP, UDP/TCP)
						//                the 1st buffer descriptor pBuff=NET_PKT.pPktLoad, nBytes=headerLen;
       						//                the 2nd buffer descriptor pBuff=pUsrBuffer, nBytes=loadLen;
						// - for RX: 
						//           if  ZC is not supported/requested or the received packet is split across
						//           multiple buffers (depending on size of RX buffers)
						//                NET_PKT is allocated to contain the whole packet
						//                the 1st buffer descriptor pBuff=NET_PKT.pPktLoad, nBytes=PktLen;
						//                the 2nd buffer descriptor pBuff=0, nBytes=0;
						//           else (ZC && contiguous buffer)
						//                NET_PKT is allocated to contain just the NET_PKT itself, with no data
						//                the 1st buffer descriptor pBuff=0 and nBytes=0
						//                the 2nd buffer descriptor pBuff=the pointer to the Ethernet RX buffer, nBytes=pkt size
	pzSendAckF	buffXmitAck;		// the TX acknowledge call back function
#else
	pktMgrDcpt	PktDcpt[1];		// - for TX: everything in one large buffer. User buffer is copied here
						// - for RX: one large buffer. Whole packet copied here
#endif	// _STACK_USE_ZC
	
	
	struct 	NetPacket *pTcpNext;
	struct  MCSocket * pOwnerSocket;

	DWORD   TCPACKNum;
	TICK	TimeStamp;	//Time when rcvd or queued for xmit
	TICK	ARPTickStart;
	WORD	PktLen;
	BYTE	PktType;	// valid only for Rx Packets
	BYTE	PktFlags;	// a NET_PKT_FLAGS value
	
	//real packet data
	//DO NOT ADD FIELDS BELOW THIS LINE	
#ifdef _STACK_USE_ZC
	struct NetPacket *pOwner;	// owner of the RX buffer
#endif
	DWORD	pPktLoad[0];
}NET_PKT;

#endif
