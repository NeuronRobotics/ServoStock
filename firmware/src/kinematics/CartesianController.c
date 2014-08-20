#include "main.h"
#if defined(__32MX795F512L__)
#define SIZE_OF_PACKET_BUFFER 400
#elif defined(__32MX440F128H__)
#define SIZE_OF_PACKET_BUFFER 60
#endif

void updateCurrentPositions();
float getLinkScale(int index);

float mmPositionResolution = .1;
static int homingAllLinks = false;

static PACKET_FIFO_STORAGE packetFifo;
static BowlerPacket buffer[SIZE_OF_PACKET_BUFFER];
static BowlerPacket linTmpPack;
static BowlerPacket packetTemp;
static PD_VEL velCartesian[3];
static AbsPID taskPID[3];

//float scale = -1.0*mmPerTick;
//static float extrusionScale = 1/(((float)ticksPerRev)/100.00);

static float current[3];
static boolean full = false;
static boolean configured = false;


static int lastPushedBufferSize = 0;
static float lastXYZE[4];

static RunEveryData pid = {0, 500};

static boolean keepCartesianPosition = false;
static int interpolationCounter = 0;
static boolean runKinematics = false;

float KP = 1;
float KI = 0;
float KD = 0;

float VKP = .01;
float VKD = 0;

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

boolean onRunKinematicsSet(BowlerPacket *Packet) {
    runKinematics = Packet->use.data[0]; // Boolean to run the kinematics or not
    return true;
}

boolean setDesiredTaskSpaceTransform(BowlerPacket *Packet) {
    println_E("setDesiredTaskSpaceTransform");
    float x = get32bit(Packet, 0) / 1000;
    float y = get32bit(Packet, 4) / 1000;
    float z = get32bit(Packet, 8) / 1000;
    //    float rx = get32bit(Packet,12)/1000;
    //    float ry = get32bit(Packet,16)/1000;
    //    float rz = get32bit(Packet,20)/1000;
    //    float w = get32bit(Packet,24)/1000;
    float ms = get32bit(Packet, 28);

    Packet->use.data[0] = 5;
    float t0 = 0, t1 = 0, t2 = 0;
    if (hwMap.iK_callback(x, y, z, &t0, &t1, &t2) == 0) {
        setInterpolateXYZ(x, y, z, ms);
        set32bit(Packet, t0, 1);
        set32bit(Packet, t1, 5);
        set32bit(Packet, t2, 9);

        set32bit(Packet, getLinkAngle(3), 13);
        set32bit(Packet, getLinkAngle(4), 17);
    } else {
        println_E("Ignoring: Can't reach: x=");
        p_fl_E(x);
        print_E(" y=");
        p_fl_E(y);
        print_E(" z=");
        p_fl_E(z);
    }
    return true;
}

boolean getCurrentTaskSpaceTransform(BowlerPacket *Packet) {
    println_E("getCurrentTaskSpaceTransform");

    float x = 0, y = 0, z = 0;
    if (hwMap.fK_callback(getLinkAngle(0), getLinkAngle(1), getLinkAngle(2), &x, &y, &z) == 0) {

        set32bit(Packet, x, 0);
        set32bit(Packet, y, 4);
        set32bit(Packet, z, 8);
        //rotation 0
        set32bit(Packet, 0, 12);
        set32bit(Packet, 0, 16);
        set32bit(Packet, 0, 20);
        set32bit(Packet, 1, 24);
    } else {
        println_E("Ignoring: Can't reach: x=");
        p_fl_E(x);
        print_E(" y=");
        p_fl_E(y);
        print_E(" z=");
        p_fl_E(z);
    }
    return true;
}

