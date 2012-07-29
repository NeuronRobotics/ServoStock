/*********************************************************************
 *
 *                  Hardware definitions
 *
 *********************************************************************
 * FileName:        hardware_profile.h
 * Dependencies:
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * Microchip Audio Library � PIC32 Software.
 * Copyright � 2008 Microchip Technology Inc.  All rights reserved.
 * 
 * Microchip licenses the Software for your use with Microchip microcontrollers
 * and Microchip digital signal controllers pursuant to the terms of the
 * Non-Exclusive Software License Agreement accompanying this Software.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION,
 * ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS
 * FOR A PARTICULAR PURPOSE.
 * MICROCHIP AND ITS LICENSORS ASSUME NO RESPONSIBILITY FOR THE ACCURACY,
 * RELIABILITY OR APPLICATION OF THE SOFTWARE AND DOCUMENTATION.
 * IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED
 * UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH
 * OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL,
 * SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS
 * OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY,
 * SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED
 * TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *
 ********************************************************************/


#ifndef _HARDWAREPROFILE_H_
#define _HARDWAREPROFILE_H_

#define ETH_STARTER_KIT

#if defined (ETH_STARTER_KIT)
	#define		SYS_XTAL_FREQ		8000000 	// external Xtal, Hz
	#define		PHY_ADDRESS		    0x1		    // address our NAT DP83848C PHY is mapped to
#else
	#error "This project is supposed to run on EThernet Starter Kit. Define the ETH_STARTER_KIT symbol!"
#endif

/*****************************************************************************
 * The number of ticks per second.  This is used to define timeouts
 * and must be defined before them.
 * This implementation uses the core timer
 *****************************************************************************/
#if !defined(TICKS_PER_SECOND)
	#define TICKS_PER_SECOND        100
#endif


/*****************************************************************************
 * The interrupt priority (1-lowest to 7-highest) and sub-priority (0 to 3) for the timer used to generate the ticks
 *****************************************************************************/
#define	TICK_IPL		4
#define	TICK_SIPL		1


/*****************************************************************************
 * Define this symbol to use the external ENC28j60 Ethernet Controller on any PIC32MX processor.
 * It is overridden by the MAC_EMBEDDED_PIC32, if defined 
 *****************************************************************************/
//#define	MAC_ENC28J60


/*****************************************************************************
 * Define this symbol to use the embedded Ethernet Controller on PIC32MX7 family
 * Takes precedence, if defined, over MAC_ENC28J60 
 *****************************************************************************/
#define	MAC_EMBEDDED_PIC32

    /* The embedded Ethernet controller uses an external PHY
     * Here are configuration options
    */
        #define	PHY_RMII			        // PHY runs in RMII mode

        #define	PHY_CONFIG_ALTERNATE		// the alternate configuration used, else default




#endif	// _HARDWAREPROFILE_H_

