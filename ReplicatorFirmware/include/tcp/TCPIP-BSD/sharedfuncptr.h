/********************************************************************
 * FileName:		SharedFuncPtr.h
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

// This is the enumeration for the shared function pointer table
// it is important to note that the enumerations MUST match the 
// SharedFunctionTbl

enum
{
    SHARED_FUNC_FAT16_INIT = 0,
    SHARED_FUNC_FOPEN,
    SHARED_FUNC_FCLOSE,
    SHARED_FUNC_REMOVE,
    SHARED_FUNC_FREAD,
    SHARED_FUNC_FWRITE,
    SHARED_FUNC_FSEEK,
    SHARED_FUNC_FTELL,
    SHARED_FUNC_REWIND,
    SHARED_FUNC_CREATE_DIR,
    SHARED_FUNC_CHANGE_DIR,
    SHARED_FUNC_GET_DIR_NAME,
    SHARED_FUNC_ERASE_DIR,
    SHARED_FUNC_FEOF,
    SHARED_FUNC_SOCKET,
    SHARED_FUNC_BIND,
    SHARED_FUNC_LISTEN,
    SHARED_FUNC_ACCEPT,
    SHARED_FUNC_CONNECT,
    SHARED_FUNC_SEND_TO,
    SHARED_FUNC_SEND,
    SHARED_FUNC_RECV_FROM,
    SHARED_FUNC_RECV,
    SHARED_FUNC_SET_SOCK_OPT,
    SHARED_FUNC_CLOSE_SOCKET,
    SHARED_FUNC_INIT_STACK_MGR,
    SHARED_FUNC_STACK_MGR_PROCESS,
    SHARED_FUNC_FTP_INIT,
    SHARED_FUNC_FTP_SERVER,
    SHARED_FUNC_FTP_GET_USER,
    SHARED_FUNC_FTP_GET_STAGE,
    SHARED_FUNC_TICK_INIT,
    SHARED_FUNC_TICK_GET,
    SHARED_FUNC_EX16_LCD_INIT,
    SHARED_FUNC_EX16_LCD_LINE
};
