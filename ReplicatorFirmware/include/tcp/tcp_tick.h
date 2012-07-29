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
 * $Id: Tick.h,v 1.4 2006/10/24 16:39:06 C12923 Exp $
 *
 ********************************************************************/

#ifndef TICK_H
#define TICK_H



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
 * Note:            Uses TCP_TICKS_PER_SECOND value from TCPIP-BSD-Config.h
 ********************************************************************/
BOOL TCPTickInit(UINT tcpTicksPerSec);

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
void TCPTickClose(void);


#endif
