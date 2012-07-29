/*********************************************************************
 *
 *                  Helper Functions for Microchip TCP/IP Stack
 *
 *********************************************************************
 * FileName:        Helpers.C
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
 * $Id: gpFunc.c,v 1.1 2006/09/28 22:10:29 C12770 Exp $
 *
 ********************************************************************/
#include "_tcpip_common.h"

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
BYTE Hex2Dec( char c )
{
	c = toupper(c);
	if( c >= 'A' && c <= 'F' )
		return c - 'A' + 10;
	else if( c >= '0' && c <= '9' )
		return c - '0';
	else
		return 0;
}

///////////////////////////////////////////////////////////
//Converts string of hex numbers to byte array in Big Endian
void MAC_StrToBin( const char* szMAC, BYTE* pMAC )
{
	const char* szpm;
	char c;

    BYTE index = 0;
	BYTE acc = 0;
	
	szpm = szMAC;
	
	while( (c = *szpm++) ) 
	{
		if( c == ' ' )
			continue;

        if( c == '-' || c == ':' )
		{
            pMAC[index++] = acc;
            acc = 0;
        }
		else
		{	c = Hex2Dec(c);
            acc = acc*16 + c;
		}
    }

    pMAC[5] = acc;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
void itoaETH(unsigned int dat, char* str)
{
	unsigned int digit, strLen = 1;
	unsigned int divs = 10;
	
	while( dat/divs )
	{
		strLen++;
		divs *= 10;
	}
	
	divs = 1;
	do
	{
		digit = dat % 10;
		str[ strLen-divs++ ] = digit + '0';
	}
	while( (dat=dat/10) );
	str[ divs-1 ] = '\0'; //null terminate the string
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void checksum16_partial( BYTE* pkt, int len, DWORD* pSum )
{
	WORD	*wPtr;
	DWORD	dSum;
	int	left;
   
	if( (len & 1) == 0 )
	{
	    left=0;
	}
	else
	{
	    left = 1;
	}
    
	dSum=*pSum;
	len = len >> 1;

	wPtr = (WORD*)pkt;
    
	while( len-- )
	{
		dSum += *wPtr++;
	}
	
	if(left)
	{
		dSum += *(BYTE*)wPtr;
	}

	*pSum=dSum;
}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
WORD fold_checksum( DWORD sum )
{
	DWORD_VAL	dSum;

	dSum.Val=sum;

	// add carry, 1's complement
	dSum.Val = (DWORD)dSum.w[0] + (DWORD)dSum.w[1];
 
	// add carry once more, just in case there was one from prev op
	dSum.w[0] += dSum.w[1];
     	
	return dSum.w[0];
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
WORD checksum16( BYTE* pkt, int len )
{
	WORD 		*wPtr;
	DWORD_VAL	dSum;
	int		left;
   
	if( (len & 1) == 0 )
	{
		left=0;
	}
	else
	{
		left = 1;
	}
	   
        len = len >> 1;
	wPtr = (WORD*)pkt;
	dSum.Val=0;
    
	while( len-- )
	{
		dSum.Val += *wPtr++;
	}
	
	if(left)
	{
		dSum.Val += *(BYTE*)wPtr;
	}
	
	// add carry, 1's complement
	dSum.Val = (DWORD)dSum.w[0] + (DWORD)dSum.w[1];
 
	// add carry once more, just in case there was one from prev op
	dSum.w[0] += dSum.w[1];
     	
	return dSum.w[0];
}



/*
WORD swaps(WORD v)
{
	WORD_VAL w1,w2;
	
	w1.Val = v;

	w2.v[0] = w1.v[1];
	w2.v[1] = w1.v[0];

	return w2.Val;
}

////////////////////////////////////////////////
////////////////////////////////////////////////
DWORD swaplEx(DWORD dw)
{
BYTE b0;
WORD w0;
DWORD_VAL dws;

	dws.Val = dw;

	w0 = dws.w[0];
	dws.w[0] = dws.w[1];
	dws.w[1] = w0;
	
	b0 = dws.v[0];
	dws.v[0] = dws.v[1];
	dws.v[1] = b0;
	
	b0 = dws.v[2];
	dws.v[2] = dws.v[3];
	dws.v[3] = b0;

	return dws.Val;	
}


////////////////////////////////////////////////
////////////////////////////////////////////////
void   swapl(DWORD dw, DWORD*pd)
{
BYTE b0;
WORD w0;
DWORD_VAL dws;

	dws.Val = dw;

	w0 = dws.w[0];
	dws.w[0] = dws.w[1];
	dws.w[1] = w0;
	
	b0 = dws.v[0];
	dws.v[0] = dws.v[1];
	dws.v[1] = b0;
	
	b0 = dws.v[2];
	dws.v[2] = dws.v[3];
	dws.v[3] = b0;

	*pd = dws.Val;	
}
*/

////////////////////////////////////////////////
////////////////////////////////////////////////
char *strupr (char *s)
{
    char c;
    char *t;

    t = s;
    while( (c = *t) )
    {
        if ( (c >= 'a' && c <= 'z') )
            *t -= ('a' - 'A');
    t++;
    }
    return s;
}
