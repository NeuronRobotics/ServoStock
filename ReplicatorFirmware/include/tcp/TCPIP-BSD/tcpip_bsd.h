/*********************************************************************
 *
 *            BSD TCPIP API Header File
 *
 *********************************************************************
 * FileName:        tcpip_bsd.h
 * Description:     API for BSD TCPIP Stack
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
 * This file includes parts which are Copyright (c) 1982-1986 Regents
 * of the University of California.  All rights reserved.  The
 * Berkeley Software License Agreement specifies the terms and
 * conditions for redistribution.
 *
 *
*/

#ifndef _TCPIP_BSD_H_
#define _TCPIP_BSD_H_

// general MCHP definitions
#include <GenericTypeDefs.h>


// TCPIP BSD standard socket API
#include "socket.h"

// TCPIP BSD stack build time configuration parameters
#include "tcpip_bsd_config.h"

// TCPIP BSD stack control API
#include "tcpip_bsd_control.h"

// TCPIP BSD HTTP API
#include "http.h"

// TCPIP BSD DHCP API
#include "dhcp.h"

// TCPIP BSD FTP API
#include "ftp.h"

// TCPIP BSD SNMP API
#include "snmp.h"

#endif  // _TCPIP_BSD_H_

