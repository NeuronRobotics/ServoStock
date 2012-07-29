/*********************************************************************
 *
 *                  System Services
 *
 *********************************************************************
 * FileName:        system_services.h
 * Dependencies:
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * Microchip Audio Library – PIC32 Software.
 * Copyright © 2008 Microchip Technology Inc.  All rights reserved.
 * 
 * Microchip licenses the Software for your use with Microchip microcontrollers
 * and Microchip digital signal controllers pursuant to the terms of the
 * Non-Exclusive Software License Agreement accompanying this Software.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY
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


#ifndef _SYSTEM_SERVICES_H_
#define _SYSTEM_SERVICES_H_

#include <GenericTypeDefs.h>

/********************************
 *   Macros to convert the interrupt priorities from numbers to priority levels and ipl
 **********************************/

#define	_PRI_LEVEL(lvl)		INT_PRIORITY_LEVEL_ ## lvl
#define	PRI_LEVEL(lvl)		_PRI_LEVEL(lvl)


#define	_SUBPRI_LEVEL(slvl)	INT_SUB_PRIORITY_LEVEL_ ## slvl
#define	SUBPRI_LEVEL(slvl)	_SUBPRI_LEVEL(slvl)

#define	_IPL(lvl)		ipl ## lvl
#define	IPL(lvl)		_IPL(lvl)

/****************** System Interface functions *************************************/
/*********************************************************************
 * Function:        unsigned int GetSystemClock(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Current system running frequency
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the system running clock frequency.
 *
 * Note:            None
 ********************************************************************/
unsigned int    GetSystemClock(void);


/*********************************************************************
 * Function:        unsigned int GetPeripheralClock(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Current peripheral bus frequency
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the peripheral bus clock frequency.
 *
 * Note:            None
 ********************************************************************/
unsigned int    GetPeripheralClock(void);

#define TickGetDiff(NewTick, StartTick)       (NewTick - StartTick)


/**********************
 *  System Tick
*************************/

typedef unsigned int    TICK;

extern volatile TICK   SystemTickCount;




typedef void (*pSystemTickHandler)(TICK currSysTick);        // system tick registration handler


/*********************************************************************
 * Function:        void SystemTickInit(UINT sysClock, UINT ticksPerSec)
 *
 * PreCondition:    None
 *
 * Input:           sysClock    - system clock frequency, Hz
 *                  ticksPerSec - number of ticks to generate per second
 *
 * Output:          TRUE if initialization succeeded,
 *                  FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        Initializes the system tick counter.
 *
 * Note:            - Normal value for ticksPerSec should be 100 (i.e. interrupt every 10 ms).
 *                  - This implementation uses the core timer.
 *                    It takes exclusive control of the ISR for this resource.
 *                    This may eventually change as it will be integrated at the system level.
 ********************************************************************/
BOOL SystemTickInit(UINT sysClock, UINT ticksPerSec);


/*********************************************************************
 * Function:        TICK SystemTickGet(void)
 *
 * PreCondition:    SystemTickInit should have been called
 *
 * Input:           None
 *
 * Output:          Current value of the system tick is returned
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
extern __inline__ TICK __attribute__((always_inline)) SystemTickGet(void)
{
    return SystemTickCount;
}


/*********************************************************************
 * Function:        UINT SystemTickGetResolution(void)
 *
 * PreCondition:    SystemTickInit should have been called
 *
 * Input:           None
 *
 * Output:          Current value of the system tick resolution
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the number of system ticks per second
 *
 * Note:            None
 ********************************************************************/
UINT        SystemTickGetResolution(void);



/*********************************************************************
 * Function:        TICK SystemTickRegisterHandler(void)
 *
 * PreCondition:    SystemTickInit should have been called
 *
 * Input:           tickHandler - handler to be called from the tick ISR
 *                  rate        - rate of call 
 *
 * Output:          TRUE if the registration succeeded, false otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function registrates a handler with the SystemTick ISR
 *                  The handler will be called from within this ISR at the desired rate. 
 *
 * Note:            - All the registered handler are called in turn, sequentially.
 *                    Therefore they have to be as short as possible.
 *                  - This handler is called from within an ISR. All the 
 *                    ISR code restrictions apply.
 *                  - The SystemTickRegisterHandler() should not be called from within an ISR.
 ********************************************************************/
BOOL        SystemTickRegisterHandler(pSystemTickHandler tickHandler, int rate);

/*********************************************************************
 * Function:        TICK SystemTickUnRegisterHandler(void)
 *
 * PreCondition:    SystemTickInit, SystemTickRegisterHandler should have been called
 *
 * Input:           tickHandler - handler to be unregistered from the tick ISR
 *
 * Output:          TRUE if the un-registration succeeded, false otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function in-registrates a handler previously registered
 *                  with the SystemTick ISR.
 *
 * Note:            The SystemTickUnRegisterHandler() should not be called from within an ISR.
 ********************************************************************/
BOOL        SystemTickUnRegisterHandler(pSystemTickHandler tickHandler);



#endif  // _SYSTEM_SERVICES_H_

