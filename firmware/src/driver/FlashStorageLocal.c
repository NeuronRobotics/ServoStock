#include "main.h"

void writeFlashLocal();

typedef struct _flashStorageData {
    AbsPID_Config localPid[numPidTotal];
    unsigned char buffer[1];
} flashStorageData;

flashStorageData localData;

#define bytesOfRaw (sizeof(localData))

void checkDataTable() {
    Nop();
}

boolean initFlashLocal() {

    if (bytesOfRaw > 0x1000 - FLASHSTORE) {
        println_E("Too much data to store");
        SoftReset();
    }
    if (bytesOfRaw % 4) {
        println_E("BAD FLASH size = ");
        p_int_W(bytesOfRaw % 4);
        while (1);
    }
    println_W("Size of Flash page data = ");
    p_int_W(bytesOfRaw / 4);
    print_W(" ");
    p_int_W(bytesOfRaw);

    SetFlashData((uint32_t *) & localData, bytesOfRaw / 4);
    FlashLoad();
    println_W("Flash loaded");

    int i = 0, j = 0; // index;

    boolean rawFlashDetect = FALSE;

    for (i = 0; i < numPidTotal; i++) {
        println_W("Setting PID #");
        p_int_W(i);
        unsigned char * raw = (unsigned char *) & getPidGroupDataTable(i)->config;
        unsigned char * data = (unsigned char *) & localData.localPid[i];
        for (j = 0; j<sizeof (AbsPID_Config); j++) {
            raw[j] = data[j];
        }
    }

    println_W("Checking for bare flash");
    for (i = 0; i < numPidTotal; i++) {
        if (((getPidGroupDataTable(i)->config.Enabled > 1 ||
                getPidGroupDataTable(i)->config.Enabled < 0))
                ) {
            rawFlashDetect = TRUE;
        }
    }


    if (rawFlashDetect) {
        println_W("Writing default values");
        for (i = 0; i < numPidTotal; i++) {

            println_E("Detected raw flash, setting defaults : ");
            p_int_E(i);
            printPIDvals(i);
            getPidGroupDataTable(i)->config.Enabled = FALSE;
            getPidGroupDataTable(i)->config.Async = 0;
            getPidGroupDataTable(i)->config.IndexLatchValue = 0;
            getPidGroupDataTable(i)->config.stopOnIndex = 0;
            getPidGroupDataTable(i)->config.useIndexLatch = 0;
            getPidGroupDataTable(i)->config.K.P = .1;
            getPidGroupDataTable(i)->config.K.I = 0;
            getPidGroupDataTable(i)->config.K.D = 0;
            getPidGroupDataTable(i)->config.V.P = .1;
            getPidGroupDataTable(i)->config.V.D = 0;
            getPidGroupDataTable(i)->config.Polarity = 1;
            getPidGroupDataTable(i)->config.stop = 0;
            getPidGroupDataTable(i)->config.upperHistoresis = 0;
            getPidGroupDataTable(i)->config.lowerHistoresis = 0;
            getPidGroupDataTable(i)->config.offset = 0.0;
            getPidGroupDataTable(i)->config.calibrationState = CALIBRARTION_Uncalibrated;
            printPIDvals(i);
        }
    } else {
        println_W("Flash image ok");
//        for (i = 0; i < numPidTotal; i++) {
//            printPIDvals(i);
//        }
    }
    if (rawFlashDetect)
        writeFlashLocal();

    return rawFlashDetect == FALSE;
}

void writeFlashLocal() {

    if (bytesOfRaw > 0x1000 - FLASHSTORE) {
        println_E("Too much data to store");
        SoftReset();
    }
    println_W("Writing values to Flash");
    int i = 0, j = 0; //, index;
    for (i = 0; i < numPidTotal; i++) {

        unsigned char * raw = (unsigned char *) &getPidGroupDataTable(i)->config;
        unsigned char * data = (unsigned char *) &localData.localPid[i];
        for (j = 0; j<sizeof (AbsPID_Config); j++) {
            data[j] = raw[j];
        }
    }
    FlashSync();
    FlashLoad();
    for (i = 0; i < numPidTotal; i++) {
        //printPIDvals(i);
    }

}
