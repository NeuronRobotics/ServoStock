/*********************************************************************
 *
 *            MAC Configuration API Header File
 *
 *********************************************************************
 * FileName:        tcpip_bsd_mac_control.h
 * Description: 	MAC Layer API header
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


/* Note: These interface functions give access to low level MAC configuration.
 * Include the header file in your project if you need to dynamically override
 * the settings in TCPIP-BSD-Config.h.
*/ 

#ifndef _TCPIP_BSD_MAC_CONTROL_H_
#define _TCPIP_BSD_MAC_CONTROL_H_

#include "eth_phy.h"

void    MACSetOpenFlags(eEthOpenFlags oFlags);
void    MACSetPhyConfigFlags(eEthPhyCfgFlags cfgFlags);
void    MACSetRxFilters(eEthRxFilters rxFilters);
void    MACSetRxDescriptors(int rxDescriptors, int rxBuffSize);
void    MACSetTxDescriptors(int txDescriptors);


#endif  // _TCPIP_BSD_MAC_CONTROL_H_

