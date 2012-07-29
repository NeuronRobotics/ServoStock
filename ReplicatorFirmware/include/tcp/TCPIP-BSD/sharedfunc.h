/********************************************************************
 *      Shared Functions header file
********************************************************************
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
#ifndef _SHARED_FUNC_INLINE
#define _SHARED_FUNC_INLINE

/*
#include "generic.h"
#include "bsd_ftp_server\ftp.h"
#include "ex16lcd.h"
#include "bsd_bootloader_over_ip\sharedfuncptr.h"
#include "bsd_bootloader_over_ip\bloip.h"
*/


inline BOOL FSInit(void)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    BOOL (*fp)(void) = (BOOL (*)(void))(tblptr[SHARED_FUNC_FAT16_INIT]);

    return fp();
}

inline FSFILE *FSfopen( const char *fileName, const char *mode )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    FSFILE *(*fp_fopen)(const char *, const char *) = (FSFILE *(*)(const char *, const char *))(tblptr[SHARED_FUNC_FOPEN]);

    return fp_fopen(fileName, mode);

}

inline int FSfclose( FSFILE *stream )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(FSFILE *) = (int (*)(FSFILE *))(tblptr[SHARED_FUNC_FCLOSE]);

    return fp(stream);
}

inline int FSremove( const char *fileName )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(const char *) = (int (*)(const char *))(tblptr[SHARED_FUNC_REMOVE]);

    return fp(fileName);
}

inline size_t FSfread( void *ptr, size_t size, size_t n, FSFILE *stream )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    size_t (*fp)(void *, size_t, size_t, FSFILE *) = (size_t (*)(void *, size_t, size_t, FSFILE *))(tblptr[SHARED_FUNC_FREAD]);

    return fp(ptr, size, n, stream);
}

inline size_t FSfwrite( const void *ptr, size_t size, size_t n, FSFILE *stream )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    size_t (*fp)(const void *, size_t, size_t, FSFILE *) = (size_t (*)(const void *, size_t, size_t, FSFILE *))(tblptr[SHARED_FUNC_FWRITE]);

    return fp(ptr, size, n, stream);
}

inline int FSfseek( FSFILE *stream, long offset, int origin )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(FSFILE *, long, int) = (int (*)(FSFILE *, long, int))(tblptr[SHARED_FUNC_FSEEK]);

    return fp(stream, offset, origin);

}

inline long FSftell( FSFILE *stream  )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    long (*fp)(FSFILE *) = (long (*)(FSFILE *))(tblptr[SHARED_FUNC_FTELL]);

    return fp(stream);

}

inline void FSrewind( FSFILE *stream )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    void (*fp)(FSFILE *) = (void (*)(FSFILE *))(tblptr[SHARED_FUNC_REWIND]);

    fp(stream);
}

inline FSFILE *CreateDirectory( const char *dirName )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    FSFILE *(*fp)(const char *) = (FSFILE *(*)(const char *))(tblptr[SHARED_FUNC_CREATE_DIR]);

    return fp(dirName);
}

inline BOOL ChangeDirectory( FSFILE *stream, const char *dirName )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    BOOL (*fp)(FSFILE *, const char *) = (BOOL (*)(FSFILE *, const char *))(tblptr[SHARED_FUNC_CHANGE_DIR]);

    return fp(stream, dirName);

}

inline BOOL GetDirectoryName(  FSFILE *stream, char *dirName )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    BOOL (*fp)(FSFILE *, char *) = (BOOL (*)(FSFILE *, char *))(tblptr[SHARED_FUNC_GET_DIR_NAME]);

    return fp(stream, dirName);
}

inline BOOL EraseDirectory( FSFILE *stream, const char *dirName )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    BOOL (*fp)(FSFILE *, const char *) = (BOOL (*)(FSFILE *, const char *))(tblptr[SHARED_FUNC_ERASE_DIR]);

    return fp(stream, dirName);

}

inline int FSfeof( FSFILE *stream )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(FSFILE *) = (int (*)(FSFILE *))(tblptr[SHARED_FUNC_FEOF]);

    return fp(stream);
}

inline SOCKET socket( int af, int type, int protocol )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    SOCKET (*fp)(int, int, int) = (SOCKET (*)(int, int, int))(tblptr[SHARED_FUNC_SOCKET]);

    return fp(af, type, protocol);
}

inline int bind( SOCKET s, const struct sockaddr * name, int namelen )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(SOCKET, const struct sockaddr *, int) = (int (*)(SOCKET, const struct sockaddr *, int))(tblptr[SHARED_FUNC_BIND]);

    return fp(s, name, namelen);
}

