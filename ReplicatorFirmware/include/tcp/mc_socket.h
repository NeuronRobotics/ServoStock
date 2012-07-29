/*********************************************************************
 *
 *                  Socket layer for Microchip TCP/IP Stack
 *
 *********************************************************************
 * FileName:        mc_socket.h
 * Description: 	Socket Layer header
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
*/



#ifndef _MC_SOCKET_H_
#define _MC_SOCKET_H_


/*
 * TCP States as defined by rfc793
 */
typedef enum _TCP_STATE
{
	SKT_CLOSED,		// 0
	SKT_CREATED,		// 1
	SKT_BOUND,		// 2
	TCP_LISTEN,		// 3
	TCP_SYN_RCVD,		// 4
	TCP_SYN_SENT,		// 5
	TCP_EST,		// 6
	TCP_CLOSE_WAIT, 	// 7
	TCP_LAST_ACK,		// 8
	TCP_FIN_WAIT_1,		// 9
	TCP_RESET_RCVD,		// 10
	TCP_CLOSE,		// 11
	TCP_INVALID,		// 12
} TCP_STATE;


typedef enum
{
	// TCP flags
	TCP_FIRST_SEND		= 0x01,		// first send on the TCP socket
	TCP_NO_DELAY		= 0x02,		// disable Nagle algorithm
	
	// general socket flags
	SOCK_FLAG_ZCOPY		= 0x080,	// zero copy socket
		

}SOCK_FLAGS;


/*
 * TCP Flags as defined by rfc793
 */
#define FIN     0x01
#define SYN     0x02
#define RST     0x04
#define PSH     0x08
#define ACK     0x10
#define URG     0x20
#define ACK_SENT     0x80	//Internal to this stack

struct MCSocket
{
	int			    SocketType;
	NET_PKT         *pRxActivePacket;
	NET_PKT         *pTxActivePacket;
	NET_PKT		    *pTCPListHead;
	NET_PKT		    *pTCPListTail;
	struct MCSocket *pParentSocket;
	PktQueue	    CnxnQueue;
	PktQueue	    RxMsgQueue;
	TCP_STATE	    smState;

	//for cnxn less, the remote address acts as a filter on the rcv datagrams.
	//discard packets that do not match the remote address.
	DWORD		remoteIP;
    WORD		remotePort;
    
	DWORD		RemIP; //used for the legacy api
	DWORD		ActiveRxSrcIP;
    WORD		ActiveRxSrcPort;
	
	//local address must be bind after socket is created
	DWORD		localIP;	//bind
    WORD		localPort;	//bind

	//Incoming packet FIFO

	SOCK_FLAGS		sockFlags;
#ifdef _STACK_USE_ZC
	pzSendAckF		sockXmitAck;
#endif	// _STACK_USE_ZC

	// TCP Specific fields
	int			DataByteIndex;
	int			TxDataIndex;
	int			TxBfrSize;	
	int			RxBfrSize;	

	//PktQueue	AckPktList; 	//TCP List for pkt retransmission
	int			AckListCount;
	
	int			backlog;
	int			SocketID;
    DWORD 		TcpSEQ;  //our sequence number
    DWORD 		TcpACK; //peer sequence number

    TICK 		startTick;
	TICK		KeepAliveTick;    
   	TICK		TCPAppCloseTimer;
	TICK		NagglesTimer;
	BOOL		TCPAppClosed;
 
    BYTE 		RetryCount;
    BYTE		KeepAliveRetrys;    
    
};

#define INVALID_TCP_PORT        (0L)

extern struct MCSocket*  SocketArray;
extern int              _StackSockets;

SOCKET FindTargetSocket( int SockType, DWORD SrcIP, DWORD DestIP, WORD DestPort );
void SocketInitialize( SOCKET s );
int SocketLayerInit();
void SocketLayerClose(void);


#endif  // _MC_SOCKET_H_

