/*********************************************************************
 *
 *                  TcpIp private Common definitions
 *
 *********************************************************************
 * FileName:        _tcpip_common.h
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its dsPIC30F and PICmicro® Microcontroller is intended 
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip's dsPIC30F and PICmicro Microcontroller products. 
 * The software is owned by the Company and/or its supplier, and is
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
 *
 ********************************************************************/

#ifndef _TCPIP_COMMON_H_
#define _TCPIP_COMMON_H_

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <plib.h>

#include <GenericTypeDefs.h>

#include "system_services.h"

#include "tcpip_bsd_config.h"

#include "TCPIP-BSD/socket.h"

#include "TCPIP-BSD/tcpip_bsd_control.h"

//#define DEBUG

#ifdef DEBUG
	#define _BsdASSERT(smth) 	do{if((smth)==0){__asm__ __volatile__ ("teq $0, $0");}}while(0)
#else
	#define	_BsdASSERT(smth)    do{if((smth)){}}while(0)
#endif


#if (( (__PIC32_FEATURE_SET__ >= 500) && (__PIC32_FEATURE_SET__ <= 799) && defined (_ETH) && defined(MAC_EMBEDDED_PIC32) ))
	/* We're running with an embedded Ethernet Controller.
	 * Ethernet notifications are available.
	 ***********************************************/

	#undef MAC_ENC28J60
	#undef _EMBEDDED_ETHC
	#define _EMBEDDED_ETHC

	#if defined(ZC_SOCKET_API)
		#undef _STACK_USE_ZC
		#define _STACK_USE_ZC
	#endif

	extern pTCPIPEventF		_TcpNotifyFnc;		// user notification handler
	extern eEthEvents		_TcpEnabledEvents;	// user enabled notification events
	extern volatile eEthEvents	_TcpPendingEvents;	// notification events that are set, waiting to be re-acknowledged

	extern void	TCPIPEventInit(int intPri, int intSubPri);
	extern void	TCPIPEventClose(void);

#endif


/********************************
 *   extern cross declarations
 **********************************/
extern int	TCPIPProcessRx(void);
extern int	TCPIPProcessTick(void);
extern int	TCPIPProcessTx(void);


extern IP_ADDR  SysIPAddr;		// big endian
extern IP_ADDR  SysIPMask;		// big-endian
extern IP_ADDR 	SysIPGateway;	// big-endian
extern MAC_ADDR SysMACAddr;     // big-endian


#include "tcp_tick.h"
#include "netpkt.h"

#include "block_mgr.h"
#include "earp.h"
#include "emac.h"
#ifdef MAC_ENC28J60
	#include "enc28j60.h"
#endif	// MAC_ENC28J60
#include "etcp.h"
#include "ether.h"
#include "eip.h"
#include "eudp.h"
#include "gpfunc.h"
#include "pkt_queue.h"
#include "route.h"
#include "mc_socket.h"


#endif	// _TCPIP_COMMON_H_


