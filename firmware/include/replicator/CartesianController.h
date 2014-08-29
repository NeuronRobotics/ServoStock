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

    typedef boolean forwardKinematics(float Alpha, float Beta, float Gama, float * x0, float *y0, float * z0);
typedef boolean inverseKinematics(float x0, float y0, float z0, float *Alpha, float *Beta, float *Gama);

/* Function: Inverse Velocity
 * Inputs: current task position (X, Y, Z) and desired task velocities (Xd, Yd, Zd)
 * Outputs: resulting joint velocities (Ad, Bd, Cd)
 */
typedef int velInverse(float X, float Y, float Z, float Xd, float Yd, float Zd, float * Ad, float * Bd, float * Cd);
/* Function: Forward Velocity
 * Inputs: current joint position (A, B, C) and desired joint velocities (Ad, Bd, Cd)
 * Outputs: resulting task velocities (Xd, Yd, Zd)
 */
typedef int velForward(float A, float B, float C, float Ad, float Bd, float Cd, float * Xd, float * Yd, float * Zd);


typedef struct _IndexScale {
    int index;
    float scale;
    char name[10];
} IndexScale;

typedef struct _HardwareMap {
    IndexScale Alpha;
    IndexScale Beta;
    IndexScale Gama;

    struct {
        IndexScale Heater0;
        IndexScale Extruder0;
    };

    struct {
        IndexScale Heater1;
        IndexScale Extruder1;
    };

    struct {
        IndexScale Heater2;
        IndexScale Extruder2;
    };
    forwardKinematics * fK_callback;
    inverseKinematics * iK_callback;
    velInverse * iVel_callback;
    velForward * fVel_callback;
    unsigned char useStateBasedVelocity;
} HardwareMap;


#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _Transform {
        float x;
        float y;
        float z;
        float rotation[3][3];
    } Transform;

#define _SLI			0x696c735f // '_sli'  Set Linear Interpolation
#define PRCL			0x6c637270 // 'prcl'  Cancle print

    /**
     * Handle a Cartesian packet.
     * @return True if the packet was processed, False if it was not  Cartesian packet
     */
    unsigned char ProcessCartesianPacket(BowlerPacket * Packet);

    void initializeCartesianController();

    int linkToHWIndex(int index);

    uint8_t setInterpolateXYZ(float x, float y, float z, float ms);

    void interpolateZXY();

    uint8_t setXYZ(float x, float y, float z, float ms);

    float getLinkAngle(int index);
    float getLinkAngleNoScale(int index);

    float setLinkAngle(int index, float value, float ms);

    //int getCurrentPosition(float * x, float * y, float * z);

    void cartesianAsync();

    void cancelPrint();

    boolean onCartesianPost(BowlerPacket *Packet);
    boolean onClearPrinter(BowlerPacket *Packet);
    void printCartesianData();

    //void InitializeCartesianController( boolean (*asyncCallbackPtr)(BowlerPacket *Packet),
    //                                    boolean (*forwardKinematicsCallbackPtr)(float * currentLinkPositions, Transform * result),
    //                                    boolean (*inverseKinematicsCallbackPtr)(Transform * currentTransform, float * result ),
    //                                    boolean (*setPositionCallbackPtr)(int linkIndex,float degrees,float ms),
    //                                    boolean (*getAllPositionsCallbackPtr)(float * currentLinkPositions)
    //                                  );
    float getmaxZ();
    float getRodLength();
    float getminZ();
    int servostock_calcInverse(float x0, float y0, float z0, float *theta1, float *theta2, float *theta3);

    int servostock_calcForward(float theta1, float theta2, float theta3, float * x0, float *y0, float * z0);

    /* Function: Inverse Velocity
     * Inputs: current task position (X, Y, Z) and desired task velocities (Xd, Yd, Zd)
     * Outputs: resulting joint velocities (Ad, Bd, Cd)
     */
    int servostock_velInverse(float X, float Y, float Z, float Xd, float Yd, float Zd,
            float * Ad, float * Bd, float * Cd);
    /* Function: Forward Velocity
     * Inputs: current joint position (A, B, C) and desired joint velocities (Ad, Bd, Cd)
     * Outputs: resulting task velocities (Xd, Yd, Zd)
     */
    int servostock_velForward(float A, float B, float C, float Ad, float Bd, float Cd,
            float * Xd, float * Yd, float * Zd);

    int frog_calcForward(float Alpha, float Beta, float Gamma, float * X, float *Y, float * Z);
    int frog_calcInverse(float X, float Y, float Z, float *Alpha, float *Beta, float *Gamma);

boolean onConfigurationGet(BowlerPacket *Packet);
boolean onRunKinematicsSet(BowlerPacket *Packet);
boolean onCartesianPacket(BowlerPacket *Packet);
boolean setDesiredTaskSpaceTransform(BowlerPacket *Packet);
boolean getCurrentTaskSpaceTransform(BowlerPacket *Packet);
boolean setDesiredJointSpaceVector(BowlerPacket *Packet);
boolean setDesiredJointAxisValue(BowlerPacket *Packet);

HardwareMap * getHardwareMap();

float getmmPositionResolution();
float getmmaximumMMperSec() ;
float getKP();
float getKI();
float getKD();

float getVKP();
float getVKD();
void setmmPositionResolution(float value);
void setKP(float value);
void setKI(float value);
void setKD(float value);
void setVKP(float value);

void setVKD(float value);

char * getName(int index);

#ifdef	__cplusplus
}
#endif

#endif	/* CARTESIANCONTROLLER_H */

