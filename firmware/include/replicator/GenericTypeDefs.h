/*******************************************************************

                  Generic Type Definitions

********************************************************************
 FileName:        GenericTypeDefs.h
 Dependencies:    None
 Processor:       PIC10, PIC12, PIC16, PIC18, PIC24, dsPIC, PIC32
 Compiler:        MPLAB C Compilers for PIC18, PIC24, dsPIC, & PIC32
                  Hi-Tech PICC PRO, Hi-Tech PICC18 PRO
 Company:         Microchip Technology Inc.

 Software License Agreement

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") is intended and supplied to you, the Company's
 customer, for use solely and exclusively with products manufactured
 by the Company.

 The software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.1   09/11/06     Add base signed types
  1.2   02/28/07     Add QWORD, LONGLONG, QWORD_VAL
  1.3   02/06/08     Add def's for PIC32
  1.4   08/08/08     Remove LSB/MSB Macros, adopted by Peripheral lib
  1.5   08/14/08     Simplify file header
  Draft 2.0   07/13/09     Updated for new release of coding standards
*******************************************************************/

#ifndef __GENERIC_TYPE_DEFS_H_
#define __GENERIC_TYPE_DEFS_H_

#ifdef __cplusplus
extern "C"
  {
#endif

/* Specify an extension for GCC based compilers */
#if defined(__GNUC__)
#define __EXTENSION __extension__
#else
#define __EXTENSION
#endif

/* get compiler defined type definitions (NULL, size_t, etc) */
#include <stddef.h>

typedef enum _boolean { false = 0, true } BOOL;    /* Undefined size */
typedef enum _BIT { CLEAR = 0, SET } BIT;

#define PUBLIC                                  /* Function attributes */
#define PROTECTED
#define PRIVATE   static

/* int32_t is processor specific in length may vary in size */
typedef signed int          INT;
typedef signed char         INT8;
typedef signed short int    INT16;
typedef signed long int     INT32;

/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
#if !defined(__18CXX)
__EXTENSION typedef signed long long    INT64;
#endif

/* uint32_t is processor specific in length may vary in size */
typedef unsigned int        UINT;
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
/* 24-bit type only available on C18 */
#if defined(__18CXX)
typedef unsigned short long UINT24;
#endif
typedef unsigned long int   UINT32;     /* other name for 32-bit integer */
/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
#if !defined(__18CXX)
__EXTENSION typedef unsigned long long  UINT64;
#endif

typedef union
{
    uint8_t Val;
    struct
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
    } bits;
} UINT8_VAL, UINT8_BITS;

typedef union
{
    uint16_t Val;
    uint8_t v[2];
    struct
    {
        uint8_t LB;
        uint8_t HB;
    } byte;
    struct
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
        __EXTENSION uint8_t b8:1;
        __EXTENSION uint8_t b9:1;
        __EXTENSION uint8_t b10:1;
        __EXTENSION uint8_t b11:1;
        __EXTENSION uint8_t b12:1;
        __EXTENSION uint8_t b13:1;
        __EXTENSION uint8_t b14:1;
        __EXTENSION uint8_t b15:1;
    } bits;
} UINT16_VAL, UINT16_BITS;

/* 24-bit type only available on C18 */
#if defined(__18CXX)
typedef union
{
    UINT24 Val;
    uint8_t v[3];
    struct
    {
        uint8_t LB;
        uint8_t HB;
        uint8_t UB;
    } byte;
    struct
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
        __EXTENSION uint8_t b8:1;
        __EXTENSION uint8_t b9:1;
        __EXTENSION uint8_t b10:1;
        __EXTENSION uint8_t b11:1;
        __EXTENSION uint8_t b12:1;
        __EXTENSION uint8_t b13:1;
        __EXTENSION uint8_t b14:1;
        __EXTENSION uint8_t b15:1;
        __EXTENSION uint8_t b16:1;
        __EXTENSION uint8_t b17:1;
        __EXTENSION uint8_t b18:1;
        __EXTENSION uint8_t b19:1;
        __EXTENSION uint8_t b20:1;
        __EXTENSION uint8_t b21:1;
        __EXTENSION uint8_t b22:1;
        __EXTENSION uint8_t b23:1;
    } bits;
} UINT24_VAL, UINT24_BITS;
#endif

typedef union
{
    uint32_t Val;
    uint16_t w[2];
    uint8_t  v[4];
    struct
    {
        uint16_t LW;
        uint16_t HW;
    } word;
    struct
    {
        uint8_t LB;
        uint8_t HB;
        uint8_t UB;
        uint8_t MB;
    } byte;
    struct
    {
        UINT16_VAL low;
        UINT16_VAL high;
    }wordUnion;
    struct
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
        __EXTENSION uint8_t b8:1;
        __EXTENSION uint8_t b9:1;
        __EXTENSION uint8_t b10:1;
        __EXTENSION uint8_t b11:1;
        __EXTENSION uint8_t b12:1;
        __EXTENSION uint8_t b13:1;
        __EXTENSION uint8_t b14:1;
        __EXTENSION uint8_t b15:1;
        __EXTENSION uint8_t b16:1;
        __EXTENSION uint8_t b17:1;
        __EXTENSION uint8_t b18:1;
        __EXTENSION uint8_t b19:1;
        __EXTENSION uint8_t b20:1;
        __EXTENSION uint8_t b21:1;
        __EXTENSION uint8_t b22:1;
        __EXTENSION uint8_t b23:1;
        __EXTENSION uint8_t b24:1;
        __EXTENSION uint8_t b25:1;
        __EXTENSION uint8_t b26:1;
        __EXTENSION uint8_t b27:1;
        __EXTENSION uint8_t b28:1;
        __EXTENSION uint8_t b29:1;
        __EXTENSION uint8_t b30:1;
        __EXTENSION uint8_t b31:1;
    } bits;
} UINT32_VAL;

