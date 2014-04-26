#include "main.h"


void writeFlashLocal();

#define bytesOfRaw (numPidTotal*sizeof(AbsPID_Config))

union LocalFlashData{
    unsigned long int data[bytesOfRaw/4];
    AbsPID_Config pid[numPidTotal];
};


union LocalFlashData localData;

BOOL initFlashLocal(){

    if(bytesOfRaw > 0x1000-FLASHSTORE){
        println_E("Too much data to store");
        SoftReset();
    }
    
    println_W("Size of Flash data = ");p_int_W(bytesOfRaw);

    SetFlashData( localData.data ,bytesOfRaw/4);
    FlashLoad();

    int i=0,j=0, index;

    BOOL rawFlashDetect=FALSE;

    for(i=0;i<numPidTotal;i++){
        index = i*sizeof(AbsPID_Config)/4;
        for(j=0;j<sizeof(AbsPID_Config)/4;j++){
            getPidGroupDataTable()[i].raw[j]=localData.data[index+j];
        }
        if( (getPidGroupDataTable()[i].config.Enabled != 1 &&
            getPidGroupDataTable()[i].config.Enabled != 0)  ){
            rawFlashDetect = TRUE;
            println_E("Detected raw flash, setting defaults : ");p_int_E(i);
            printPIDvals(i);
            getPidGroupDataTable()[i].config.Enabled = FALSE;
            getPidGroupDataTable()[i].config.Async=0;
            getPidGroupDataTable()[i].config.IndexLatchValue=0;
            getPidGroupDataTable()[i].config.stopOnIndex=0;
            getPidGroupDataTable()[i].config.useIndexLatch=0;
            getPidGroupDataTable()[i].config.K.P=.1;
            getPidGroupDataTable()[i].config.K.I=0;
            getPidGroupDataTable()[i].config.K.D=0;
            getPidGroupDataTable()[i].config.V.P=.1;
            getPidGroupDataTable()[i].config.V.D=0;
            getPidGroupDataTable()[i].config.Polarity=1;
            getPidGroupDataTable()[i].config.stop=0;
            getPidGroupDataTable()[i].config.upperHistoresis=0;
            getPidGroupDataTable()[i].config.lowerHistoresis=0;
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
    int i=0,j=0, index;
    for(i=0;i<numPidTotal;i++){
        printPIDvals(i);
        index = i*sizeof(AbsPID_Config)/4;
        for(j=0;j<sizeof(AbsPID_Config)/4;j++){
            localData.data[index+j]=getPidGroupDataTable()[i].raw[j];
        }
    }
    FlashSync();
    FlashLoad();
    for(i=0;i<numPidTotal;i++){
        printPIDvals(i);
    }

}