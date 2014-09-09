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
    DeltaConfig defaultConfig;
    int32_t kinematicsIndex;
    // this should be changed to garuntee that the struct is exactly a multiple of 4 bytes
    unsigned char buffer[1];
} flashStorageData;



flashStorageData localData;
#define bytesOfRaw (sizeof(localData))

//Default values for ServoStock
HardwareMap hwMap = {
    {0, -1.0 * mmPerTick, "Alpha"}, //axis 0
    {2, -1.0 * mmPerTick, "Beta"}, //axis 1
    {4, -1.0 * mmPerTick, "Gama"}, //axis 2
    {
        {1, 1.0, "Extruder"}, // Motor
        {10, 1.0, "Heater"}// Heater
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

void setKinematicsMath(){
    switch(localData.kinematicsIndex){
        case 0:
            localData.hwMap.fK_callback = (forwardKinematics *)& servostock_calcForward;
            localData.hwMap.iK_callback=(inverseKinematics *) & servostock_calcInverse;
            localData.hwMap.iVel_callback = (velInverse *) & servostock_velInverse;
            localData.hwMap.fVel_callback = (velForward *) & servostock_velForward;
            localData.hwMap.useStateBasedVelocity=true;
            break;
        case 1:
            localData.hwMap.fK_callback = (forwardKinematics *)& box_calcForward;
            localData.hwMap.iK_callback=(inverseKinematics *) & box_calcInverse;
            localData.hwMap.useStateBasedVelocity=false;
            break;
        case 2:
            localData.hwMap.fK_callback = (forwardKinematics *)& frog_calcForward;
            localData.hwMap.iK_callback=(inverseKinematics *) & frog_calcInverse;
            localData.hwMap.useStateBasedVelocity=false;
            break;
    }
}

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

HardwareMap * getHardwareMap() {
    return &hwMap;
}

boolean onControllerConfigurationGet(BowlerPacket *Packet) {

    set32bit(Packet, localData.KP * 1000.0, 0); //KP
    set32bit(Packet, localData.KI * 1000.0, 4); //KI
    set32bit(Packet, localData.KD * 1000.0, 8); //KD
    set32bit(Packet, localData.VKP * 1000.0, 12); //VKP
    set32bit(Packet, localData.VKD * 1000.0, 16); //VKD
    set32bit(Packet, localData.mmPositionResolution * 1000.0, 20); //mmPositionResolution
    set32bit(Packet, localData.maximumMMperSec * 1000.0, 24); // maximumMMperSec

    set32bit(Packet, localData.defaultConfig.BaseRadius * 1000.0, 28); //
    set32bit(Packet, localData.defaultConfig.EndEffectorRadius * 1000.0, 32); //

    set32bit(Packet, localData.defaultConfig.MaxZ * 1000.0, 36); //

    set32bit(Packet, localData.defaultConfig.MinZ * 1000.0, 40); //
    set32bit(Packet, localData.defaultConfig.RodLength * 1000.0, 44); //

}

boolean onControllerConfigurationSet(BowlerPacket *Packet) {
    localData.KP = get32bit(Packet, 0) / 1000.0;
    localData.KI = get32bit(Packet, 4) / 1000.0;
    localData.KD = get32bit(Packet, 8) / 1000.0;
    localData.VKP = get32bit(Packet, 12) / 1000.0;
    localData.VKD = get32bit(Packet, 16) / 1000.0;
    localData.mmPositionResolution = get32bit(Packet, 20) / 1000.0;
    localData.maximumMMperSec = get32bit(Packet, 24) / 1000.0;

    localData.defaultConfig.BaseRadius = get32bit(Packet, 28) / 1000.0; //
    localData.defaultConfig.EndEffectorRadius = get32bit(Packet, 32) / 1000.0; //

    localData.defaultConfig.MaxZ = get32bit(Packet, 36) / 1000.0; //

    localData.defaultConfig.MinZ = get32bit(Packet, 40) / 1000.0; //
    localData.defaultConfig.RodLength = get32bit(Packet, 44) / 1000.0; //

    writeFlashLocal();
}

boolean onConfigurationGet(BowlerPacket *Packet) {
    Packet->use.head.DataLegnth = 4;
    uint8_t index = Packet->use.data[0]; // joint space requested index

    Packet->use.data[0] = linkToHWIndex(index); // the PID link maped
    Packet->use.head.DataLegnth++;
    Packet->use.data[1] = 5; // 5 active axis
    Packet->use.head.DataLegnth++;
    set32bit(Packet, getPidGroupDataTable(Packet->use.data[0])->config.IndexLatchValue, 2);
    Packet->use.head.DataLegnth += 4;
    set32bit(Packet, -100000, 6);
    Packet->use.head.DataLegnth += 4;
    set32bit(Packet, 100000, 10);
    Packet->use.head.DataLegnth += 4;
    set32bit(Packet, getLinkScale(index)*1000, 14);
    Packet->use.head.DataLegnth += 4;

    int i = 0;
    int offset = Packet->use.head.DataLegnth - 4;
    while (getName(index)[i]) {
        Packet->use.data[offset + i] = getName(index)[i];
        i++;
        Packet->use.head.DataLegnth++;
    }
    Packet->use.data[offset + i] = 0;
    Packet->use.head.DataLegnth++;
    return true;

}

boolean onConfigurationSet(BowlerPacket *Packet) {
    //TODO fill in configuration set
    return true;

}

boolean onSlic3rConfigurationGet(BowlerPacket *Packet) {
    //TODO load slicer configs
}

boolean onSlic3rConfigurationSet(BowlerPacket *Packet) {
    //TODO set slicer configs

}

float getEndEffectorRadius() {
    return localData.defaultConfig.EndEffectorRadius;
}

float getBaseRadius() {
    return localData.defaultConfig.BaseRadius;
}

float getRodLength() {
    return localData.defaultConfig.RodLength;
}

float getmaxZ() {
    return localData.defaultConfig.MaxZ;
}

float getminZ() {
    return localData.defaultConfig.MinZ;
}

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
    localData.mmPositionResolution = value;
}

void setKP(float value) {
    localData.KP = value;
}

void setKI(float value) {
    localData.KI = value;
}

void setKD(float value) {
    localData.KD = value;
}

void setVKP(float value) {
    localData.VKP = value;
}

void setVKD(float value) {
    localData.VKD = value;
}

void checkDataTable() {
    Nop();
}

boolean initFlashLocal() {

    if (bytesOfRaw > 0x1000 - FLASHSTORE) {
        println_E("Too much data to store");
        Reset();
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
            getPidGroupDataTable(i)->config.Async = true;
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
        localData.KP = 10;
        localData.KI = 0;
        localData.KD = 0;
        localData.VKP = 1;
        localData.VKD = 0;
        localData.mmPositionResolution =.5;
        localData.maximumMMperSec = 30;
        localData.defaultConfig.BaseRadius = 140;
        localData.defaultConfig.EndEffectorRadius = 25;
        localData.defaultConfig.MaxZ = 100;
        localData.defaultConfig.MinZ = -10;
        localData.defaultConfig.RodLength = 203.82;
//        HardwareMap hwMap = {
//    {0, -1.0 * mmPerTick, "Alpha"}, //axis 0
//    {2, -1.0 * mmPerTick, "Beta"}, //axis 1
//    {4, -1.0 * mmPerTick, "Gama"}, //axis 2
//    {
//        {1, 1.0, "Extruder"}, // Motor
//        {11, 1.0, "Heater"}// Heater
//    }, //Extruder 0
//    {
//        {AXIS_UNUSED, 1.0, ""},
//        {AXIS_UNUSED, 1.0, ""}
//    }, //Extruder 1
//    {
//        {AXIS_UNUSED, 1.0, ""},
//        {AXIS_UNUSED, 1.0, ""}
//    }, //Extruder 2
//    (forwardKinematics *)& servostock_calcForward,
//    (inverseKinematics *) & servostock_calcInverse,
//    (velInverse *) & servostock_velInverse,
//    (velForward *) & servostock_velForward,
//    true
//};
        localData.hwMap.Alpha.index=0;
        localData.hwMap.Alpha.scale= -1.0 * mmPerTick;
        localData.hwMap.Alpha.name="Alpha";

        localData.hwMap.Beta.index=2;
        localData.hwMap.Beta.scale= -1.0 * mmPerTick;
        localData.hwMap.Beta.name="Beta";

        localData.hwMap.Gama.index=4;
        localData.hwMap.Gama.scale= -1.0 * mmPerTick;
        localData.hwMap.Gama.name="Gama";
        
        localData.hwMap.Extruder0.index=1;
        localData.hwMap.Extruder0.scale= 1.0 ;
        localData.hwMap.Extruder0.name="Extruder";

        localData.hwMap.Heater0.index=10;
        localData.hwMap.Heater0.scale= 1.0 ;
        localData.hwMap.Heater0.name="Heater";
        
        localData.hwMap.Extruder1.index=AXIS_UNUSED;
        localData.hwMap.Extruder1.scale= -1.0 ;
        localData.hwMap.Extruder1.name="AXIS_UNUSED";
        
        localData.hwMap.Extruder2.index=AXIS_UNUSED;
        localData.hwMap.Extruder2.scale= -1.0 ;
        localData.hwMap.Extruder2.name="AXIS_UNUSED";

        localData.hwMap.Heater1.index=AXIS_UNUSED;
        localData.hwMap.Heater1.scale= -1.0 ;
        localData.hwMap.Heater1.name="AXIS_UNUSED";

        localData.hwMap.Heater2.index=AXIS_UNUSED;
        localData.hwMap.Heater2.scale= -1.0 ;
        localData.hwMap.Heater2.name="AXIS_UNUSED";

        localData.kinematicsIndex=0;
        setKinematicsMath();
    } else {
        println_W("Flash image ok");
        setKinematicsMath();
    }
    if (rawFlashDetect)
        writeFlashLocal();

    return rawFlashDetect == false;
}

void writeFlashLocal() {

    if (bytesOfRaw > 0x1000 - FLASHSTORE) {
        println_E("Too much data to store");
        Reset();
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
