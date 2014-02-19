/* 
 * File:   CartesianController.h
 * Author: hephaestus
 *
 * Created on October 10, 2012, 10:58 AM
 */

#ifndef CARTESIANCONTROLLER_H
#define	CARTESIANCONTROLLER_H
#include "Bowler/Bowler_Helper.h"

//#define EXTRUDER0_INDEX 0
//#define HEATER0_INDEX   11
//#define LINK0_INDEX 6
//#define LINK1_INDEX 7
//#define LINK2_INDEX 4
#define AXIS_UNUSED 0xFF
typedef BOOL forwardKinematics(float Alpha, float Beta, float Gama, float * x0, float *y0, float * z0);
typedef BOOL inverseKinematics(float x0, float y0, float z0, float *Alpha, float *Beta, float *Gama);

typedef struct  _IndexScale{
    int index;
    float scale;
}IndexScale;

typedef struct  _HardwareMap{
    IndexScale Alpha;
    IndexScale Beta;
    IndexScale Gama;
    struct {
        IndexScale Heater0;
        IndexScale Extruder0;
    };
    struct{
        IndexScale Heater1;
        IndexScale Extruder1;
    };
    struct{
        IndexScale Heater2;
        IndexScale Extruder2;
    };
    //forwardKinematics * fK_callback;
    inverseKinematics * iK_callback;
}HardwareMap;


#ifdef	__cplusplus
extern "C" {
#endif
typedef struct  _Transform{
    float x;
    float y;
    float z;
    float rotation[3][3];
}Transform;

#define _SLI			0x696c735f // '_sli'  Set Linear Interpolation
#define PRCL			0x6c637270 // 'prcl'  Cancle print

/**
 * Handle a Cartesian packet.
 * @return True if the packet was processed, False if it was not  Cartesian packet
 */
unsigned char ProcessCartesianPacket(BowlerPacket * Packet);

void initializeCartesianController();

BYTE setInterpolateXYZ(float x, float y, float z,float ms);

void interpolateZXY();

BYTE setXYZ(float x, float y, float z);

//int getCurrentPosition(float * x, float * y, float * z);

void cartesianAsync();

void cancelPrint();

BOOL onCartesianPost(BowlerPacket *Packet);

//void InitializeCartesianController( BOOL (*asyncCallbackPtr)(BowlerPacket *Packet),
//                                    BOOL (*forwardKinematicsCallbackPtr)(float * currentLinkPositions, Transform * result),
//                                    BOOL (*inverseKinematicsCallbackPtr)(Transform * currentTransform, float * result ),
//                                    BOOL (*setPositionCallbackPtr)(int linkIndex,float degrees,float ms),
//                                    BOOL (*getAllPositionsCallbackPtr)(float * currentLinkPositions)
//                                  );
float getmaxZ();
float getminZ();
int servostock_calcInverse(float x0, float y0, float z0, float *theta1, float *theta2, float *theta3);

int servostock_calcForward(float theta1, float theta2, float theta3, float * x0, float *y0, float * z0);
#ifdef	__cplusplus
}
#endif

#endif	/* CARTESIANCONTROLLER_H */

