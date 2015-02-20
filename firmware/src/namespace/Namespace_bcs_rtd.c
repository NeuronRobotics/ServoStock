#include "main.h"
  //const char rtdNSName[] = "neuronrobotics.pid.rtd.*;0.3;;";

  RPC_LIST pid_setSteinHartHartCoefs = {BOWLER_POST, // Method
    "sshh", //RPC as string
    &setSensorCoefs, //function pointer to a packet parsinf function
    {
        BOWLER_I08, //chan
        BOWLER_FIXED1K,//a
        BOWLER_FIXED1K,//b
        BOWLER_FIXED1K,//c
        0
    }, // Response arguments
    BOWLER_POST, // response method
    {0}, // Response arguments
    NULL //Termination
};

  NAMESPACE_LIST neuronroboticsPidRTD = { "neuronrobotics.pid.rtd.*;0.3;;", // The string defining the namespace
    NULL, // the first element in the RPC list
    &PidRTDAsyncEventCallback, // async for this namespace
    NULL// no initial elements to the other namesapce field.
};

boolean namespcaedAddedBcsRtd = false;

NAMESPACE_LIST * getNeuronroboticsPidRTD() {
    if (!namespcaedAddedBcsRtd) {
        //POST
        //Add the RPC structs to the namespace
        addRpcToNamespace(&neuronroboticsPidRTD, & pid_setSteinHartHartCoefs);
        //addRpcToNamespace(&neuronroboticsPidRTD, & cartesian__SLI);


        namespcaedAddedBcsRtd = true;
    }

    return &neuronroboticsPidRTD; //Return pointer to the struct
}