boolean setDesiredJointSpaceVector(BowlerPacket *Packet) {

    int numJoints = Packet->use.data[0];
    float j0 = get32bit(Packet, 1) / 1000;
    float j1 = get32bit(Packet, 5) / 1000;
    float j2 = get32bit(Packet, 9) / 1000;

    float extrusion = get32bit(Packet, 13) / 1000;
    float tempreture = get32bit(Packet, 17) / 1000;

    float ms = get32bit(Packet, 1 + numJoints * 4);
    println_E("setDesiredJointSpaceVector ");
    p_int_E(numJoints);
    printPacket(Packet, ERROR_PRINT);

    float x = 0, y = 0, z = 0;
    if (hwMap.fK_callback(j0, j1, j2, &x, &y, &z) == 0) {
        if (hwMap.iK_callback(x, y, z, &j0, &j1, &j2) == 0) {
            setInterpolateXYZ(x, y, z, ms);
            setLinkAngle(3, extrusion, ms);
            setLinkAngle(4, tempreture, ms);
            // load data into packet
            set32bit(Packet, x, 0);
            set32bit(Packet, y, 4);
            set32bit(Packet, z, 8);
            //rotation 0
            set32bit(Packet, 0, 12);
            set32bit(Packet, 0, 16);
            set32bit(Packet, 0, 20);
            set32bit(Packet, 1, 24);
        }
    } else {
        println_E("Ignoring: Can't reach x=");
        p_fl_E(x);
        print_E(" y=");
        p_fl_E(y);
        print_E(" z=");
        p_fl_E(z);
    }
    return true;
}

