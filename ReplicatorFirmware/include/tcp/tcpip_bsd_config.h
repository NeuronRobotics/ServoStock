/*********************************************************************
 *
 *            BSD TCP/IP Stack Configuration File
 *
 *********************************************************************
 * FileName:        tcpip_bsd_config.h
 * Description: 	Configurations for BSD TCPIP Stack
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
 *
*/

#ifndef _TCPIP_BSD_CONFIG_H_
#define _TCPIP_BSD_CONFIG_H_

#include "hardware_profile.h"

/*****************************************************************************
 * peripheral library include, may be needed if the user is defining 
 * their own I/O lines and SPI configuration
 *****************************************************************************/
#include <plib.h>

/*****************************************************************************
 * General definitions for the TCP/IP stack 
 *****************************************************************************/
	/*****************************************************************************
	 * The device is configured with a default IP and MAC address.
	 * If the project uses a DHCP client, than the IP address will
	 * be assigned by the DCHP server.  
	 *****************************************************************************/
	#define DEFAULT_IP_ADDR			"192.168.0.37"
	#define DEFAULT_IP_GATEWAY		"192.168.0.1"
	#define DEFAULT_IP_MASK			"255.255.255.0"
	//#define DEFAULT_MAC_ADDR		"00-04-a3-00-00-02"     // set to "00-04-a3-00-00-00" (DEFAULT_MAC_ADDRESS) to use the MAC factory pre-programmed address  
	#define DEFAULT_MAC_ADDR		"00-20-4a-cc-b1-90"//cortex.wpi.edu
	/*****************************************************************************
	 * The maximum number of sockets that you may have active at one time.
	 *  If you are using any other middleware (HTTP, DHCP), you will need to 
	 * make sure that you can accomidate the worst case senerio.
	 *****************************************************************************/
	#define MAX_SOCKET				32

	/*****************************************************************************
	 * The number of ticks per second to generate an TCP tick.
	 * Used by the TCP state machine
	 * All other timings are based on this setting
     * Note: the System Tick resolution in HardwireProfile.h (TICKS_PER_SECOND) has to 
     * be fine enough to allow for this TCP tick granularity.  
	 *****************************************************************************/
	#define TCP_TICKS_PER_SECOND        (50)        // 20 ms default tick 

	/*****************************************************************************
	 * This is the transmit buffer size for out going TCP/IP packets
     * Can be modified by SO_SNDBUF on a per socket level.
	 *****************************************************************************/
	#define TCP_DEFAULT_TX_BFR_SZ	256

	/*****************************************************************************
	 * The default receive buffer size for TCP/IP sockets.
     * It is the default advertised window size on a stream socket.
     * Can be modified by SO_RCVBUF on a per socket level.
     * Note: all sockets share the common receive heap defined by BUFF_MGR_HEAP_SIZE
     * (see below). 
	 *****************************************************************************/
	#define TCP_DEFAULT_RX_BFR_SZ	512

	/*****************************************************************************
	 * This is the Nagle algorithm timeout.  Please refer to
	 * TCP/IP documentation for more informaiton on the Nagle
	 * algorithm
	 *****************************************************************************/
	#define NAGLE_TX_BFR_TIMEOUT	(TCP_TICKS_PER_SECOND * 1)

	/*****************************************************************************
	 * This is the ARP timeout.
	 *****************************************************************************/
	#define ARP_TIMEOUT_TICKS 		(TCP_TICKS_PER_SECOND * 6)

	/*****************************************************************************
	 *  This is the number of retries and timeout associated with
	 * transmitted TCP packets.
	 *****************************************************************************/
	#define MAX_RETRY_COUNTS		1
	#define TCP_RETRY_TIMEOUT_VAL   (TCP_TICKS_PER_SECOND * 7)

	/*****************************************************************************
	 *  Keep Alive  timeout and retries
	 *****************************************************************************/
    #define TCP_KEEP_ALIVE_TIMEOUT_VAL   (TCP_TICKS_PER_SECOND * 10)
    #define TCP_MAX_KEEP_ALIVE_RETRYS	2	// send n ack msgs TCP_KEEP_ALIVE_TIMEOUT_VAL ticks apart, 
										    // then close connection if no reply

	/*****************************************************************************
	 * The maximum number of packets waiting to be acknowledged for a socket.
     * When this limit is reached another transmit for the corresponding socket will fail.
	 *****************************************************************************/
	#define MAX_TCP_TX_PKT_BFR		8

	/*****************************************************************************
	 * The delay for the wait on a socket.
	 *****************************************************************************/
	#define TCP_WAIT_SOCKET_DEL		(TCP_TICKS_PER_SECOND * 14)


	/*****************************************************************************
	 * Process upto n Rx packets on every StackMgrProcess() call
	 *****************************************************************************/
	#define STACK_MGR_RX_PKT_CNT	8

	/*****************************************************************************
	 * The BSD stack uses a memory heap to store data for incoming/outgoing packets.
     * Define the size of this heap (BUFF_MGR_HEAP_SIZE) large enough to handle the packets
     * based on the number of TX connections and the kind of RX traffic you want to handle.
     * Note: this heap is different from the EMAC_RX_BUFF_SIZE RX buffers used by 
     * the internal PIC32 MAC when MAC_EMBEDDED_PIC32 is defined.
	 *****************************************************************************/
	#define BUFF_MGR_HEAP_SIZE		(1024*16)


/*****************************************************************************
 * If using the embedded Ethernet Controller on PIC32MX7 family
 *****************************************************************************/
#ifdef	MAC_EMBEDDED_PIC32

	/*****************************************************************************
	 * Definitions for PIC32MX processor with embedded 10/100 Mbps Ethernet Controller
	 *****************************************************************************/

	/*****************************************************************************
	 * Definitions for Ethernet Controller generated TcpIp Events
	 * The interrupt priority (1-lowest to 7-highest) and sub-priority (0 to 3) for the timer used to generate the ticks
	 *****************************************************************************/
	#define	TCPIP_EVENT_IPL			5
	#define	TCPIP_EVENT_SIPL		1

	/*****************************************************************************
	 * Enabling the Zero Copy sockets API
     * Define/Undefine to add/remove ZC functionality from the build 
	 *****************************************************************************/
	#define	ZC_SOCKET_API

	/*****************************************************************************
	 * Resources for Ethernet Controller Descriptors
	 * Can modify as needed.         
	 *****************************************************************************/
	#define EMAC_TX_DESCRIPTORS		10		// number of the TX descriptors to be created
	#define EMAC_RX_DESCRIPTORS		20		// number of the RX descriptors to be created 

	#define	EMAC_RX_BUFF_SIZE		1536/2		// size of a RX buffer. should be multiple of 16
								// this is the minimum size of all receive buffers
								// that can be passed by the stack to the ETHC
								// If the packets are large, they will take multiple RX buffers and the overhead will be higher

    #define EMAC_OPEN_LINK      (ETH_OPEN_AUTO|ETH_OPEN_10|ETH_OPEN_100|ETH_OPEN_HDUPLEX|ETH_OPEN_FDUPLEX|ETH_OPEN_MDIX_AUTO)
    // flags to be used for the Ethernet link
    // adjust to your needs. ETH_OPEN_AUTO (auto negotiation) strongly recommended.
    // Note: if Auto MDIX is not enabled, ETH_OPEN_MDIX_SWAP or ETH_OPEN_MDIX_NORM could be selected

		

#endif	// MAC_EMBEDDED_PIC32


/*****************************************************************************
 * End of Definitions
 *****************************************************************************/


#endif  // _TCPIP_BSD_CONFIG_H_

