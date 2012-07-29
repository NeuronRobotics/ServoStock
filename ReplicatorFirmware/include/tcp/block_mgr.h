/*********************************************************************
 *
 *                  Memory Block Manager for BSD TCPIP Stack
 *
 *********************************************************************
 * FileName:        block_mgr.h
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
 * $Id: block_mgr.h,v 1.3 2006/09/12 18:38:36 C12770 Exp $
 *
 ********************************************************************/

#ifndef __BLOCK_MGR_H
#define __BLOCK_MGR_H


NET_PKT* AllocSocketBuffer( UINT16 hdrLen,  UINT16 loadLen, NET_PKT_FLAGS flags ); //creates buffer with extra space for ip and mac headers
NET_PKT* AllocPacketBuffer( UINT16 hdrLen, UINT16 loadLen, NET_PKT_FLAGS flags); //creates buffer for BfrSize
void DeAllocateBuffer( NET_PKT* pBfr );


// memory allocation routines
// could be overridden if needed

typedef void*(*pBsdAllocFnc)(size_t);       // allocation function
typedef void(*pBsdFreeFnc)(void*);          // de-allocation function


void __attribute__((weak))              BsdBuffMgrSetAllocFnc(pBsdAllocFnc fnc);    // sets the allocation function; default is malloc
void __attribute__((weak))              BsdBuffMgrSetFreeFnc(pBsdFreeFnc fnc);      // sets the de-allocation function; default is free
void __attribute__((weak))              BsdBuffMgrSetHeapSize(size_t hSize);        // sets the heap size


int __attribute__((weak))               BsdBuffMgrInit();
void __attribute__((weak))              BsdBuffMgrClose(void);

void* __attribute__((weak))             BsdBuffMgrAlloc( size_t BfrSize );
void __attribute__((weak))              BsdBuffMgrFree( void* pBfr );



#endif