boolean setDesiredJointAxisValue(BowlerPacket *Packet) {
    println_E("setDesiredJointAxisValue");

    setLinkAngle(Packet->use.data[0], get32bit(Packet, 1) / 1000, get32bit(Packet, 5));

    return true;
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

boolean isCartesianInterpolationDone() {
    updateCurrentPositions();

    int setpointBound = 200;

    int i;
    for (i = 0; i < 4; i++) {
        if (i < 3) {
            if (!bound(taskPID[i].interpolate.set, current[i], mmPositionResolution, mmPositionResolution)) {
                //println_W("Interpolation not done on to: ");p_fl_W(taskPID[i].interpolate.set);print_W(" is = ");p_fl_W(targets[i]);
                return false;
            }
        }
        if ((isPIDArrivedAtSetpoint(linkToHWIndex(i), setpointBound) == false) && (i == 3)) {
            println_W("LINK not done moving index = ");
            p_int_W(linkToHWIndex(i));
            print_W(" currently is = ");
            p_fl_W(getPidGroupDataTable(linkToHWIndex(i))->CurrentState);
            print_W(" heading towards = ");
            p_fl_W(getPidGroupDataTable(linkToHWIndex(i))->SetPoint);
            return false;
        }

    }
    return true;
}

void initializeCartesianController() {
    InitPacketFifo(&packetFifo, buffer, SIZE_OF_PACKET_BUFFER);
    int i=0;
    for (i=0;i<3;i++){
        taskPID[i].config.Enabled=true;
        InitAbsPIDWithPosition(&taskPID[i], KP, KI, KD, getMs(),0);
    }
}

void pushBufferEmpty() {
    LoadCorePacket(& packetTemp);
    packetTemp.use.head.Method = BOWLER_ASYN;
    packetTemp.use.head.MessageID = 1;
    packetTemp.use.head.RPC = GetRPCValue("_sli");
    INT32_UNION tmp;
    tmp.Val = lastPushedBufferSize;
    packetTemp.use.data[0] = tmp.byte.FB;
    packetTemp.use.data[1] = tmp.byte.TB;
    packetTemp.use.data[2] = tmp.byte.SB;
    packetTemp.use.data[3] = tmp.byte.LB;
    packetTemp.use.head.DataLegnth = 4 + 4;
    asyncCallback(&packetTemp);
}

void loadCurrentPosition(BowlerPacket * Packet) {
    LoadCorePacket(Packet);
    Packet->use.head.Method = BOWLER_STATUS;
    Packet->use.head.MessageID = 1;
    Packet->use.head.RPC = GetRPCValue("ctps");
    INT32_UNION tmp;
    tmp.Val = lastPushedBufferSize;
    Packet->use.data[0] = tmp.byte.FB;
    Packet->use.data[1] = tmp.byte.TB;
    Packet->use.data[2] = tmp.byte.SB;
    Packet->use.data[3] = tmp.byte.LB;

    tmp.Val = SIZE_OF_PACKET_BUFFER;
    Packet->use.data[4] = tmp.byte.FB;
    Packet->use.data[5] = tmp.byte.TB;
    Packet->use.data[6] = tmp.byte.SB;
    Packet->use.data[7] = tmp.byte.LB;

    Packet->use.head.DataLegnth = 4 + 4 + 4;
}

void updateCurrentPositions() {
    if (hwMap.fK_callback(getLinkAngle(0),
            getLinkAngle(1),
            getLinkAngle(2),
            &current[0],
            &current[1],
            &current[2]) != 0) {
        println_E("Forward Kinematics Failed!!");
        return;
    }
}

void checkPositionChange() {
    int i;
    float tmp[4];
    updateCurrentPositions();

    tmp[0] = current[0];
    tmp[1] = current[1];
    tmp[2] = current[2];
    tmp[3] = getLinkAngle(3);
    if (tmp[0] != lastXYZE[0] ||
            tmp[1] != lastXYZE[1] ||
            tmp[2] != lastXYZE[2] ||
            tmp[3] != lastXYZE[3]) {
        for (i = 0; i < 4; i++) {
            lastXYZE[i] = tmp[i];
        }

        //        println_I("Current Voltage of sensor");p_fl_E(getAdcVoltage(mapHeaterIndex(HEATER0_INDEX),10));
        //        print_E(" Temp = ");p_fl_E(getHeaterTempreture(HEATER0_INDEX));
        //        print_E(" Raw ADC = ");p_int_E(getAdcRaw(mapHeaterIndex(HEATER0_INDEX),10));

        //        println_I("Current  position X=");p_fl_E(lastXYZE[0]);
        //        print_E(" Y=");p_fl_E(lastXYZE[1]);
        //        print_E(" Z=");p_fl_E(lastXYZE[2]);
        //        print_E(" extr=");p_fl_E(lastXYZE[3]);
        INT32_UNION PID_Temp;
        LoadCorePacket(& packetTemp);
        packetTemp.use.head.DataLegnth = 4;
        packetTemp.use.head.RPC = GetRPCValue("cpos");
        int i;
        for (i = 0; i < 4; i++) {
            PID_Temp.Val = lastXYZE[i];
            packetTemp.use.data[0 + (i * 4)] = PID_Temp.byte.FB;
            packetTemp.use.data[1 + (i * 4)] = PID_Temp.byte.TB;
            packetTemp.use.data[2 + (i * 4)] = PID_Temp.byte.SB;
            packetTemp.use.data[3 + (i * 4)] = PID_Temp.byte.LB;
            packetTemp.use.head.DataLegnth += 4;
        }
        packetTemp.use.head.Method = BOWLER_ASYN;
        FixPacket(&packetTemp);
        asyncCallback(& packetTemp);
    }
}

void cartesianAsync() {
    if (RunEvery(&pid)) {
        int tmp = FifoGetPacketSpaceAvailible(&packetFifo);
        if (tmp != lastPushedBufferSize) {
            lastPushedBufferSize = tmp;
            pushBufferEmpty();
            full = false;
        }
        if (runKinematics) {
            //checkPositionChange();
        }

    }
}

void processLinearInterpPacket(BowlerPacket * Packet) {
    if (Packet->use.head.RPC == _SLI) {
        //INT32_UNION tmp;
        float tmpData [5];
        int i;

        tmpData[0] = ((float) get32bit(Packet, 1));
        for (i = 1; i < 5; i++) {

            tmpData[i] = ((float) get32bit(Packet, (i * 4) + 1)) / 1000;
        }
        float t0, t1, t2;

        if (hwMap.iK_callback(tmpData[1], tmpData[2], tmpData[3], &t0, &t1, &t2) == 0) {
            setInterpolateXYZ(tmpData[1], tmpData[2], tmpData[3], tmpData[0]);
        } else {
            ERR(Packet, 33, 34);
        }
    } else {
        println_E("Wrong packet type!");
        printPacket(Packet, ERROR_PRINT);
    }
}

boolean onClearPrinter(BowlerPacket *Packet) {
    Print_Level l = getPrintLevel();
    setPrintLevelInfoPrint();
    cancelPrint();
    READY(Packet, 35, 35);
    setPrintLevel(l);
    return true;
}

boolean onCartesianPost(BowlerPacket *Packet) {

    if (FifoGetPacketSpaceAvailible(&packetFifo) > 0) {
        if (Packet->use.data[0] == 1) {
            processLinearInterpPacket(Packet);
        } else {
            println_I("Cached linear Packet ");
            p_int_I(FifoGetPacketSpaceAvailible(&packetFifo));
            FifoAddPacket(&packetFifo, Packet);
        }
        Packet->use.head.Method = BOWLER_STATUS;
        INT32_UNION tmp;
        tmp.Val = FifoGetPacketSpaceAvailible(&packetFifo);
        Packet->use.data[0] = tmp.byte.FB;
        Packet->use.data[1] = tmp.byte.TB;
        Packet->use.data[2] = tmp.byte.SB;
        Packet->use.data[3] = tmp.byte.LB;

        tmp.Val = SIZE_OF_PACKET_BUFFER;
        Packet->use.data[4] = tmp.byte.FB;
        Packet->use.data[5] = tmp.byte.TB;
        Packet->use.data[6] = tmp.byte.SB;
        Packet->use.data[7] = tmp.byte.LB;

        Packet->use.head.DataLegnth = 4 + 4 + 4;
        if (tmp.Val == 0) {
            full = true;
        }

    } else {
        println_I("###ERROR BUFFER FULL!!");
        p_int_I(FifoGetPacketSpaceAvailible(&packetFifo));

        ERR(Packet, 33, 33);
    }
    return true;
}

void cancelPrint() {
    Print_Level l = getPrintLevel();

    println_W("Cancel Print");
    setPrintLevel(l);
    InitPacketFifo(&packetFifo, buffer, SIZE_OF_PACKET_BUFFER);

    //ZeroPID(hwMap.Extruder0.index);
    //SetPIDTimed(hwMap.Heater0.index,0,0);
}

boolean onCartesianGet(BowlerPacket *Packet) {
    return false;
}

boolean onCartesianCrit(BowlerPacket *Packet) {
    return false;
}

boolean onCartesianPacket(BowlerPacket *Packet) {
    Print_Level l = getPrintLevel();

    println_I("Packet Checked by Cartesian Controller");
    boolean ret = false;
    switch (Packet->use.head.Method) {
        case BOWLER_POST:
            ret = onCartesianPost(Packet);
            break;
        case BOWLER_GET:
            ret = onCartesianGet(Packet);
            break;
        case BOWLER_CRIT:
            ret = onCartesianCrit(Packet);
            break;
    }
    setPrintLevel(l);
    return ret;
}

void printXYZ(int xyz) {
    switch (xyz) {
        case 0:
            print_W("X");
            break;
        case 1:
            print_W("Y");
            break;
        case 2:
            print_W("Z");
            break;
    }
}

void printCartesianData() {
    updateCurrentPositions();
    println_W("Current  position cx=");
    p_fl_W(current[0]);

    print_W(" cy=");
    p_fl_W(current[1]);
    print_W(" cz=");
    p_fl_W(current[2]);
    println_W("Current  angles Alpha=");
    p_fl_W(getLinkAngle(0));
    print_W(" Beta=");
    p_fl_W(getLinkAngle(1));
    print_W(" Gamma=");
    p_fl_W(getLinkAngle(2));

    println_W("Raw  angles Alpha=");
    p_fl_W(getLinkAngleNoScale(0));
    print_W(" Beta=");
    p_fl_W(getLinkAngleNoScale(1));
    print_W(" Gamma=");
    p_fl_W(getLinkAngleNoScale(2));

}

void runInterpolatedPositions() {
    float x = 0, y = 0, z = 0;
    float ms = getMs();

    x = interpolate(& taskPID[0].interpolate, ms);
    y = interpolate(& taskPID[1].interpolate, ms);
    z = interpolate(& taskPID[2].interpolate, ms);
    if (isCartesianInterpolationDone() == false) {
        setXYZ(x, y, z, 0);
    }
}

void setVelocity(int index, float jointSpace) {
    float value = (jointSpace /
            getLinkScale(index));
    println_I("V ");
    p_int_I(index);
    print_I(" = ");
    p_fl_I(jointSpace);
    print_I(" : ");
    p_fl_I(value);
    setOutput(linkToHWIndex(index),
            value);
}

float calculateTaskSpaceVelocityValue(int xyz) {
    println_W(" ");
    printXYZ(xyz);
    print_W(" Data: ");
    float ms = getMs();
    taskPID[xyz].CurrentState = current[xyz];
    taskPID[xyz].SetPoint = interpolate(&taskPID[xyz].interpolate,getMs());
    RunAbstractPIDCalc(&taskPID[xyz],ms);

    float currentTarget =taskPID[xyz].SetPoint;
    float currentError = currentTarget - current[xyz];

    //runPdVelocityFromPointer(&velCartesian[xyz], current[xyz], VKP, VKD);


    if (currentError > mmPositionResolution || currentError < -mmPositionResolution) {
        println_E("\terror=   ");
        p_fl_E(currentError);
        if (getMs()>(taskPID[xyz].interpolate.setTime + taskPID[xyz].interpolate.startTime)) {
            return taskPID[xyz].Output;
        } else {
            print_W(" TIMED ");
            return taskPID[xyz].Output;
        }
    } else {
        println_W("\terror=   ");
        p_fl_W(currentError);
        return 0;
    }


}
RunEveryData velPrinter = {0, 500};

void runStateBasedController() {
    float Xd, Yd, Zd;
    float Ad, Bd, Cd;

    if (RunEvery(&velPrinter)) {
        setPrintLevelInfoPrint();
        clearPrint();
    }
    Xd = calculateTaskSpaceVelocityValue(0);
    Yd = calculateTaskSpaceVelocityValue(1);
    Zd = calculateTaskSpaceVelocityValue(2);

    if (hwMap.iVel_callback(current[0], current[1], current[2], Xd, Yd, Zd,
            & Ad, & Bd, & Cd) == 0) {
        int i = 0;
        for (i = 0; i < 3; i++) {
            SetPIDEnabled(linkToHWIndex(i), false);
        }
        setVelocity(0, Ad);
        setVelocity(1, Bd);
        setVelocity(2, Cd);

    } else {
        println_E("Inverse velocity kinematics failed");
    }
    setPrintLevelNoPrint();


}

void interpolateZXY() {
    updateCurrentPositions();
    interpolationCounter = 0;
    if (!configured) {
        HomeLinks();
        return;
    }
    if (!runKinematics) {
        return;
    }
    keepCartesianPosition = true;
    if (keepCartesianPosition) {
        if (hwMap.useStateBasedVelocity) {
            runStateBasedController();
        } else {
            runInterpolatedPositions();
        }
        if (isCartesianInterpolationDone()) {
            if (FifoGetPacketCount(&packetFifo) > 0) {
                println_W("Loading new packet ");
                if (FifoGetPacket(&packetFifo, &linTmpPack)) {
                    processLinearInterpPacket(&linTmpPack);
                }
            } else {
                keepCartesianPosition = false;
            }
        }
    }
}

uint8_t setInterpolateXYZ(float x, float y, float z, float ms) {
    int i = 0;
    if (ms < .01)
        ms = 0;
    float start = getMs();
    float valocity_calculated;
    updateCurrentPositions();
    float tmp[3] = {x, y, z};

    println_W("Setting new position x=");
    p_fl_W(x);
    print_W(" y=");
    p_fl_W(y);
    print_W(" z=");
    p_fl_W(z);
    print_W(" Time MS=");
    p_fl_W(ms);
    println_W("Current  position cx=");
    p_fl_W(current[0]);

    print_W(" cy=");
    p_fl_W(current[1]);
    print_W(" cz=");
    p_fl_W(current[2]);
    println_W("Current  angles Alpha=");
    p_fl_W(getLinkAngle(0));
    print_W(" Beta=");
    p_fl_W(getLinkAngle(1));
    print_W(" Gamma=");
    p_fl_W(getLinkAngle(2));

    for (i = 0; i < 3; i++) {
        SetPIDTimedPointer(&taskPID[i], tmp[i], current[i], ms);
        printPIDvalsPointer(&taskPID[i]);
        valocity_calculated = ((taskPID[i].interpolate.set - taskPID[i].interpolate.start) / (taskPID[i].interpolate.setTime / 1000));
        println_W("Setting new position FEED RATE=");
        p_fl_W(valocity_calculated);

        velCartesian[i].unitsPerSeCond = valocity_calculated;
        velCartesian[i].currentOutputVel = valocity_calculated;
        velCartesian[i].lastTime = getMs();
        velCartesian[i].lastVelocity = 0;
        velCartesian[i].lastPosition = current[i];

    }

    runKinematics = true;

    if (ms == 0) {
        println_I("Setting values directly");
        setXYZ(x, y, z, 0);
    } else {
        keepCartesianPosition = true;
        if (hwMap.useStateBasedVelocity == false) {
            println_I("Setting values with linear interpolation");
            start = getMs();
            x = interpolate(& taskPID[0].interpolate, start);
            y = interpolate(& taskPID[1].interpolate, start);
            z = interpolate(& taskPID[2].interpolate, start);
            setXYZ(x, y, z, 0);
        } else {
            println_I("Using the State-based velocity controller");

        }
    }
    //setPrintLevelNoPrint();
    return 0;
}

uint8_t setXYZ(float x, float y, float z, float ms) {
    updateCurrentPositions();
    float t0 = 0, t1 = 0, t2 = 0;
    if (hwMap.iK_callback(x, y, z, &t0, &t1, &t2) == 0) {
        println_I("New target angles t1=");
        p_fl_I(t0);
        print_I(" t2=");
        p_fl_I(t1);
        print_I(" t3=");
        p_fl_I(t2);
        setLinkAngle(0, t0, ms);
        setLinkAngle(1, t1, ms);
        setLinkAngle(2, t2, ms);
    } else {
        println_E("Interpolate failed, can't reach: x=");
        p_fl_E(x);
        print_E(" y=");
        p_fl_E(y);
        print_E(" z=");
        p_fl_E(z);
    }
    return 0;
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

float getLinkAngleNoScale(int index) {
    int localIndex = linkToHWIndex(index);
    return GetPIDPosition(localIndex);
}

float getLinkAngle(int index) {

    return getLinkAngleNoScale(index) * getLinkScale(index);
}

float setLinkAngle(int index, float value, float ms) {
    int localIndex = linkToHWIndex(index);
    float v = value / getLinkScale(index);
    if (index == 0 ||
            index == 1 ||
            index == 2
            ) {
        //        if(v>1650){
        //            println_E("Upper Capped link ");p_int_E(index);print_E(", attempted: ");p_fl_E(value);
        //            v=1650;
        //        }
        //        if(v<-6500){
        //            v=-6500;
        //            println_E("Lower Capped link ");p_int_E(index);print_E(", attempted: ");p_fl_E(value);
        //        }
    }
    //    println_I("Setting position from cartesian controller ");p_int_I(localIndex);print_I(" to ");p_fl_I(v);
    //    print_I(" in ");p_fl_I(ms); print_I("ms ");

    SetPIDEnabled(localIndex, true);

    return SetPIDTimed(localIndex, v, ms);
}

void startHomingLinks() {
    println_W("Homing links for kinematics");

    homingAllLinks = true;

    startHomingLink(linkToHWIndex(0), CALIBRARTION_home_down);
    startHomingLink(linkToHWIndex(1), CALIBRARTION_home_down);
    startHomingLink(linkToHWIndex(2), CALIBRARTION_home_down);
    println_W("Started Homing...");
}

void HomeLinks() {
    if (homingAllLinks) {
        if (GetPIDCalibrateionState(linkToHWIndex(0)) == CALIBRARTION_DONE &&
                GetPIDCalibrateionState(linkToHWIndex(1)) == CALIBRARTION_DONE &&
                GetPIDCalibrateionState(linkToHWIndex(2)) == CALIBRARTION_DONE
                ) {
            homingAllLinks = false;
            configured = true;
            println_W("All linkes reported in");
            BYTE_FIFO_STORAGE * data = GetPICUSBFifo();

            int i;
            float Alpha, Beta, Gama;
            hwMap.iK_callback(0, 0, getmaxZ(), &Alpha, &Beta, &Gama);
            for (i = 0; i < 3; i++) {
                pidReset(linkToHWIndex(i), (Alpha + getRodLength() / 3) / getLinkScale(i));
            }
            cancelPrint();
            setInterpolateXYZ(0, 0, getmaxZ(), 5000);
        }
    }
}
