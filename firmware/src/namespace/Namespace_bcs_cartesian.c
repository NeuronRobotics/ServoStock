#include "main.h"

static const char cartNSName[] = "bcs.cartesian.*;0.3;;";

boolean cartesianAsyncEventCallback(BowlerPacket * Packet, boolean(*pidAsyncCallbackPtr)(BowlerPacket *Packet)) {

    Print_Level l = getPrintLevel();
    //setPrintLevelNoPrint();
    if (!getRunPidIsr()) {
        RunPIDControl();
    }
    setPrintLevel(l);
    //printPIDvals(6);
    // uses its own async callback
    cartesianAsync();
    return false;
}

static RPC_LIST cartesian_runk = {BOWLER_POST, // Method
    "runk", //RPC as string
    &onRunKinematicsSet, //function pointer to a packet parsinf function
    ((const char [2]) {
        BOWLER_BOOL, //Run or not boolean
        0
    }), // Response arguments
    BOWLER_POST, // response method
    NULL, // Response arguments
    NULL //Termination
};


// Abstract Kinematics commnds

static RPC_LIST cartesian_SDSJ = {BOWLER_POST, // Method
    "sdsj", //RPC as string
    &setDesiredJointAxisValue, //function pointer to a packet parsinf function
    ((const char [4]) {
        BOWLER_I08, //axis
        BOWLER_FIXED1K, //value
        BOWLER_I32, //ms
        0
    }), // Response arguments
    BOWLER_POST, // response method
    NULL, // Response arguments
    NULL //Termination
};

static RPC_LIST cartesian_SDJV = {BOWLER_POST, // Method
    "sdjv", //RPC as string
    &setDesiredJointSpaceVector, //function pointer to a packet parsinf function
    ((const char [3]) {
        BOWLER_FIXED1K_STR, //Run or not boolean
        BOWLER_I32, //ms
        0
    }), // Response arguments
    BOWLER_POST, // response method
    ((const char [8]) {
        BOWLER_FIXED1K, //x
        BOWLER_FIXED1K, //y
        BOWLER_FIXED1K, //z
        BOWLER_FIXED1K, //rx
        BOWLER_FIXED1K, //ry
        BOWLER_FIXED1K, //rz
        BOWLER_FIXED1K, //w
        0
    }), // Response arguments
    NULL //Termination
};

static RPC_LIST cartesian_GCTT = {BOWLER_GET, // Method
    "gctt", //RPC as string
    &getCurrentTaskSpaceTransform, //function pointer to a packet parsinf function
    NULL, //  arguments
    BOWLER_POST, // response method
    ((const char [8]) {
        BOWLER_FIXED1K, //x
        BOWLER_FIXED1K, //y
        BOWLER_FIXED1K, //z
        BOWLER_FIXED1K, //rx
        BOWLER_FIXED1K, //ry
        BOWLER_FIXED1K, //rz
        BOWLER_FIXED1K, //w
        0
    }), // Response arguments
    NULL //Termination
};

static RPC_LIST cartesian_SDTT = {BOWLER_POST, // Method
    "sdtt", //RPC as string
    &setDesiredTaskSpaceTransform, //function pointer to a packet parsinf function
    ((const char [9]) {
        BOWLER_FIXED1K, //x
        BOWLER_FIXED1K, //y
        BOWLER_FIXED1K, //z
        BOWLER_FIXED1K, //rx
        BOWLER_FIXED1K, //ry
        BOWLER_FIXED1K, //rz
        BOWLER_FIXED1K, //w
        BOWLER_I32, //ms
        0
    }), // Response arguments
    BOWLER_POST, // response method
    ((const char [2]) {
        BOWLER_FIXED1K_STR, //current joint values
        0
    }), // Response arguments
    NULL //Termination
};


// Send a print line

static RPC_LIST cartesian__SLI = {BOWLER_POST, // Method
    "_sli", //RPC as string
    &onCartesianPost, //function pointer to a packet parsinf function
    ((const char [6]) {
        BOWLER_I32, //ms
        BOWLER_FIXED1K, //x
        BOWLER_FIXED1K, //y
        BOWLER_FIXED1K, //z
        BOWLER_FIXED1K, //E
        0
    }), // Response arguments
    BOWLER_POST, // response method
    ((const char [3]) {
        BOWLER_I32, //Space in FIFo
        BOWLER_I32, //Size of FIFO
        0
    }), // Response arguments
    NULL //Termination
};

// Get axis cartesian configuration

static RPC_LIST cartesian_GCFG = {BOWLER_GET, // Method
    "gcfg", //RPC as string
    &onConfigurationGet, //function pointer to a packet parsinf function
    ((const char [2]) {
        BOWLER_I08,
        0
    }), // Calling arguments
    BOWLER_POST, // response method
    ((const char [8]) {
        BOWLER_I08, //index
        BOWLER_I08, //total links
        BOWLER_I32, //latch
        BOWLER_I32, //lower limit
        BOWLER_I32, //upper limit
        BOWLER_FIXED1K, //scale
        BOWLER_ASCII, // name
        0
    }), // Response arguments
    NULL //Termination
};

// Set axis cartesian configuration

