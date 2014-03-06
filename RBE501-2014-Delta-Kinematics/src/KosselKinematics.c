/*
  motion_control.c - high level interface for issuing motion commands
  Part of Grbl

  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2011 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
  
  
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
//#include <Bowler/Debug.h>

typedef struct _DeltaConfig{
	float RodLength;
	float BaseRadius;
	float EndEffectorRadius;
	float MaxZ;
	float MinZ;
}DeltaConfig;

static DeltaConfig defaultConfig ={203.82,//RodLength
                            150,//BaseRadius
                            40.32,//EndEffectorRadius
                            300.0,//MaxZ
                            0.0};//MinZ
float sq(float num) {
    return num*num; 
}
float getRodLength(){
    return defaultConfig.RodLength;
}
float getmaxZ(){
    return defaultConfig.MaxZ;
}
float getminZ(){
    return defaultConfig.MinZ;
}
//TODO hack!
//#define E_AXIS 0
#define N_ARC_CORRECTION 0
#define MM_PER_ARC_SEGMENT 1
//TODO end hack!

int servostock_calcInverse(float X, float Y, float Z, float *Alpha, float *Beta, float *Gamma){
    float L = defaultConfig.RodLength;
    float R = defaultConfig.BaseRadius-defaultConfig.EndEffectorRadius;
    float Lsqr=L*L;
    float maxRad=(R*2/3);
    
//#warning "Z is not used yet"
    if(abs(X)>maxRad || abs(Y)>maxRad || Z<defaultConfig.MinZ||Z>defaultConfig.MaxZ){
        //println_E("Outside of workspace x=");p_fl_E(X);print_E(" y=");p_fl_E(Y);print_E(" z=");p_fl_E(Z);print_E(" Bound radius=");p_fl_E((maxRad));
    	printf("\r\nOutside of workspace x= %g y=%g z=%g Bound = %g",X,Y,Z,maxRad);
        return 1;//This is ourside the reachable work area
    }
    
    float SIN_60 = 0.8660254037844386;
    float COS_60 = 0.5;

// Values are in mm, Alpha, Beta, Gamma starts at 0 at the base platform.
    Alpha[0] = sqrt(Lsqr - (0 - X)*(0 - X)                  - (R - Y)*(R - Y))+Z;
    Beta[0]  = sqrt(Lsqr - (-SIN_60*R - X)*(-SIN_60*R - X)  - (-COS_60*R - Y)*(-COS_60*R - Y))+Z;
    Gamma[0]  = sqrt(Lsqr - (SIN_60*R - X)*(SIN_60*R - X)   - (-COS_60*R - Y)*(-COS_60*R - Y))+Z;

    return 0;//SUCCESS
}

int servostock_calcForward(float Alpha, float Beta, float Gamma, float * X, float *Y, float * Z){

		// modified from https://gist.github.com/kastner/5279172
		//http://www.cutting.lv/fileadmin/user_upload/lindeltakins.c
		//http://blog.machinekit.io/2013/07/linear-delta-kinematics.html

        float DELTA_DIAGONAL_ROD = defaultConfig.RodLength;

        // Horizontal offset from middle of printer to smooth rod center.
        float DELTA_SMOOTH_ROD_OFFSET = defaultConfig.BaseRadius; // mm

        // Horizontal offset of the universal joints on the end effector.
        // DELTA_EFFECTOR_OFFSET = 32.0 // mm
        //float DELTA_EFFECTOR_OFFSET = 32.0 // mm

        // Horizontal offset of the universal joints on the carriages.
        // DELTA_CARRIAGE_OFFSET = 26.0 // mm
       float  DELTA_CARRIAGE_OFFSET = defaultConfig.EndEffectorRadius; // mm

        // In order to correct low-center, DELTA_RADIUS must be increased.
        // In order to correct high-center, DELTA_RADIUS must be decreased.
        // For convex/concave -- -20->-30 makes the center go DOWN
        // DELTA_FUDGE -27.4 // 152.4 total radius
        float DELTA_FUDGE =0;

        // Effective horizontal distance bridged by diagonal push rods.
        float DELTA_RADIUS = (DELTA_SMOOTH_ROD_OFFSET-DELTA_CARRIAGE_OFFSET-DELTA_FUDGE);

        float SIN_60 = 0.8660254037844386;
        float COS_60 = 0.5;

        //float DELTA_TOWER1_X = 0.0; // back middle tower
        float DELTA_TOWER1_Y = DELTA_RADIUS;

        float DELTA_TOWER2_X = -SIN_60*DELTA_RADIUS; // front left tower
        float DELTA_TOWER2_Y = -COS_60*DELTA_RADIUS;

        float DELTA_TOWER3_X = SIN_60*DELTA_RADIUS; // front right tower
        float DELTA_TOWER3_Y = -COS_60*DELTA_RADIUS;

        float y1 = DELTA_TOWER1_Y;
        float z1 = Alpha;

        float x2 = DELTA_TOWER2_X;
        float y2 = DELTA_TOWER2_Y;
        float z2 = Beta;

        float x3 = DELTA_TOWER3_X;
        float y3 = DELTA_TOWER3_Y;
        float z3 = Gamma;

        float re = DELTA_DIAGONAL_ROD;

        float dnm = (y2-y1)*x3-(y3-y1)*x2;

        float w1 = y1*y1 + z1*z1;
        float w2 = x2*x2 + y2*y2 + z2*z2;
        float w3 = x3*x3 + y3*y3 + z3*z3;

        // x = (a1*z + b1)/dnm
        float a1 = (z2-z1)*(y3-y1)-(z3-z1)*(y2-y1);
        float b1 = -((w2-w1)*(y3-y1)-(w3-w1)*(y2-y1))/2.0;

        // y = (a2*z + b2)/dnm;
        float a2 = -(z2-z1)*x3+(z3-z1)*x2;
        float b2 = ((w2-w1)*x3 - (w3-w1)*x2)/2.0;

        // a*z^2 + b*z + c = 0
        float a = a1*a1 + a2*a2 + dnm*dnm;
        float b = 2*(a1*b1 + a2*(b2-y1*dnm) - z1*dnm*dnm);
        float c = (b2-y1*dnm)*(b2-y1*dnm) + b1*b1 + dnm*dnm*(z1*z1 - re*re);

        // discriminant
        float d = b*b - 4.0*a*c;
        if (d < 0)
            return -1; // non-existing point

        Z[0] = -0.5*(b+sqrt(d))/a;
        X[0] = (a1*Z[0] + b1)/dnm;
        Y[0] = (a2*Z[0] + b2)/dnm;

          return 0;//success
}
