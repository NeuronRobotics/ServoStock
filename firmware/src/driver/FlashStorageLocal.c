#include "main.h"

void writeFlashLocal();

typedef struct _Slic3rData {
    float nozzle_diameter;
    float printCenter [2];
    float filimentDiameter;
    float extrusionMultiplier;
    int tempreture;
    int bedTempreture;
    float layerHeight;
    int wallThickness;
    boolean useSupportMaterial;
    float retractLength;
    int travilSpeed;
    int perimeterSpeed;
    int bridgeSpeed;
    int gapFillSpeed;
    int infillSpeed;
    int supportMaterialSpeed;

    int smallPerimeterSpeedPercent;
    int externalPerimeterSpeedPercent;
    int solidInfillSpeedPercent;
    int topSolidInfillSpeedPercent;
    int supportMaterialInterfaceSpeedPercent;
    int firstLayerSpeedPercent;
} Slic3rData;

typedef struct _flashStorageData {
    AbsPID_Config localPid[numPidTotal];
    float mmPositionResolution;
    float KP;
    float KI;
    float KD;

    float VKP;
    float VKD;
    float maximumMMperSec;
    Slic3rData slic3r;
    HardwareMap hwMap;
    unsigned char buffer[1];
} flashStorageData;



flashStorageData localData;

//Default values for ServoStock
HardwareMap hwMap = {
    {0, -1.0 * mmPerTick, "Alpha"}, //axis 0
    {2, -1.0 * mmPerTick, "Beta"}, //axis 1
    {4, -1.0 * mmPerTick, "Gama"}, //axis 2
    {
        {1, 1.0, "Extruder"}, // Motor
        {11, 1.0, "Heater"}// Heater
    }, //Extruder 0
    {
        {AXIS_UNUSED, 1.0, ""},
        {AXIS_UNUSED, 1.0, ""}
    }, //Extruder 1
    {
        {AXIS_UNUSED, 1.0, ""},
        {AXIS_UNUSED, 1.0, ""}
    }, //Extruder 2
    (forwardKinematics *)& servostock_calcForward,
    (inverseKinematics *) & servostock_calcInverse,
    (velInverse *) & servostock_velInverse,
    (velForward *) & servostock_velForward,
    true
};


int linkToHWIndex(int index) {
    int localIndex = 0;
    switch (index) {
        case 0:
            localIndex = hwMap.Alpha.index;
            break;
        case 1:
            localIndex = hwMap.Beta.index;
            break;
        case 2:
            localIndex = hwMap.Gama.index;
            break;
        case 3:
            localIndex = hwMap.Extruder0.index;
            break;
        case 4:
            localIndex = hwMap.Heater0.index;
            break;
    }
    return localIndex;
}

float getLinkScale(int index) {
    switch (index) {
        case 0:
            return hwMap.Alpha.scale;
        case 1:
            return hwMap.Beta.scale;
        case 2:
            return hwMap.Gama.scale;
        case 3:
            return hwMap.Extruder0.scale;
        case 4:
            return hwMap.Heater0.scale;
    }
    return 0.0;
}

char * getName(int index) {
    switch (index) {
        case 0:
            return hwMap.Alpha.name;
        case 1:
            return hwMap.Beta.name;
        case 2:
            return hwMap.Gama.name;
        case 3:
            return hwMap.Extruder0.name;
        case 4:
            return hwMap.Heater0.name;
    }
    return NULL;
}

HardwareMap * getHardwareMap(){
    return &hwMap;
}

#define bytesOfRaw (sizeof(localData))
float getmmaximumMMperSec() {
    return localData.maximumMMperSec;
}

float getmmPositionResolution() {
    return localData.mmPositionResolution;
}

float getKP() {
    return localData.KP;
}

float getKI() {
    return localData.KI;
}

float getKD() {
    return localData.KD;
}

float getVKP() {
    return localData.VKP;
}

float getVKD() {
    return localData.VKD;
}


void setmmPositionResolution(float value) {
     localData.mmPositionResolution=value;
}

void setKP(float value) {
     localData.KP=value;
}

void setKI(float value) {
     localData.KI=value;
}

void setKD(float value) {
     localData.KD=value;
}

void setVKP(float value) {
     localData.VKP=value;
}

void setVKD(float value) {
     localData.VKD=value;
}


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

    boolean rawFlashDetect = false;

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
            rawFlashDetect = true;
        }
    }


    if (rawFlashDetect) {
        println_W("Writing default values");
        for (i = 0; i < numPidTotal; i++) {

            println_E("Detected raw flash, setting defaults : ");
            p_int_E(i);
            printPIDvals(i);
            getPidGroupDataTable(i)->config.Enabled = false;
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
            getPidGroupDataTable(i)->config.tipsScale = 1;
            printPIDvals(i);
        }
        localData.KP = .85;
        localData.KI=0;
        localData.KD=0;
        localData.VKP=1;
        localData.VKD=0;
        localData.mmPositionResolution=1;
        localData.maximumMMperSec=30;
    } else {
        println_W("Flash image ok");
        //        for (i = 0; i < numPidTotal; i++) {
        //            printPIDvals(i);
        //        }
    }
    if (rawFlashDetect)
        writeFlashLocal();

    return rawFlashDetect == false;
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
