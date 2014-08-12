#include "main.h"




void writeFlashLocal();

#define bytesOfRaw (numPidTotal*sizeof(AbsPID_Config))


static AbsPID 			pidGroupsLocal[numPidTotal];

AbsPID * getFlashPidGroupDataTable(){
	if(pidGroupsLocal == NULL){
		println_E("PID data table is null");
		return NULL;
	}

	return pidGroupsLocal;
}
union LocalFlashData{
    unsigned long int data[bytesOfRaw/4];
    AbsPID_Config pid[numPidTotal];

};

AbsPID_Config localPid[numPidTotal];
//union LocalFlashData localData;

void checkDataTable(){
    Nop();
}

BOOL initFlashLocal(){

    if(bytesOfRaw > 0x1000-FLASHSTORE){
        println_E("Too much data to store");
        SoftReset();
    }
    
    println_W("Size of Flash data = ");p_int_W(bytesOfRaw);

    SetFlashData( (UINT32 *)localPid ,bytesOfRaw/4);
    FlashLoad();

    int i=0,j=0;// index;

    BOOL rawFlashDetect=FALSE;

    for(i=0;i<numPidTotal;i++){
        //index = i*sizeof(AbsPID_Config)/4;
        unsigned int * raw = (  unsigned int *)&pidGroupsLocal[i].config;
        unsigned int * data = (  unsigned int *) &localPid[i];
        for(j=0;j<sizeof(AbsPID_Config)/4;j++){
            raw[j]=data[j];
        }
        if( ((pidGroupsLocal[i].config.Enabled != 1 &&
              pidGroupsLocal[i].config.Enabled != 0))||
              pidGroupsLocal[i].config.offset != getPidGroupDataTable(i)->config.offset
                ){
            rawFlashDetect = TRUE;
        }
    }

    if( rawFlashDetect ){
        for(i=0;i<numPidTotal;i++){
            if(i==1){
                Nop();
            }
            println_E("Detected raw flash, setting defaults : ");p_int_E(i);
            printPIDvals(i);
            pidGroupsLocal[i].config.Enabled = FALSE;
            pidGroupsLocal[i].config.Async=0;
            pidGroupsLocal[i].config.IndexLatchValue=0;
            pidGroupsLocal[i].config.stopOnIndex=0;
            pidGroupsLocal[i].config.useIndexLatch=0;
            pidGroupsLocal[i].config.K.P=.1;
            pidGroupsLocal[i].config.K.I=0;
            pidGroupsLocal[i].config.K.D=0;
            pidGroupsLocal[i].config.V.P=.1;
            pidGroupsLocal[i].config.V.D=0;
            pidGroupsLocal[i].config.Polarity=1;
            pidGroupsLocal[i].config.stop=0;
            pidGroupsLocal[i].config.upperHistoresis=0;
            pidGroupsLocal[i].config.lowerHistoresis=0;
            pidGroupsLocal[i].config.offset=0.0;
            pidGroupsLocal[i].config.calibrationState=CALIBRARTION_Uncalibrated;
            printPIDvals(i);
        }
    }
    if(rawFlashDetect )
        writeFlashLocal();

    return !rawFlashDetect;
}

void writeFlashLocal(){

    if(bytesOfRaw > 0x1000-FLASHSTORE){
        println_E("Too much data to store");
        SoftReset();
    }
    println_W("Writing values to Flash");
    int i=0,j=0;//, index;
    for(i=0;i<numPidTotal;i++){
        //printPIDvals(i);
        //index = i*sizeof(AbsPID_Config)/4;
        unsigned int * raw = (  unsigned int *)&pidGroupsLocal[i].config;
        unsigned int * data =(  unsigned int *) &localPid[i];
        for(j=0;j<sizeof(AbsPID_Config)/4;j++){
            data[j]=raw[j];
        }
    }
    FlashSync();
    FlashLoad();
    for(i=0;i<numPidTotal;i++){
        //printPIDvals(i);
    }

}