/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
#if !defined(__18CXX)
typedef union
{
    uint64_t Val;
    uint32_t d[2];
    uint16_t w[4];
    uint8_t v[8];
    struct
    {
        uint32_t LD;
        uint32_t HD;
    } dword;
    struct
    {
        uint16_t LW;
        uint16_t HW;
        uint16_t UW;
        uint16_t MW;
    } word;
    struct
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
        __EXTENSION uint8_t b8:1;
        __EXTENSION uint8_t b9:1;
        __EXTENSION uint8_t b10:1;
        __EXTENSION uint8_t b11:1;
        __EXTENSION uint8_t b12:1;
        __EXTENSION uint8_t b13:1;
        __EXTENSION uint8_t b14:1;
        __EXTENSION uint8_t b15:1;
        __EXTENSION uint8_t b16:1;
        __EXTENSION uint8_t b17:1;
        __EXTENSION uint8_t b18:1;
        __EXTENSION uint8_t b19:1;
        __EXTENSION uint8_t b20:1;
        __EXTENSION uint8_t b21:1;
        __EXTENSION uint8_t b22:1;
        __EXTENSION uint8_t b23:1;
        __EXTENSION uint8_t b24:1;
        __EXTENSION uint8_t b25:1;
        __EXTENSION uint8_t b26:1;
        __EXTENSION uint8_t b27:1;
        __EXTENSION uint8_t b28:1;
        __EXTENSION uint8_t b29:1;
        __EXTENSION uint8_t b30:1;
        __EXTENSION uint8_t b31:1;
        __EXTENSION uint8_t b32:1;
        __EXTENSION uint8_t b33:1;
        __EXTENSION uint8_t b34:1;
        __EXTENSION uint8_t b35:1;
        __EXTENSION uint8_t b36:1;
        __EXTENSION uint8_t b37:1;
        __EXTENSION uint8_t b38:1;
        __EXTENSION uint8_t b39:1;
        __EXTENSION uint8_t b40:1;
        __EXTENSION uint8_t b41:1;
        __EXTENSION uint8_t b42:1;
        __EXTENSION uint8_t b43:1;
        __EXTENSION uint8_t b44:1;
        __EXTENSION uint8_t b45:1;
        __EXTENSION uint8_t b46:1;
        __EXTENSION uint8_t b47:1;
        __EXTENSION uint8_t b48:1;
        __EXTENSION uint8_t b49:1;
        __EXTENSION uint8_t b50:1;
        __EXTENSION uint8_t b51:1;
        __EXTENSION uint8_t b52:1;
        __EXTENSION uint8_t b53:1;
        __EXTENSION uint8_t b54:1;
        __EXTENSION uint8_t b55:1;
        __EXTENSION uint8_t b56:1;
        __EXTENSION uint8_t b57:1;
        __EXTENSION uint8_t b58:1;
        __EXTENSION uint8_t b59:1;
        __EXTENSION uint8_t b60:1;
        __EXTENSION uint8_t b61:1;
        __EXTENSION uint8_t b62:1;
        __EXTENSION uint8_t b63:1;
    } bits;
} UINT64_VAL;
#endif /* __18CXX */

/***********************************************************************************/

/* Alternate definitions */
typedef void                    VOID;

typedef char                    CHAR8;
typedef unsigned char           UCHAR8;

typedef unsigned char           BYTE;                           /* 8-bit unsigned  */
typedef unsigned short int      WORD;                           /* 16-bit unsigned */
typedef unsigned long           DWORD;                          /* 32-bit unsigned */
/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
#if !defined(__18CXX)
__EXTENSION
typedef unsigned long long      QWORD;                          /* 64-bit unsigned */
#endif /* __18CXX */
typedef signed char             CHAR;                           /* 8-bit signed    */
typedef signed short int        SHORT;                          /* 16-bit signed   */
typedef signed long             LONG;                           /* 32-bit signed   */
/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
#if !defined(__18CXX)
__EXTENSION
typedef signed long long        LONGLONG;                       /* 64-bit signed   */
#endif /* __18CXX */
typedef union
{
    uint8_t Val;
    struct
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;

typedef union
{
    uint16_t Val;
    uint8_t v[2];
    struct
    {
        uint8_t LB;
        uint8_t HB;
    } byte;
    struct
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
        __EXTENSION uint8_t b8:1;
        __EXTENSION uint8_t b9:1;
        __EXTENSION uint8_t b10:1;
        __EXTENSION uint8_t b11:1;
        __EXTENSION uint8_t b12:1;
        __EXTENSION uint8_t b13:1;
        __EXTENSION uint8_t b14:1;
        __EXTENSION uint8_t b15:1;
    } bits;
} WORD_VAL, WORD_BITS;

