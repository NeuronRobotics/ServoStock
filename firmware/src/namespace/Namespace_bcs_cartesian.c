#include "main.h"

 // const char cartNSName[] = "bcs.cartesian.*;0.3;;";

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

  RPC_LIST cartesian_runk = {BOWLER_POST, // Method
    "runk", //RPC as string
    &onRunKinematicsSet, //function pointer to a packet parsing function
    {BOWLER_BOOL, //Run or not boolean
        0
    }, // Calling arguments
    BOWLER_POST, // response method
    {0}, // Response arguments
    NULL //Termination
};


// Abstract Kinematics commnds

  RPC_LIST cartesian_SDSJ = {BOWLER_POST, // Method
    "sdsj", //RPC as string
    &setDesiredJointAxisValue, //function pointer to a packet parsing function
    {BOWLER_I08, //axis
        BOWLER_FIXED1K, //value
        BOWLER_I32, //ms
        0
    }, // Calling arguments
    BOWLER_POST, // response method
    {0}, // Response arguments
    NULL //Termination
};

  RPC_LIST cartesian_SDJV = {BOWLER_POST, // Method
    "sdjv", //RPC as string
    &setDesiredJointSpaceVector, //function pointer to a packet parsing function
    {BOWLER_FIXED1K_STR, //Run or not boolean
        BOWLER_I32, //ms
        0
    }, // Calling arguments
    BOWLER_POST, // response method
    {
        BOWLER_FIXED1K, //x
        BOWLER_FIXED1K, //y
        BOWLER_FIXED1K, //z
        BOWLER_FIXED1K, //rx
        BOWLER_FIXED1K, //ry
        BOWLER_FIXED1K, //rz
        BOWLER_FIXED1K, //w
        0
    }, // Calling arguments
    NULL //Termination
};

  RPC_LIST cartesian_GCTT = {BOWLER_GET, // Method
    "gctt", //RPC as string
    &getCurrentTaskSpaceTransform, //function pointer to a packet parsing function
    {0}, //  arguments
    BOWLER_POST, // response method
    {BOWLER_FIXED1K, //x
        BOWLER_FIXED1K, //y
        BOWLER_FIXED1K, //z
        BOWLER_FIXED1K, //rx
        BOWLER_FIXED1K, //ry
        BOWLER_FIXED1K, //rz
        BOWLER_FIXED1K, //w
        0
    }, // Calling arguments
    NULL //Termination
};

  RPC_LIST cartesian_SDTT = {BOWLER_POST, // Method
    "sdtt", //RPC as string
    &setDesiredTaskSpaceTransform, //function pointer to a packet parsing function
    {
        BOWLER_FIXED1K, //x
        BOWLER_FIXED1K, //y
        BOWLER_FIXED1K, //z
        BOWLER_FIXED1K, //rx
        BOWLER_FIXED1K, //ry
        BOWLER_FIXED1K, //rz
        BOWLER_FIXED1K, //w
        BOWLER_I32, //ms
        0
    }, // Calling arguments
    BOWLER_POST, // response method
    {BOWLER_FIXED1K_STR, //current joint values
        0
    }, // Calling arguments
    NULL //Termination
};


// Send a print line

  RPC_LIST cartesian__SLI = {BOWLER_POST, // Method
    "_sli", //RPC as string
    &onCartesianPost, //function pointer to a packet parsing function
     {
        BOWLER_I32, //ms
        BOWLER_FIXED1K, //x
        BOWLER_FIXED1K, //y
        BOWLER_FIXED1K, //z
        BOWLER_FIXED1K, //E
        0
    }, // Calling arguments
    BOWLER_POST, // response method
    {
        BOWLER_I32, //Space in FIFo
        BOWLER_I32, //Size of FIFO
        0
    }, // Calling arguments
    NULL //Termination
};

// Get axis cartesian configuration

  RPC_LIST cartesian_GCFG = {BOWLER_GET, // Method
    "gcfg", //RPC as string
    &onConfigurationGet, //function pointer to a packet parsing function
    {
        BOWLER_I08,//Joint space Index
        0
    }, // Calling arguments
    BOWLER_POST, // response method
     {
        BOWLER_I08, //HW index
        BOWLER_I08, //total links
        BOWLER_I32, //latch
        BOWLER_I32, //lower limit
        BOWLER_I32, //upper limit
        BOWLER_FIXED1K, //scale
        BOWLER_ASCII, // name
        0
    }, // Calling arguments
    NULL //Termination
};
// Set axis cartesian configuration

  RPC_LIST cartesian_SCFG = {BOWLER_POST, // Method
    "scfg", //RPC as string
    &onConfigurationSet, //function pointer to a packet parsing function
    {
        BOWLER_I08, //Joint space Index
        BOWLER_I08, //HW index
        BOWLER_FIXED1K, //scale
        BOWLER_I32, //latch
        BOWLER_I32, //lower limit
        BOWLER_I32, //upper limit
        0
    }, // Calling arguments
    BOWLER_STATUS, // response method
    {0},
    NULL //Termination
};

// Clear the running print
  RPC_LIST cartesian_PRCL = {BOWLER_POST, // Method
    "pclr", //RPC as string
    &onClearPrinter, //function pointer to a packet parsing function
    {0}, // Calling arguments
    BOWLER_POST, // response method
    {0}, // Response arguments
    NULL //Termination
};

// Pause the running print
  RPC_LIST cartesian_PAUS = {BOWLER_POST, // Method
    "paus", //RPC as string
    &onPausePrinter, //function pointer to a packet parsing function
    {BOWLER_BOOL, // pause state
        0
    }, // Calling arguments
    BOWLER_STATUS, // response method
    {0}, // Response arguments
    NULL //Termination
};

