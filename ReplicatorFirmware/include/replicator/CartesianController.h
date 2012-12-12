/* 
 * File:   CartesianController.h
 * Author: hephaestus
 *
 * Created on October 10, 2012, 10:58 AM
 */

#ifndef CARTESIANCONTROLLER_H
#define	CARTESIANCONTROLLER_H
#include "Bowler/Bowler_Helper.h"

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

int getCurrentPosition(float * x, float * y, float * z);

void cartesianAsync();

void cancelPrint();

//void InitializeCartesianController( BOOL (*asyncCallbackPtr)(BowlerPacket *Packet),
//                                    BOOL (*forwardKinematicsCallbackPtr)(float * currentLinkPositions, Transform * result),
//                                    BOOL (*inverseKinematicsCallbackPtr)(Transform * currentTransform, float * result ),
//                                    BOOL (*setPositionCallbackPtr)(int linkIndex,float degrees,float ms),
//                                    BOOL (*getAllPositionsCallbackPtr)(float * currentLinkPositions)
//                                  );


#ifdef	__cplusplus
}
#endif

#endif	/* CARTESIANCONTROLLER_H */

