#include "Bowler/Bowler.h"
#include "CartesianController.h"
#include "ReplicatorHeader.h"

static const unsigned char cartNSName[]  = "bcs.cartesian.*;0.3;;";

BOOL cartesianAsyncEventCallback(BowlerPacket * Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){

    Print_Level l = getPrintLevel();
    //setPrintLevelNoPrint();
    if(!getRunPidIsr()){
        RunPIDControl();
    }
    setPrintLevel(l);
    //printPIDvals(6);
    // uses its own async callback
    //cartesianAsync();
    return FALSE;
}

static RPC_LIST cartesian__SLI={	BOWLER_POST,// Method
                                "_sli",//RPC as string
                                &onCartesianPost,//function pointer to a packet parsinf function
                                NULL,// Calling arguments
                                BOWLER_POST,// response method
                                NULL,// Response arguments
                                NULL //Termination
};

static RPC_LIST cartesian_GCFG={	BOWLER_GET,// Method
                                "gcfg",//RPC as string
                                &onConfigurationGet,//function pointer to a packet parsinf function
                                ((const char [2]){  BOWLER_I08,
                                                    0}),// Calling arguments
                                BOWLER_POST,// response method
                                ((const char [8]){  BOWLER_I08,//index
                                        BOWLER_I08,//total links
                                        BOWLER_I32,//latch
                                        BOWLER_I32,//lower limit
                                        BOWLER_I32,//upper limit
                                        BOWLER_FIXED1K,//scale
                                        BOWLER_ASCII,// name
                                                    0}),// Response arguments
                                NULL //Termination
};

static RPC_LIST cartesian_PRCL={	BOWLER_POST,// Method
                                "pclr",//RPC as string
                                &onCartesianPost,//function pointer to a packet parsinf function
                                NULL,// Calling arguments
                                BOWLER_POST,// response method
                                NULL,// Response arguments
                                NULL //Termination
};


static NAMESPACE_LIST bcsCartesian ={	cartNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &cartesianAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * getBcsCartesianNamespace(){
	if(!namespcaedAdded){
                //POST
                //Add the RPC structs to the namespace
                addRpcToNamespace(&bcsCartesian,& cartesian__SLI);
                addRpcToNamespace(&bcsCartesian,& cartesian_PRCL);
                addRpcToNamespace(&bcsCartesian,& cartesian_GCFG);
                namespcaedAdded =TRUE;
	}

	return &bcsCartesian;//Return pointer to the struct
}
