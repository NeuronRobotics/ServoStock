/*********************************************************************
 *
 *                  System Services
 *
 *********************************************************************
 * FileName:        system_services.c
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

#include <plib.h>

#include "hardware_profile.h"
#include "system_services.h"


// definitions
// 


#if (TICKS_PER_SECOND < 10 || TICKS_PER_SECOND > 255)
    #error Invalid TICKS_PER_SECONDS specified.
#endif



typedef struct _tag_TickNode
{
        struct _tag_TickNode*   next;
        pSystemTickHandler      tFunc;      // function to be called
        int                     rate;       // rate of call
        int                     currCnt;    // current count value
}sTickNode;     // system tick registration node


// global data
// 
volatile TICK                   SystemTickCount = 0;

// local data
// 
static unsigned int             _SystemTickUpdateRate;
static unsigned int             _SystemTickResolution;


static sTickNode*               _tickHead = 0;
static sTickNode*               _tickTail = 0;



/********************************** System Interface functions *****************************/



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
unsigned int GetSystemClock(void)
{
	__OSCCONbits_t	osccon;

	osccon=OSCCONbits;	// read current configuration
	if(osccon.COSC==3)
	{	// Primary PLL
		unsigned int sysClock;
		unsigned int pllInDiv, pllMult, oDiv;
		
		// input divider
		pllInDiv=1+DEVCFG2bits.FPLLIDIV;	
		if(pllInDiv==7)
		{
			pllInDiv=10;
		}
		else if(pllInDiv==8)
		{
			pllInDiv=12;
		}
		sysClock=SYS_XTAL_FREQ/pllInDiv;
		
		// pll multiplier
		pllMult=15+osccon.PLLMULT;
		if(pllMult==22)
		{
			pllMult=24;
		}
		sysClock*=pllMult;
		// finally the output divider
		oDiv=osccon.PLLODIV;
		sysClock>>=oDiv;

		return sysClock;
	}

	return 0;	// not implemented yet!
	

}


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
unsigned int GetPeripheralClock(void)
{
	return GetSystemClock()>>mOSCGetPBDIV();
}


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
 * Note:            Normal value for ticksPerSec should be 100 (i.e. interrupt every 10 ms).
 ********************************************************************/
BOOL SystemTickInit(UINT sysClock, UINT ticksPerSec)
{
	INTEnable(INT_CT, INT_DISABLED);

    _SystemTickResolution=ticksPerSec;
    _SystemTickUpdateRate=sysClock/(2*ticksPerSec);
    _tickHead = 0;
    _tickTail = 0;
	
	INTClearFlag(INT_CT);
	OpenCoreTimer(_SystemTickUpdateRate);
	INTSetVectorPriority(INT_CORE_TIMER_VECTOR, PRI_LEVEL(TICK_IPL));
	INTSetVectorSubPriority(INT_CORE_TIMER_VECTOR, SUBPRI_LEVEL(TICK_SIPL));
	INTEnable(INT_CT, INT_ENABLED);


	return TRUE;
	
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
UINT SystemTickGetResolution(void)
{
    return _SystemTickResolution;
}

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
BOOL SystemTickRegisterHandler(pSystemTickHandler tickHandler, int rate)
{
        sTickNode*  newNode=0;

        if(tickHandler && rate)
        {
            newNode=malloc(sizeof(*newNode));
            if(newNode)
            {
                newNode->tFunc=tickHandler;
                newNode->rate=newNode->currCnt=rate;
                newNode->next=0;

                INTEnable(INT_CT, INT_DISABLED);
                // add tail
                if(_tickTail==0)
                {
                    _tickHead=_tickTail=newNode;
                }
                else
                {
                    _tickTail->next=newNode;
                    _tickTail=newNode;
                }

                INTEnable(INT_CT, INT_ENABLED);
            }
        }

    return newNode!=0;    
        
}


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
BOOL SystemTickUnRegisterHandler(pSystemTickHandler tickHandler)
{
        sTickNode   *pTick, *prev;

        if(_tickHead==0)
        {
            return 0;
        }

        INTEnable(INT_CT, INT_DISABLED);
        
        if((pTick=_tickHead)->tFunc==tickHandler)
        {   // remove head
            if(_tickHead==_tickTail)
            {
                _tickHead=_tickTail=0;
            }
            else
            {
                _tickHead=pTick->next;
            }
        }        
        else for(prev=_tickHead, pTick=_tickHead->next; pTick!=0; prev=pTick, pTick=pTick->next)
        {   // search within the list
            if(pTick->tFunc==tickHandler)
            {   // found it
                prev->next=pTick->next;
                if(_tickTail==pTick)
                {   // adjust tail
                    _tickTail=prev;
                }
                break;
            }
        }

        INTEnable(INT_CT, INT_ENABLED);

    if(pTick)
    {
        free(pTick);
    }

    return pTick!=0;        
        
}



/*********************************************************************
 * Function:        void _ISR CoreTimerIntHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          SystemTickCount variable is updated
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void __ISR(_CORE_TIMER_VECTOR, IPL(TICK_IPL)) CoreTimerIntHandler(void)
{
    sTickNode   *pTick;

	mCTClearIntFlag();
	SystemTickCount ++;
    
    for(pTick=_tickHead; pTick!=0; pTick=pTick->next)
    {
        if(--pTick->currCnt==0)
        {
            pTick->currCnt=pTick->rate;
            (*pTick->tFunc)(SystemTickCount);
        }
    }

	UpdateCoreTimer(_SystemTickUpdateRate);	
}