inline int listen( SOCKET s, int backlog )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(SOCKET, int) = (int (*)(SOCKET, int))(tblptr[SHARED_FUNC_LISTEN]);

    return fp(s, backlog);
}

inline SOCKET accept( SOCKET s, struct sockaddr * addr, int * addrlen )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    SOCKET (*fp)(SOCKET, struct sockaddr *, int *) = (SOCKET (*)(SOCKET, struct sockaddr *, int *))(tblptr[SHARED_FUNC_ACCEPT]);

    return fp(s, addr, addrlen);
}

inline int connect( SOCKET s, struct sockaddr * name, int namelen )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(SOCKET, struct sockaddr *, int) = (int (*)(SOCKET, struct sockaddr *, int))(tblptr[SHARED_FUNC_CONNECT]);

    return fp(s, name, namelen);
}

inline int sendto( SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(SOCKET, const char *, int, int, const struct sockaddr *, int) = 
        (int (*)(SOCKET, const char *, int, int, const struct sockaddr *, int))(tblptr[SHARED_FUNC_SEND_TO]);

    return fp(s, buf, len, flags, to, tolen);
}

inline int send( SOCKET s, const char* buf, int len, int flags )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(SOCKET, const char *, int, int) = (int (*)(SOCKET, const char *, int, int))(tblptr[SHARED_FUNC_SEND]);

    return fp(s, buf, len, flags);
}

inline int recvfrom( SOCKET s, char * buf, int len, int flags, struct sockaddr * from, int * fromlen )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(SOCKET, char *, int, int, struct sockaddr *, int *) = 
        (int (*)(SOCKET, char *, int, int, struct sockaddr *, int *))(tblptr[SHARED_FUNC_RECV_FROM]);

    return fp(s, buf, len, flags, from, fromlen);
}

inline int recv( SOCKET s, char * buf, int len, int flags )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(SOCKET, char *, int, int) = (int (*)(SOCKET, char *, int, int))(tblptr[SHARED_FUNC_RECV]);

    return fp(s, buf, len, flags);
}

inline int setsockopt( SOCKET s, int level, int optname,char * optval, int optlen )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(SOCKET, int, int, char *, int) = (int (*)(SOCKET, int, int, char *, int))(tblptr[SHARED_FUNC_SET_SOCK_OPT]);

    return fp(s, level, optname, optval, optlen);
}

inline int closesocket( SOCKET s )
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    int (*fp)(SOCKET) = (int (*)(SOCKET))(tblptr[SHARED_FUNC_CLOSE_SOCKET]);

    return fp(s);
}

inline void TCPIPInit(void)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    void (*fp)(void) = (void (*)(void))(tblptr[SHARED_FUNC_INIT_STACK_MGR]);

    fp();
}

inline void TCPIPProcess(void)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    void (*fp)(void) = (void (*)(void))(tblptr[SHARED_FUNC_STACK_MGR_PROCESS]);

    fp();
}

inline BOOL FTPInit(void)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    BOOL (*fp)(void) = (BOOL (*)(void))(tblptr[SHARED_FUNC_FTP_INIT]);

    return fp();
}

inline BOOL FTPServer(void)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    BOOL (*fp)(void) = (BOOL (*)(void))(tblptr[SHARED_FUNC_FTP_SERVER]);

    return fp();
}

inline BOOL FTPGetUser(BYTE *user)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    BOOL (*fp)(BYTE *) = (BOOL (*)(BYTE *))(tblptr[SHARED_FUNC_FTP_GET_USER]);

    return fp(user);
}

inline SM_FTP FTPGetStage(void)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    SM_FTP (*fp)(void) = (SM_FTP (*)(void))(tblptr[SHARED_FUNC_FTP_GET_STAGE]);

    return fp();

}

inline void SystemTickInit(void)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    void (*fp)(void) = (void (*)(void))(tblptr[SHARED_FUNC_TICK_INIT]);

    fp();
}

inline TICK SystemTickGet(void)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    TICK (*fp)(void) = (TICK (*)(void))(tblptr[SHARED_FUNC_TICK_GET]);

    return fp();
}

inline void Ex16LCDInit(UINT pb_clk)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    void (*fp)(UINT) = (void (*)(UINT))(tblptr[SHARED_FUNC_EX16_LCD_INIT]);

    fp(pb_clk);
}

inline void Ex16LCDWriteLine(UINT number, const BYTE *line)
{
    void **tblptr;

    tblptr = (void **)BLOIP_SHARED_FUNC;

    void (*fp)(UINT, const BYTE *) = (void (*)(UINT, const BYTE *))(tblptr[SHARED_FUNC_EX16_LCD_LINE]);

    fp(number, line);

}
#endif
