/*********************************************************************
 *
 *                  Helper Function Defs for TCP/IP Stack
 *
 *********************************************************************
 * FileName:        gpFunc.h
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
 *
 ********************************************************************/

#ifndef _GP_FUNC_H_
#define _GP_FUNC_H_


WORD swaps(WORD v);
void swapl(DWORD dw, DWORD*pd);
DWORD swaplEx(DWORD dw);

void MAC_StrToBin( const char* szMAC, BYTE* pMAC );
void itoaETH(unsigned int dat, char* str);

WORD fold_checksum( DWORD csum );
void checksum16_partial( BYTE* pkt, int len, DWORD* sum );
WORD checksum16( BYTE* pkt, int len );
char *strupr(char*);

#define LOWORD(a) ((WORD)a)
#define HIWORD(a) ((WORD)(a >> 16))

extern inline DWORD __attribute__ ((always_inline)) _arrayToDword(BYTE *array)
{
DWORD_VAL   data;

	data.v[0] = array[0];
	data.v[1] = array[1];
	data.v[2] = array[2];
	data.v[3] = array[3];
	
	return data.Val;
}

extern inline void __attribute__ ((always_inline)) _dwordToArray(DWORD data, BYTE *array)
{
DWORD_VAL   temp;
	
	temp.Val    = data;
	array[0]   = temp.v[0];
	array[1]   = temp.v[1];
	array[2]   = temp.v[2];
	array[3]   = temp.v[3];	
}



extern inline WORD __attribute__ ((always_inline))  swaps(WORD v)
{
	WORD_VAL w1,w2;
	
	w1.Val = v;

	w2.v[0] = w1.v[1];
	w2.v[1] = w1.v[0];

	return w2.Val;
}

////////////////////////////////////////////////
////////////////////////////////////////////////
extern inline DWORD __attribute__ ((always_inline)) swaplEx(DWORD dw)
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
extern inline void __attribute__ ((always_inline)) swapl(DWORD dw, DWORD*pd)
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





#endif  // _GP_FUNC_H_