typedef union
{
    uint32_t Val;
    uint16_t w[2];
    uint8_t v[4];
    struct
    {
        uint16_t LW;
        uint16_t HW;
    } word;
    struct
    {
        uint8_t LB;
        uint8_t HB;
        uint8_t UB;
        uint8_t MB;
    } byte;
    struct
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
        __EXTENSION uint8_t b8:1;
        __EXTENSION uint8_t b9:1;
        __EXTENSION uint8_t b10:1;
        __EXTENSION uint8_t b11:1;
        __EXTENSION uint8_t b12:1;
        __EXTENSION uint8_t b13:1;
        __EXTENSION uint8_t b14:1;
        __EXTENSION uint8_t b15:1;
        __EXTENSION uint8_t b16:1;
        __EXTENSION uint8_t b17:1;
        __EXTENSION uint8_t b18:1;
        __EXTENSION uint8_t b19:1;
        __EXTENSION uint8_t b20:1;
        __EXTENSION uint8_t b21:1;
        __EXTENSION uint8_t b22:1;
        __EXTENSION uint8_t b23:1;
        __EXTENSION uint8_t b24:1;
        __EXTENSION uint8_t b25:1;
        __EXTENSION uint8_t b26:1;
        __EXTENSION uint8_t b27:1;
        __EXTENSION uint8_t b28:1;
        __EXTENSION uint8_t b29:1;
        __EXTENSION uint8_t b30:1;
        __EXTENSION uint8_t b31:1;
    } bits;
} DWORD_VAL;

/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
#if !defined(__18CXX)
typedef union
{
    uint64_t Val;
    uint32_t d[2];
    uint16_t w[4];
    uint8_t v[8];
    struct
    {
        uint32_t LD;
        uint32_t HD;
    } dword;
    struct
    {
        uint16_t LW;
        uint16_t HW;
        uint16_t UW;
        uint16_t MW;
    } word;
    struct
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
        __EXTENSION uint8_t b8:1;
        __EXTENSION uint8_t b9:1;
        __EXTENSION uint8_t b10:1;
        __EXTENSION uint8_t b11:1;
        __EXTENSION uint8_t b12:1;
        __EXTENSION uint8_t b13:1;
        __EXTENSION uint8_t b14:1;
        __EXTENSION uint8_t b15:1;
        __EXTENSION uint8_t b16:1;
        __EXTENSION uint8_t b17:1;
        __EXTENSION uint8_t b18:1;
        __EXTENSION uint8_t b19:1;
        __EXTENSION uint8_t b20:1;
        __EXTENSION uint8_t b21:1;
        __EXTENSION uint8_t b22:1;
        __EXTENSION uint8_t b23:1;
        __EXTENSION uint8_t b24:1;
        __EXTENSION uint8_t b25:1;
        __EXTENSION uint8_t b26:1;
        __EXTENSION uint8_t b27:1;
        __EXTENSION uint8_t b28:1;
        __EXTENSION uint8_t b29:1;
        __EXTENSION uint8_t b30:1;
        __EXTENSION uint8_t b31:1;
        __EXTENSION uint8_t b32:1;
        __EXTENSION uint8_t b33:1;
        __EXTENSION uint8_t b34:1;
        __EXTENSION uint8_t b35:1;
        __EXTENSION uint8_t b36:1;
        __EXTENSION uint8_t b37:1;
        __EXTENSION uint8_t b38:1;
        __EXTENSION uint8_t b39:1;
        __EXTENSION uint8_t b40:1;
        __EXTENSION uint8_t b41:1;
        __EXTENSION uint8_t b42:1;
        __EXTENSION uint8_t b43:1;
        __EXTENSION uint8_t b44:1;
        __EXTENSION uint8_t b45:1;
        __EXTENSION uint8_t b46:1;
        __EXTENSION uint8_t b47:1;
        __EXTENSION uint8_t b48:1;
        __EXTENSION uint8_t b49:1;
        __EXTENSION uint8_t b50:1;
        __EXTENSION uint8_t b51:1;
        __EXTENSION uint8_t b52:1;
        __EXTENSION uint8_t b53:1;
        __EXTENSION uint8_t b54:1;
        __EXTENSION uint8_t b55:1;
        __EXTENSION uint8_t b56:1;
        __EXTENSION uint8_t b57:1;
        __EXTENSION uint8_t b58:1;
        __EXTENSION uint8_t b59:1;
        __EXTENSION uint8_t b60:1;
        __EXTENSION uint8_t b61:1;
        __EXTENSION uint8_t b62:1;
        __EXTENSION uint8_t b63:1;
    } bits;
} QWORD_VAL;
#endif /* __18CXX */

#undef __EXTENSION

#ifdef __cplusplus
  }
#endif
#endif /* __GENERIC_TYPE_DEFS_H_ */
