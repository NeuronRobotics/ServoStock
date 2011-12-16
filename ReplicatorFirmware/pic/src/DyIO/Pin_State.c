/*
 * Pin_State.c
 *
 *  Created on: Nov 23, 2009
 *      Author: hephaestus
 */
#include "UserApp.h"

STORAGE self;
extern DATA_STRUCT DATA __attribute__ ((section (".scs_global_var")));
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));
void InitPins(void){
	InitPinFunction();
	int i;
	printfDEBUG("Pin Functions");
	InitPinFunction();
	printfDEBUG("Pin States");
	InitPinStates();
	printfDEBUG("Done with Pin States");

	FlashGetMac(MyMAC.v);
	FlashGetName(self.Name);
	for(i=0;i<17;i++){
		if((unsigned char)self.Name[i]==0xff){
			strcpy(self.Name,"DyIO Module     ");
			FlashSetName(self.Name);
		}
		FlashGetName(self.Name);
	}

	if (!GetLockCode(self.LockCode)){
		strcpy(self.LockCode,"0000");
		SetLockCode(self.LockCode);
	}

}
