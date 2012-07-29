/********************************************************************
 * FileName:		dhcp_private.h
 * Dependencies:
 * Company:			Microchip Technology, Inc.
 *
 * Software License Agreement:
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
 ********************************************************************/
#ifndef _DHCP_PRIVATE_HEADER_FILE
#define _DHCP_PRIVATE_HEADER_FILE

/*******************************************************************
 * Constant data
 *******************************************************************/
#define DHCP_TIMEOUT                    3       // timeout in seconds
#define MAX_NUM_RETRY					(5)
#define MAX_TRY_TIME					(60)
#define DHCP_MAX_PKT_LEN				(576)			//per RFC2131

#define DHCP_CLIENT_PORT                (68)
#define DHCP_SERVER_PORT                (67)

// DHCP Message Field Values
#define BOOT_REQUEST                    (1)
#define BOOT_REPLY                      (2)
#define HW_TYPE                         (1)
#define LEN_OF_HW_TYPE                  (6)

// DHCP Message Option Values
#define DHCP_SUBNET_MASK                (1)
#define DHCP_PARAM_IPv4_ADDRESS_LEN     (4)
#define DHCP_ROUTER                     (3)

#define DHCP_PARAM_REQUEST_IP_ADDRESS   (50)

#define DHCP_PARAM_IP_LEASE_TIME        (51)
#define DHCP_PARAM_IP_LEASE_TIME_LEN    (4)

#define DHCP_MESSAGE_TYPE               (53)
#define DHCP_MESSAGE_TYPE_LEN           (1)

#define DHCP_UNKNOWN_MESSAGE            (0)
#define DHCP_DISCOVER_MESSAGE           (1)
#define DHCP_OFFER_MESSAGE              (2)
#define DHCP_REQUEST_MESSAGE            (3)
#define DHCP_DECLINE_MESSAGE            (4)
#define DHCP_ACK_MESSAGE                (5)
#define DHCP_NAK_MESSAGE                (6)
#define DHCP_RELEASE_MESSAGE            (7)

#define DHCP_SERVER_IDENTIFIER          (54)

#define DHCP_PARAM_REQUEST_LIST         (55)
#define DHCP_PARAM_REQUEST_LIST_LEN     (2)

#define DHCP_END_OPTION                 (255)

/*********************************************************************
        DHCP PACKET FORMAT AS PER RFC 1541

   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     op (1)    |   htype (1)   |   hlen (1)    |   hops (1)    |
   +---------------+---------------+---------------+---------------+
   |                            xid (4)                            |
   +-------------------------------+-------------------------------+
   |           secs (2)            |           flags (2)           |
   +-------------------------------+-------------------------------+
   |                          ciaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          yiaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          siaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          giaddr  (4)                          |
   +---------------------------------------------------------------+
   |                                                               |
   |                          chaddr  (16)                         |
   |                                                               |
   |                                                               |
   +---------------------------------------------------------------+
   |                                                               |
   |                          sname   (64)                         |
   +---------------------------------------------------------------+
   |                                                               |
   |                          file    (128)                        |
   +---------------------------------------------------------------+
   |                                                               |
   |                          options (312)                        |
   +---------------------------------------------------------------+

 ********************************************************************/

typedef struct _DHCP_MSG_HEADER
{
    BYTE    	Op;
    BYTE    	Htype;
    BYTE    	Hlen;
    BYTE    	Hops;
    WORD    	Xid[2];
    WORD    	Secs;
    WORD_VAL    Flags;
    IP_ADDR 	Ciaddr;
    IP_ADDR 	Yiaddr;
    IP_ADDR 	Siaddr;
    IP_ADDR 	Giaddr;
    BYTE    	Chaddr[16];
    BYTE    	Sname[64];
    BYTE    	file[128];
} DHCP_MSG_HEADER;

typedef struct _DHCP_PACKET
{
	DHCP_MSG_HEADER	dhcpHeader;
	BYTE			dhcpOptions[24]; 		//[Cookie+  Msg Type +  Req List + Req IP + Srv ID + End]		
} DHCP_PACKET;


#endif

