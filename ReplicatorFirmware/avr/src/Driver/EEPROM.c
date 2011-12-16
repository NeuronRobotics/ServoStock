/*
 * EEPROM.c
 *
 *  Created on: Feb 17, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

extern MAC_ADDR MyMAC;

BYTE eeReadByte(UINT16 addr);
void eeWriteByte(UINT16 addr,BYTE val);

#define MACKEY 42
#define LOCKKEY 37
#define KEYADDR 0
#define MACSTART 	(KEYADDR+1)
#define MODESTART 	(MACSTART+6)
#define VALUESTART 	(MODESTART+24)
#define UARTBAUD 	(VALUESTART+24)
#define DATASTART 	(UARTBAUD+4)


void EEInitMAC(void){
	BYTE i;
	BYTE key=0;
	key=eeReadByte(KEYADDR);
	if ( (key == LOCKKEY) ){
		for (i=0;i<6;i++){
			MyMAC.v[i]=eeReadByte(i+MACSTART);
		}
	}
}

BOOL ProvisionMAC(BYTE * m){
	BYTE i;
	BYTE key=0;
	key=eeReadByte(KEYADDR);
	if (key==LOCKKEY){
		return FALSE;
	}else{
		for (i=0;i<6;i++){
			MyMAC.v[i]=m[i];
			eeWriteByte(i+MACSTART,MyMAC.v[i]);
		}
		eeWriteByte(KEYADDR,LOCKKEY);
		return TRUE;
	}
}

void EEWriteMode(BYTE pin,BYTE mode){
	if (EEReadMode(pin) != mode){
		eeWriteByte((UINT16)(MODESTART+pin),mode);
	}
}

BYTE EEReadMode(BYTE pin){
	return eeReadByte((UINT16)(MODESTART+pin));
}


void EEWriteValue(UINT16 pin,BYTE value){
	if (value == 255)
		value = 254;
	eeWriteByte((UINT16)(VALUESTART+pin),value);
}

BYTE EEReadValue(UINT16 pin){
	BYTE val = eeReadByte((UINT16)(VALUESTART+pin));
	if (val == 255)
		EEWriteValue(pin,128);
	return eeReadByte((UINT16)(VALUESTART+pin));
}

UINT32 EEReadBaud(void){
	UINT32_UNION v;
	v.byte.FB= eeReadByte((UARTBAUD+0));
	v.byte.TB= eeReadByte((UARTBAUD+1));
	v.byte.SB= eeReadByte((UARTBAUD+2));
	v.byte.LB= eeReadByte((UARTBAUD+3));
	return v.Val;
}

void EEWriteBaud(UINT32 val){
	UINT32_UNION v;
	v.Val = val;
	eeWriteByte((UARTBAUD+0),v.byte.FB);
	eeWriteByte((UARTBAUD+1),v.byte.TB);
	eeWriteByte((UARTBAUD+2),v.byte.SB);
	eeWriteByte((UARTBAUD+3),v.byte.LB);
}

BYTE EEReadData(UINT16 addr){
	if((addr+DATASTART)>=1024){
		return 0;
	}
	return eeReadByte((DATASTART+addr));
}
void EEWriteData(UINT16 addr,BYTE data){
	if((addr+DATASTART)>=1024){
		return;
	}
	eeWriteByte((DATASTART+addr),data);

}


BYTE eeReadByte(UINT16 addr){
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	EECR=0;
	/* Set up address register */
	EEAR = addr;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;

}

void eeWriteByte(UINT16 addr,BYTE val){
	if (eeReadByte(addr)==val)
		return;
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	EECR=0;
	/* Set up address and Data Registers */
	EEAR = addr;
	EEDR = val;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);

}