static RPC_LIST cartesian_SCFG = {BOWLER_GET, // Method
    "scfg", //RPC as string
    &onConfigurationSet, //function pointer to a packet parsinf function
    ((const char [8]) {
        BOWLER_I08, //index
        BOWLER_I08, //total links
        BOWLER_I32, //latch
        BOWLER_I32, //lower limit
        BOWLER_I32, //upper limit
        BOWLER_FIXED1K, //scale
        BOWLER_ASCII, // name
        0
    }), // Response arguments
    BOWLER_STATUS, // response method
    NULL,
    NULL //Termination
};

// Clear the running print
static RPC_LIST cartesian_PRCL = {BOWLER_POST, // Method
    "pclr", //RPC as string
    &onClearPrinter, //function pointer to a packet parsinf function
    NULL, // Calling arguments
    BOWLER_POST, // response method
    NULL, // Response arguments
    NULL //Termination
};
// Pause the running print

static RPC_LIST cartesian_PAUS = {BOWLER_POST, // Method
    "paus", //RPC as string
    &onClearPrinter, //function pointer to a packet parsinf function
    ((const char [2]) {
        BOWLER_I08, // pause state
        0
    }), // Calling arguments
    BOWLER_STATUS, // response method
    NULL, // Response arguments
    NULL //Termination
};


// Home printer
static RPC_LIST cartesian_HOME = {BOWLER_POST, // Method
    "home", //RPC as string
    &onClearPrinter, //function pointer to a packet parsinf function
    NULL,
    BOWLER_STATUS, // response method
    NULL, // Response arguments
    NULL //Termination
};

//State Based Controller configuration

static RPC_LIST cartesian_SBCG = {BOWLER_GET, // Method
    "sbcc", //RPC as string
    &onControllerConfigurationGet, //function pointer to a packet parsinf function
    NULL, // Calling arguments
    BOWLER_POST, // response method
    ((const char [8]) {
        BOWLER_FIXED1K, //KP
        BOWLER_FIXED1K, //KI
        BOWLER_FIXED1K, //KD
        BOWLER_FIXED1K, //VKP
        BOWLER_FIXED1K, //VKD
        BOWLER_FIXED1K, //mmPositionResolution
        BOWLER_FIXED1K, // maximumMMperSec
        0
    }), // Response arguments
    NULL //Termination
};

static RPC_LIST cartesian_SBCP = {BOWLER_POST, // Method
    "sbcc", //RPC as string
    &onControllerConfigurationSet, //function pointer to a packet parsinf function
    ((const char [8]) {
        BOWLER_FIXED1K, //KP
        BOWLER_FIXED1K, //KI
        BOWLER_FIXED1K, //KD
        BOWLER_FIXED1K, //VKP
        BOWLER_FIXED1K, //VKD
        BOWLER_FIXED1K, //mmPositionResolution
        BOWLER_FIXED1K, // maximumMMperSec
        0
    }), // Response arguments
    BOWLER_STATUS, // response method
    NULL, // Response arguments
    NULL //Termination
};


//Slic3r commands
static RPC_LIST cartesian_SLCR_g = {BOWLER_GET, // Method
    "slcr", //RPC as string
    &onSlic3rConfigurationGet, //function pointer to a packet parsinf function
    NULL, // Calling arguments
    BOWLER_POST, // response method
    NULL, // Response arguments
    NULL //Termination
};

static RPC_LIST cartesian_LSCR_p = {BOWLER_POST, // Method
    "slcr", //RPC as string
    &onSlic3rConfigurationSet, //function pointer to a packet parsinf function
    NULL, // Calling arguments
    BOWLER_STATUS, // response method
    NULL, // Response arguments
    NULL //Termination
};


static NAMESPACE_LIST bcsCartesian = {cartNSName, // The string defining the namespace
    NULL, // the first element in the RPC list
    &cartesianAsyncEventCallback, // async for this namespace
    NULL// no initial elements to the other namesapce field.
};



static boolean namespcaedAdded = false;

NAMESPACE_LIST * getBcsCartesianNamespace() {
    if (!namespcaedAdded) {
        //POST
        //Add the RPC structs to the namespace
        addRpcToNamespace(&bcsCartesian, & cartesian_runk);
        addRpcToNamespace(&bcsCartesian, & cartesian__SLI);
        addRpcToNamespace(&bcsCartesian, & cartesian_PRCL);
        addRpcToNamespace(&bcsCartesian, & cartesian_GCFG);

        addRpcToNamespace(&bcsCartesian, & cartesian_SDTT);
        addRpcToNamespace(&bcsCartesian, & cartesian_GCTT);
        addRpcToNamespace(&bcsCartesian, & cartesian_SDJV);
        addRpcToNamespace(&bcsCartesian, & cartesian_SDSJ);
        addRpcToNamespace(&bcsCartesian, & cartesian_SBCG);
        addRpcToNamespace(&bcsCartesian, & cartesian_SBCP);
        addRpcToNamespace(&bcsCartesian, & cartesian_SLCR_g);
        addRpcToNamespace(&bcsCartesian, & cartesian_LSCR_p);
        addRpcToNamespace(&bcsCartesian, & cartesian_PAUS);
        addRpcToNamespace(&bcsCartesian, & cartesian_HOME);

        namespcaedAdded = true;
    }

    return &bcsCartesian; //Return pointer to the struct
}
