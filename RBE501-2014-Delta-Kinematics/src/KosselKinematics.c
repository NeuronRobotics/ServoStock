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

int servostock_calcInverse(float X, float Y, float Z, float *Alpha, float *Beta, float *Gama){
    float L = defaultConfig.RodLength;
    float R = defaultConfig.BaseRadius-defaultConfig.EndEffectorRadius;
    float Lsqr=L*L;
    float root3=sqrt(3)/2;
    float maxRad=(R*2/3);
//#warning "Z is not used yet"
    if(abs(X)>maxRad || abs(Y)>maxRad || Z<defaultConfig.MinZ||Z>defaultConfig.MaxZ){
        //println_E("Outside of workspace x=");p_fl_E(X);print_E(" y=");p_fl_E(Y);print_E(" z=");p_fl_E(Z);print_E(" Bound radius=");p_fl_E((maxRad));
    	printf("\r\nOutside of workspace x= %g y=%g z=%g Bound = %g",X,Y,Z,maxRad);
        return 1;//This is ourside the reachable work area
    }
    Alpha[0] = sqrt(Lsqr - (X - 0)*(X - 0)      - (Y - R)*(Y - R))+Z;
    Beta[0]  = sqrt(Lsqr - (X - R/2)*(X - R/2)  - (Y + R*root3)*(Y + R*root3))+Z;
    Gama[0]  = sqrt(Lsqr - (X + R/2)*(X + R/2)  - (Y + R*root3)*(Y + R*root3))+Z;

    return 0;//SUCCESS
}

int servostock_calcForward(float Alpha, float Beta, float Gama, float * X, float *Y, float * Z){
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

#define AD (Alpha)
#define BD (Beta)
#define CD (Gama)
#define Dx (*X)
#define Dy (*Y)
#define Dz (*Z)

        /* Ax = rigid arms length */
        /* Cz = moving tool platform radius */
#define Ax (DELTA_DIAGONAL_ROD)
#define Cx (DELTA_RADIUS*sqrt(3)/2)
#define Bx (Cx*2)
#define Cy (DELTA_RADIUS + (DELTA_RADIUS/2))
#define Cz (DELTA_RADIUS)

        //http://www.cutting.lv/fileadmin/user_upload/lindeltakins.c
        //http://blog.machinekit.io/2013/07/linear-delta-kinematics.html
  Dx=(-sq(AD)+2*(Dz)*(AD)+sq(BD)-2*(Bx)*(Cz)*0.8660254-2*(BD)*(Dz)+sq(Bx))/(2*((Bx)-2*(Cz)*0.8660254));

  Dy=((sq(Cz)*sq(0.8660254))+2*(Cz)*0.8660254*(Dx)-2*(Cz)*0.8660254*(Bx)-2*(Dx)*(Bx)+sq(Bx)+sq(BD)-2*(Dz)*(BD)+2*(Cx)*(Dx)-sq(Cx)-sq(Cy)+2*(Cy)*(Cz)-sq(Cz)-sq(CD)+2*(Dz)*(CD)+sq(Cz)*sq(0.5))/(2*((Cz)*0.5+(Cz)-(Cy)));

  Dz=AD-sqrt(sq(Ax)-sq((Dx)-0.8660254*(Cz))-sq((Dy)-0.5*(Cz)));

  return 0;

#undef AD
#undef BD
#undef CD
#undef Dx
#undef Dy
#undef Dz
}
