/*********************************************************************
 *
 *                  Timer Tick Manager
 *
 *********************************************************************
 * FileName:        Tick.h
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
 * $Id: Tick.c,v 1.5 2006/10/24 16:39:06 C12923 Exp $
 *
 ********************************************************************/

#define TICK_INCLUDE

#include "_tcpip_common.h"


// local prototypes
#ifdef _EMBEDDED_ETHC
static void _TcpTickHandler(TICK currSysTick);        // TCP tick handler
#endif  // _EMBEDDED_ETHC

/*********************************************************************
 * Function:        void TCPTickInit(UINT sysClock, UINT ticksPerSec)
 *
 * PreCondition:    None
 *
 * Input:           tcpTicksPerSec - number of ticks per second for the TCP clock
 *
 * Output:          TRUE if initialization succeeded,
 *                  FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        Initializes the TCP tick counter.
 *
 * Note:            None
 ********************************************************************/
BOOL TCPTickInit(UINT tcpTicksPerSec)
{
#ifdef _EMBEDDED_ETHC
    unsigned int    tcpTickRate;
    
    tcpTickRate=(SystemTickGetResolution()+tcpTicksPerSec-1)/tcpTicksPerSec;
    return SystemTickRegisterHandler(_TcpTickHandler, tcpTickRate);
#else
    return TRUE;
#endif
	
}

/*********************************************************************
 * Function:        void TCPTickClose(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Closes the TCP tick counter.
 *
 * Note:            None
 ********************************************************************/
void TCPTickClose(void)
{
#ifdef _EMBEDDED_ETHC
    SystemTickUnRegisterHandler(_TcpTickHandler);
#endif

}



/*********************************************************************
 * Function:        void  _TcpTickHandler(TICK currSysTick)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TickCount variable is updated
 *
 * Side Effects:    None
 *
 * Overview:        Called from within the System Tick ISR
 *
 * Note:            None
 ********************************************************************/
#ifdef _EMBEDDED_ETHC
static void _TcpTickHandler(TICK currSysTick)        // TCP tick handler
{

	if((_TcpEnabledEvents&TCPIP_EV_TICK) && !(_TcpPendingEvents&TCPIP_EV_TICK))
	{
        INTEnable(INT_ETHERNET, INT_DISABLED);		// stop Eth ints shortly		
        _TcpPendingEvents|=TCPIP_EV_TICK;
        INTEnable(INT_ETHERNET, INT_ENABLED);		// restart ints

        (*_TcpNotifyFnc)(_TcpPendingEvents);		// let the user know
	}
}
#endif	// _EMBEDDED_ETHC





