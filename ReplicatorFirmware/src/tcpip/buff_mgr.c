/*********************************************************************
 *
 *                  Buffer Memory Allocation for Microchip BSD TCP/IP Stack
 *
 *********************************************************************
 * FileName:        buff_mgr.c
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
 ********************************************************************/
#include <stdlib.h>
#include "_tcpip_common.h"

// definitions

typedef struct _tag_headNode
{
		
    struct _tag_headNode*	next;
    size_t			        units;
}_headNode __attribute__ ((aligned (8)));;


#define	BUFF_MGR_MIN_BLK_USIZE  	2	// avoid tiny blocks having units <=  value. 

// local data
//

static _headNode*   _heapHead=0;                     // the heap itself, dinamically allocated
static _headNode*   _heapTail=0;

#ifdef DEBUG
    static _headNode*   _heapStart;                     // debug checkpoint     
   static _headNode*   _heapEnd;                       // debug checkpoint     
    static int          _heapAllocatedUnits=0;          // how many units allocated out there
#endif

static size_t       _heapUnits = ((BUFF_MGR_HEAP_SIZE +sizeof(_headNode)-1)/sizeof(_headNode));        // default size of the heap, units 



static pBsdAllocFnc     _heap_alloc=malloc;       // default allocation function
static pBsdFreeFnc      _heap_free=free;          // default de-allocation function



// functions


void __attribute__((weak)) BsdBuffMgrSetAllocFnc(pBsdAllocFnc fnc)
{
    _heap_alloc=fnc;
}

void __attribute__((weak)) BsdBuffMgrSetFreeFnc(pBsdFreeFnc fnc)
{
    _heap_free=fnc;    
}


void __attribute__((weak)) BsdBuffMgrSetHeapSize(size_t hSize)
{
    _heapUnits=(hSize + sizeof(_headNode) - 1) / sizeof(_headNode);              // adjust the heap size to multiple of heads
}


int __attribute__((weak)) BsdBuffMgrInit(void)
{
    _heapHead=(_headNode*)(*_heap_alloc)(_heapUnits*sizeof(_headNode));
    if(_heapHead)
    {
        _heapHead->units=_heapUnits;
        _heapHead->next=0;
        _heapTail=_heapHead;
    #ifdef DEBUG
        _heapStart=_heapHead;
        _heapEnd=_heapHead+_heapUnits;
    #endif
    }
    
    return _heapHead!=0;
}

// deallocates the heap
// NOTE: no check is done if some blocks are still in use!
void __attribute__((weak)) BsdBuffMgrClose(void)
{
            
    if(_heapHead)
    {
    #ifdef DEBUG
        if(_heapAllocatedUnits!=0 || _heapHead!=_heapStart || _heapHead->units!=_heapUnits)
        {
            _BsdASSERT(0);  //  deallocating a heap not completely de-allocated or corrupted
        }
    #endif
        (*_heap_free)(_heapHead);
        _heapHead=_heapTail=0;
    }
    
}

void* __attribute__((weak)) BsdBuffMgrAlloc(size_t nbytes)
{
	_headNode	*ptr,*prev;
	size_t	nunits;

	if(!nbytes)
	{
		return 0;
	}
	
	nunits=(nbytes+sizeof(_headNode)-1)/sizeof(_headNode)+1;	// allocate units   
	prev=0;
    
	for(ptr=_heapHead; ptr!=0; prev=ptr, ptr=ptr->next)
	{
		if(ptr->units>=nunits)
		{
			if(ptr->units-nunits<=BUFF_MGR_MIN_BLK_USIZE)
			{
				nunits=ptr->units;	// get the whole block
			}

            if(ptr->units==nunits)
			{   // exact match
				if(prev)
				{
					prev->next=ptr->next;
				}
				else
				{
					_heapHead=ptr->next;
                    prev=_heapHead;
				}

                if(_heapTail==ptr)
                {
                    _heapTail=prev;
                }
			}
			else
			{   // larger than we need
				ptr->units-=nunits;
				ptr+=ptr->units;
				ptr->units=nunits;
			}

        #ifdef DEBUG
            _heapAllocatedUnits+=nunits;
        #endif           
            return ptr+1;
		}
	}

    return 0;
}

void __attribute__((weak)) BsdBuffMgrFree(void* aptr)
{  
	_headNode	*hdr,*ptr;

    if(!aptr)
	{
        return;
    }

    ptr=(_headNode*)aptr-1;
    
#ifdef DEBUG
    if(ptr<_heapStart || ptr+ptr->units>_heapEnd)
    {
        _BsdASSERT(0);  // not one of our supplied pointers!!!
    }
    _heapAllocatedUnits-=ptr->units;
#endif
	

    if(!_heapHead)
    {
        ptr->next=0;
        _heapHead=_heapTail=ptr;
    }
    else if(ptr<_heapHead)
    {   // put it in front
        if(ptr+ptr->units==_heapHead)
        {   // compact
            ptr->units+=_heapHead->units;
            ptr->next=_heapHead->next;
            if(_heapTail==_heapHead)
            {
                _heapTail=ptr;
            }
        }
        else
        {
            ptr->next=_heapHead;
        }
        _heapHead=ptr;    // new head
    }
    else if(ptr>_heapTail)
    {   // append tail
        if(_heapTail+_heapTail->units==ptr)
        {   // compact
            _heapTail->units+=ptr->units;
        }
        else
        {
            _heapTail->next=ptr;
            ptr->next=0;
            _heapTail=ptr;
        }
    }
    else
    {   // somewhere in the middle
        for(hdr=_heapHead; hdr!=0; hdr=hdr->next)
        {
            if(hdr<ptr && ptr<hdr->next)
            {   // found a place
                if(ptr+ptr->units==hdr->next)
                {   // compact right
                    ptr->units+=hdr->next->units;
                    ptr->next=hdr->next->next;
                    if(_heapTail==hdr->next)
                    {
                        _heapTail=ptr;
                    }
                }
                else
                {
                #ifdef DEBUG
                    if(ptr+ptr->units>hdr->next)
                    {
                        _BsdASSERT(0);  //  corrupted pointer!!!
                    }
                #endif
                    ptr->next=hdr->next;
                }
                
                // compact left
                if(hdr+hdr->units==ptr)
                {
                    hdr->units+=ptr->units;
                    hdr->next=ptr->next;
                    if(_heapTail==ptr)
                    {
                        _heapTail=hdr;
                    }
                }
                else
                {
                #ifdef DEBUG
                    if(hdr+hdr->units>ptr)
                    {
                        _BsdASSERT(0);  // corrupted pointer!!!
                    }
                #endif
                    hdr->next=ptr;
                }

                return;                
            }
        }
        
        _BsdASSERT(0);  // corrupted pointer!!!

    }

}