// Get Pause the running print
  RPC_LIST cartesian_PAUS_g = {BOWLER_GET, // Method
    "paus", //RPC as string
    &onPausePrinter, //function pointer to a packet parsing function
    {0},
    BOWLER_POST, // response method
    {BOWLER_BOOL, // pause state
        0
    }, // Calling arguments
    NULL //Termination
};

// set the kinematics model
  RPC_LIST cartesian_KMOD_p = {BOWLER_POST, // Method
    "kmod", //RPC as string
    &onKinematicsModelSet, //function pointer to a packet parsing function
     {BOWLER_I08, // index of the kinematics model to use
        0
    }, // Calling arguments
    BOWLER_STATUS, // response method
    {0}, // Response arguments
    NULL //Termination
};

// set the kinematics model
  RPC_LIST cartesian_KMOD_g = {BOWLER_GET, // Method
    "kmod", //RPC as string
    &onKinematicsModelGet, //function pointer to a packet parsing function
    {0}, // Response arguments
    BOWLER_POST, // response method
    { BOWLER_I08, // index of the kinematics model to use
        0
    }, // Calling arguments
    NULL //Termination
};

// Home printer
  RPC_LIST cartesian_HOME = {BOWLER_POST, // Method
    "home", //RPC as string
    &onHomePrinter, //function pointer to a packet parsing function
    {0},
    BOWLER_STATUS, // response method
    {0}, // Response arguments
    NULL //Termination
};

//State Based Controller configuration

  RPC_LIST cartesian_SBCG = {BOWLER_GET, // Method
    "sbcc", //RPC as string
    &onControllerConfigurationGet, //function pointer to a packet parsing function
    {0}, // Calling arguments
    BOWLER_POST, // response method
    {BOWLER_FIXED1K, //KP
        BOWLER_FIXED1K, //KI
        BOWLER_FIXED1K, //KD
        BOWLER_FIXED1K, //VKP
        BOWLER_FIXED1K, //VKD
        BOWLER_FIXED1K, //mmPositionResolution
        BOWLER_FIXED1K, // maximumMMperSec
        BOWLER_FIXED1K, // float RodLength;
	BOWLER_FIXED1K, // float BaseRadius;
	BOWLER_FIXED1K, // float EndEffectorRadius;
	BOWLER_FIXED1K, // float MaxZ;
	BOWLER_FIXED1K, // float MinZ;
        BOWLER_BOOL,// use hard positioning
        0
    }, // Calling arguments
    NULL //Termination
};

  RPC_LIST cartesian_SBCP = {BOWLER_POST, // Method
    "sbcc", //RPC as string
    &onControllerConfigurationSet, //function pointer to a packet parsing function
    {BOWLER_FIXED1K, //KP
        BOWLER_FIXED1K, //KI
        BOWLER_FIXED1K, //KD
        BOWLER_FIXED1K, //VKP
        BOWLER_FIXED1K, //VKD
        BOWLER_FIXED1K, //mmPositionResolution
        BOWLER_FIXED1K, // maximumMMperSec
        BOWLER_FIXED1K, // float RodLength;
	BOWLER_FIXED1K, // float BaseRadius;
	BOWLER_FIXED1K, // float EndEffectorRadius;
	BOWLER_FIXED1K, // float MaxZ;
	BOWLER_FIXED1K, // float MinZ;
        BOWLER_BOOL,// use hard positioning
        0
    }, // Calling arguments
    BOWLER_STATUS, // response method
    {0}, // Response arguments
    NULL //Termination
};


//Slic3r commands
  RPC_LIST cartesian_SLCR_g = {BOWLER_GET, // Method
    "slcr", //RPC as string
    &onSlic3rConfigurationGet, //function pointer to a packet parsing function
    {0}, // Calling arguments
    BOWLER_POST, // response method
    {BOWLER_FIXED1K_STR, //Slicer configurations
        0
    }, // Calling arguments
    NULL //Termination
};

  RPC_LIST cartesian_LSCR_p = {BOWLER_POST, // Method
    "slcr", //RPC as string
    &onSlic3rConfigurationSet, //function pointer to a packet parsing function
    {    BOWLER_FIXED1K_STR, //Slicer configurations
        0
    }, // Calling arguments
    BOWLER_STATUS, // response method
    {0}, // Response arguments
    NULL //Termination
};


  NAMESPACE_LIST bcsCartesian = {"bcs.cartesian.*;0.3;;", // The string defining the namespace
    NULL, // the first element in the RPC list
    &cartesianAsyncEventCallback, // async for this namespace
    NULL// no initial elements to the other namesapce field.
};



  boolean namespcaedAdded = false;

NAMESPACE_LIST * getBcsCartesianNamespace() {
    if (!namespcaedAdded) {
        //POST
        //Add the RPC structs to the namespace
        addRpcToNamespace(&bcsCartesian, & cartesian_runk);
        addRpcToNamespace(&bcsCartesian, & cartesian__SLI);
        addRpcToNamespace(&bcsCartesian, & cartesian_PRCL);
        addRpcToNamespace(&bcsCartesian, & cartesian_GCFG);
        addRpcToNamespace(&bcsCartesian, & cartesian_SCFG);
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
        addRpcToNamespace(&bcsCartesian, & cartesian_KMOD_p);
        addRpcToNamespace(&bcsCartesian, & cartesian_KMOD_g);
        addRpcToNamespace(&bcsCartesian, & cartesian_PAUS_g);
        namespcaedAdded = true;
    }

    return &bcsCartesian; //Return pointer to the struct
}
