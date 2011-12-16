/*
 * IO.c
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

extern DATA_STRUCT DATA;

BYTE GetDIO(BYTE PIN){
	switch (PIN){
#if !defined(WPIRBE)
	case 0:
		return PI0;
	case 1:
		return PI1;
	case 2:
		return PI2;
	case 3:
		return PI3;
#endif
	case 4:
		return PI4;
	case 5:
		return PI5;
	case 6:
		return PI6;
	case 7:
		return PI7;
	case 8:
		return PI8;
	case 9:
		return PI9;
	case 10:
		return PI10;
	case 11:
		return PI11;
	case 12:
		return PI12;
	case 13:
		return PI13;
	case 14:
		return PI14;
	case 15:
		return PI15;
	case 16:
		if (UCSR1Bbits._TXEN1 == 0)
			return PI16;
	case 17:
		if (UCSR1Bbits._TXEN1 == 0)
			return PI17;
	case 18:
		return PI18;
	case 19:
		return PI19;
	case 20:
		return PI20;
	case 21:
		return PI21;
	case 22:
		return PI22;
	case 23:
		return PI23;
	}
	return 0;
}

void SetDIO(BYTE PIN,BYTE state){
	switch (PIN){
#if !defined(WPIRBE)
	case 0:
		PO0 = state;
		return;
	case 1:
		PO1 = state;
		return;
	case 2:
		PO2 = state;
		return;
	case 3:
		PO3 = state;
		return;
#endif
	case 4:
		PO4 = state;
		return;
	case 5:
		PO5 = state;
		return;
	case 6:
		PO6 = state;
		return;
#if !defined(WPIRBE)
	case 7:
		PO7 = state;
		return;
#endif
	case 8:
		PO8 = state;
		return;
	case 9:
		PO9 = state;
		return;
	case 10:
		PO10 = state;
		return;
	case 11:
		PO11 = state;
		return;
	case 12:
		PO12 = state;
		return;
	case 13:
		PO13 = state;
		return;
	case 14:
		PO14 = state;
		return;
	case 15:
		PO15 = state;
		return;

	case 16:
		if (UCSR1Bbits._TXEN1 == 0)
			PO16 = state;
		return;
	case 17:
		if (UCSR1Bbits._TXEN1 == 0)
			PO17 = state;
		return;
	case 18:
		PO18 = state;
		return;
	case 19:
		PO19 = state;
		return;
	case 20:
		PO20 = state;
		return;
	case 21:
		PO21 = state;
		return;
	case 22:
		PO22 = state;
		return;
	case 23:
		PO23 = state;
		return;
	}
}
void SetPinTris(BYTE PIN,BYTE state){
	switch (PIN){
#if !defined(WPIRBE)
	case 0:
		DDR0 = state;
		return;
	case 1:
		DDR1 = state;
		return;
	case 2:
		DDR2 = state;
		return;
	case 3:
		DDR3 = state;
		return;
#endif
	case 4:
		DDR4 = state;
		return;
	case 5:
		DDR5 = state;
		return;
	case 6:
		DDR6 = state;
		return;
#if !defined(WPIRBE)
	case 7:
		DDR7 = state;
		return;
#endif
	case 8:
		DDR8 = state;
		return;
	case 9:
		DDR9 = state;
		return;
	case 10:
		DDR10 = state;
		return;
	case 11:
		DDR11 = state;
		return;
	case 12:
		DDR12 = state;
		return;
	case 13:
		DDR13 =state;
		return;
	case 14:
		DDR14 = state;
		return;
	case 15:
		DDR15 = state;
		return;
	case 16:
		if (UCSR1Bbits._TXEN1 == 0)
			DDR16 = state;
		return;
	case 17:
		if (UCSR1Bbits._TXEN1 == 0)
			DDR17 = state;
		return;
	case 18:
		DDR18 = state;
		return;
	case 19:
		DDR19 = state;
		return;
	case 20:
		DDR20 = state;
		return;
	case 21:
		DDR21 = state;
		return;
	case 22:
		DDR22 = state;
		return;
	case 23:
		DDR23 = state;
		return;
	}
}

