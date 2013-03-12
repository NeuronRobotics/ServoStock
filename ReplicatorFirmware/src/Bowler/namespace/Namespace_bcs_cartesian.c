#include "Bowler/Bowler.h"
#include "CartesianController.h"

static const unsigned char cartNSName[]  = "bcs.cartesian.*;0.3;;";

BOOL cartesianAsyncEventCallback(BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
    // uses its own async callback
    cartesianAsync();
    return FALSE;
}

static RPC_LIST cartesian__SLI={	BOWLER_POST,// Method
                                "_sli",//RPC as string
                                &onCartesianPost,//function pointer to a packet parsinf function
                                NULL //Termination
};

static RPC_LIST cartesian_PRCL={	BOWLER_POST,// Method
                                "pclr",//RPC as string
                                &onCartesianPost,//function pointer to a packet parsinf function
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
                namespcaedAdded =TRUE;
	}

	return &bcsCartesian;//Return pointer to the struct
}
