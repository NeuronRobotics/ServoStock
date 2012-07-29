/********************************************************************
 *  Boot loader over IP interface file
********************************************************************
 * FileName:		BLOIP.c
 * Dependencies:
 * Company:		Microchip Technology, Inc.
 *
 * Software License Agreement:
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
 ********************************************************************/

#ifndef _BOOTLOADER_OVER_IP_HEADER_FILE
#define _BOOTLOADER_OVER_IP_HEADER_FILE

typedef struct
{
    DWORD   addr;
    BYTE    data[512];
    WORD    chksum;
}BIN_FILE_REC;

typedef struct
{
    BYTE    micro_name[16];
    WORD    micro_type;
    DWORD   size;
    DWORD   file_chksum;
}BIN_FILE_HDR;

#define BLOIP_APP_FILENAME              "main.app"
#define BLOIP_APP_START                 0xBD030200
#define BLOIP_APP_ROM_DATA				0xBD030000
#define BLOIP_APP_END					0xBD080000
#define BLOIP_SHARED_FUNC               0xBD002000
#endif
