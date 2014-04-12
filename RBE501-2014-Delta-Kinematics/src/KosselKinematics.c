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
                            175,//BaseRadius
                            40.32,//EndEffectorRadius
                            300.0,//MaxZ
                            0.0};//MinZ

//Prototypes
int formJacobian (float A, float B, float C, float Jex[3][3]);
int mtxMlt_ThreeByThree (float A[3][3], float B[3][3], float result[3][3]);
int mtxMlt_ThreeByOne (float A[3][3], float B[3], float result[3]);
int mtxTrns_ThreebyThree (float A[3][3], float result[3][3]);
int mtxInv_ThreebyThree(float A[3][3], float result[3][3]);


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
    float maxRad=sqrt((X*X)+(Y*Y));
    
//#warning "Z is not used yet"
    if(maxRad>(L/2)*.97 || Z<defaultConfig.MinZ||Z>defaultConfig.MaxZ){
        //println_E("Outside of workspace x=");p_fl_E(X);print_E(" y=");p_fl_E(Y);print_E(" z=");p_fl_E(Z);print_E(" Bound radius=");p_fl_E((maxRad));
    	printf("\r\nOutside of workspace x= %g y=%g z=%g Bound = %g",X,Y,Z,maxRad);
        return 1;//This is outside the reachable work area
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


/* Function: Inverse Velocity
 * Inputs: current task position (X, Y, Z) and desired task velocities (Xd, Yd, Zd)
 * Outputs: resulting joint velocities (Ad, Bd, Cd)
 */

int servostock_velInverse(float X, float Y, float Z, float Xd, float Yd, float Zd,
		float * Ad, float * Bd, float * Cd){

	// Calculate Current Joint Positions from given Tool Positions
	float A = 0;
	float B = 0;
	float C = 0;
	if (servostock_calcInverse(X, Y, Z, &A, &B, &C))
		return 1;


	// Form Jacobian
	float J[3][3] = {{0}};
	if (formJacobian(A, B, C, J))
		return 1;


	// Jacobian Pseudo-inverse
	// Jinv = J' * inv(J * J')
	float Jtrns[3][3] = {{0}};
	if (mtxTrns_ThreebyThree(J, Jtrns))
		return 1;

	float temp1[3][3] = {{0}};
	if (mtxMlt_ThreeByThree(J, Jtrns, temp1))
		return 1;

	float temp2[3][3] = {{0}};
	if (mtxInv_ThreebyThree(temp1, temp2))
		return 1;

	float Jinv[3][3] = {{0}};
	if (mtxMlt_ThreeByThree(Jtrns, temp2, Jinv))
		return 1;

	//TODO: investigate incorrect results
	// Inverse calculation: jointVel = Jinv * taskVel
	float jointVel[3] = {0};
	float taskVel[3] = {Xd, Yd, Zd};
	if (mtxMlt_ThreeByOne(Jinv, taskVel, jointVel))
		return 1;

	// Return Values
	Ad[0] = jointVel[0];
	Bd[0] = jointVel[1];
	Cd[0] = jointVel[2];

	return 0; //success
}


/* Function: Forward Velocity
 * Inputs: current joint position (A, B, C) and desired joint velocities (Ad, Bd, Cd)
 * Outputs: resulting task velocities (Xd, Yd, Zd)
 */

int servostock_velForward(float A, float B, float C, float Ad, float Bd, float Cd,
		float * Xd, float * Yd, float * Zd)
{

	// Form Jacobian
	float J[3][3] = {{0}};
	if (formJacobian(A, B, C, J))
		return 1;

	// Forward Calculation: taskVel = J * joinVel
	float taskVel[3] = {0};
	float jointVel[3] = {Ad, Bd, Cd};
	mtxMlt_ThreeByOne(J, jointVel, taskVel);

	// Return Values
	Xd[0] = taskVel[0];
	Yd[0] = taskVel[1];
	Zd[0] = taskVel[2];

	return 0;
}

int formJacobian (float A, float B, float C, float Jex[3][3])
{
	//Output from MatlabScript.md 'Jsym'

	float t2 = B*2.0202E2;
	float t10 = C*2.0202E2;
	float t3 = t2-t10;
	float t5 = A*2.3326576E2;
	float t6 = B*1.1663288E2;
	float t7 = C*1.1663288E2;
	float t4 = -t5+t6+t7;
	float t8 = B*B;
	float t9 = C*C;
	float t14 = A*A;
	float t15 = t14*1.1663288E2;
	float t16 = t8*5.831644E1;
	float t17 = t9*5.831644E1;
	float t18 = -t15+t16+t17+6.34661421608432E6;
	float t19 = t8*1.0101E2;
	float t20 = t9*1.0101E2;
	float t21 = t19-t20;
	float t26 = A*4.441408506283233E9;
	float t27 = t4*t18*2.0;
	float t28 = t3*t21*2.0;
	float t11 = t26+t27+t28;
	float t12 = t3*t3;
	float t13 = t4*t4;
	float t22 = t18*t18;
	float t23 = t14*2.220704253141616E9;
	float t24 = t21*t21;
	float t25 = t22+t23+t24-9.225381162920857E13;
	float t29 = t12*4.0;
	float t30 = t13*4.0;
	float t31 = t29+t30+8.882817012566465E9;
	float t32 = A*t4*4.6653152E2;
	float t33 = t8*2.72064573941888E4;
	float t34 = t9*2.72064573941888E4;
	float t35 = t12+t13+2.220704253141616E9;
	float t36 = t11*t11;
	float t39 = t25*t31;
	float t37 = t36-t39;
	float t38 = 1.0/t35;
	float t40 = sqrt(t37);
	float t41 = t26+t27+t28-t40;
	float t42 = 1.0/sqrt(t37);
	float t43 = B*t3*4.0404E2;
	float t44 = B*t4*2.3326576E2;
	float t45 = t8*5.44153090970944E4;
	float t46 = 1.0/(t35*t35);
	float t47 = t38*t41*2.143477894055261E-3;
	float t48 = A*2.176516591535104E5;
	float t49 = C*t3*4.0404E2;
	float t50 = t14*2.72064573941888E4;
	float t51 = t8*2.72088517029056E4;
	float t52 = t9*5.44153090970944E4;
	float t53 = A*5.44129147883776E4;
	float t54 = B*2.176516591535104E5;
	float t55 = C*2.176516591535104E5;
	float t80 = A*4.353033183070208E5;
	float t56 = t54+t55-t80;
	float t57 = t14*5.44129147883776E4;
	float t83 = A*t18*4.6653152E2;
	float t58 = t26-t83;
	float t59 = t31*t58;
	float t60 = B*5.44129147883776E4;
	float t61 = C*5.44129147883776E4;
	float t86 = A*1.088258295767552E5;
	float t62 = t60+t61-t86;
	float t63 = C*2.176708136232448E5;
	float t89 = B*4.353224727767552E5;
	float t64 = t48+t63-t89;
	float t65 = t25*t64;
	float t66 = B*t21*4.0404E2;
	float t67 = B*t18*2.3326576E2;
	float t68 = t66+t67;
	float t69 = C*5.44177034058112E4;
	float t92 = B*1.088306181941888E5;
	float t70 = t53+t69-t92;
	float t71 = t38*t41*1.237501237501237E-3;
	float t72 = C*t4*2.3326576E2;
	float t73 = B*2.176708136232448E5;
	float t95 = C*4.353224727767552E5;
	float t74 = t48+t73-t95;
	float t75 = C*t18*2.3326576E2;
	float t96 = C*t21*4.0404E2;
	float t76 = t75-t96;
	float t77 = t31*t76;
	float t78 = B*5.44177034058112E4;
	float t99 = C*1.088306181941888E5;
	float t79 = t53+t78-t99;
	float t81 = t32+t33+t34-t57-1.480512929199806E9;
	float t82 = t11*t81*2.0;
	float t84 = t59+t82-t25*t56;
	float t85 = t32+t33+t34-t57-t42*t84*(1.0/2.0)-1.480512929199806E9;
	float t91 = t9*2.72088517029056E4;
	float t87 = t43+t44+t45-t50-t91+1.480447788541713E9;
	float t88 = t11*t87*2.0;
	float t90 = t65+t88-t31*t68;
	float t93 = t49+t50+t51-t52-t72-1.480447788541713E9;
	float t94 = t11*t93*2.0;
	float t97 = t77+t94-t25*t74;
	float t98 = t42*t97*(1.0/2.0);

	Jex[0][0] = t3*t38*(t32+t33+t34-t57-t42*(t59-t25*t56+t11*(t14*(-5.44129147883776E4)+t32+t33+t34-1.480512929199806E9)*2.0)*(1.0/2.0)-1.480512929199806E9)*(-1.061022618579973E-5)+t3*t41*t46*t62*1.061022618579973E-5;
	Jex[0][1] = B*(-4.286955788110522E-3)+t47+t3*t38*(t9*(-2.72088517029056E4)-t14*2.72064573941888E4+t43+t44+t45-t42*(t65-t31*t68+t11*(t9*(-2.72088517029056E4)-t14*2.72064573941888E4+t43+t44+t45+1.480447788541713E9)*2.0)*(1.0/2.0)+1.480447788541713E9)*1.061022618579973E-5+t3*t41*t46*t70*1.061022618579973E-5;
	Jex[0][2] = C*4.286955788110522E-3-t47+t3*t38*(-t49-t50-t51+t52+t72+t42*(t77-t25*t74+t11*(t49+t50+t51-t52-C*t4*2.3326576E2-1.480447788541713E9)*2.0)*(1.0/2.0)+1.480447788541713E9)*1.061022618579973E-5+t3*t41*t46*t79*1.061022618579973E-5;
	Jex[1][0] = A*4.950004950004949E-3-t38*t41*2.475002475002475E-3-t4*t38*t85*1.061022618579973E-5+t4*t41*t46*t62*1.061022618579973E-5;
	Jex[1][1] = B*(-2.475002475002475E-3)+t71+t4*t38*(t9*(-2.72088517029056E4)+t43+t44+t45-t50-t42*t90*(1.0/2.0)+1.480447788541713E9)*1.061022618579973E-5+t4*t41*t46*t70*1.061022618579973E-5;
	Jex[1][2] = C*(-2.475002475002475E-3)+t71+t4*t38*(-t49-t50-t51+t52+t72+t98+1.480447788541713E9)*1.061022618579973E-5+t4*t41*t46*t79*1.061022618579973E-5;
	Jex[2][0] = t38*t85*(-1.0/2.0)+t41*t46*t62*(1.0/2.0);
	Jex[2][1] = t38*(t43+t44+t45-t50-t91-t42*t90*(1.0/2.0)+1.480447788541713E9)*(1.0/2.0)+t41*t46*t70*(1.0/2.0);
	Jex[2][2] = t38*(-t49-t50-t51+t52+t72+t98+1.480447788541713E9)*(1.0/2.0)+t41*t46*t79*(1.0/2.0);

	return 0; //success
}

int mtxMlt_ThreeByThree (float A[3][3], float B[3][3], float result[3][3])
{

	result[0][0] = (A[0][0] * B[0][0]) + (A[0][1] * B[1][0]) + (A[0][2] * B[3][0]);
	result[0][1] = (A[0][0] * B[0][1]) + (A[0][1] * B[1][1]) + (A[0][2] * B[3][1]);
	result[0][2] = (A[0][0] * B[0][2]) + (A[0][1] * B[1][2]) + (A[0][2] * B[3][2]);

	result[1][0] = (A[1][0] * B[0][0]) + (A[1][1] * B[1][0]) + (A[1][2] * B[3][0]);
	result[1][1] = (A[1][0] * B[0][1]) + (A[1][1] * B[1][1]) + (A[1][2] * B[3][1]);
	result[1][2] = (A[1][0] * B[0][2]) + (A[1][1] * B[1][2]) + (A[1][2] * B[3][2]);

	result[2][0] = (A[2][0] * B[0][0]) + (A[2][1] * B[1][0]) + (A[3][2] * B[3][0]);
	result[2][1] = (A[2][0] * B[0][1]) + (A[2][1] * B[1][1]) + (A[3][2] * B[3][1]);
	result[2][2] = (A[2][0] * B[0][2]) + (A[2][1] * B[1][2]) + (A[3][2] * B[3][2]);

	return 0; //success
}

int mtxMlt_ThreeByOne (float A[3][3], float B[3], float result[3])
{

	result[0] = (A[0][0] * B[0]) + (A[0][1] * B[1]) + (A[0][2] * B[2]);
	result[1] = (A[1][0] * B[0]) + (A[1][1] * B[1]) + (A[1][2] * B[2]);
	result[2] = (A[2][0] * B[0]) + (A[2][1] * B[1]) + (A[2][2] * B[2]);

	return 0; //success
}

int mtxTrns_ThreebyThree (float A[3][3], float result[3][3])
{

	result[0][0] = A[0][0];
	result[0][1] = A[1][0];
	result[0][2] = A[2][0];

	result[1][0] = A[0][1];
	result[1][1] = A[1][1];
	result[1][2] = A[2][1];

	result[2][0] = A[0][2];
	result[2][1] = A[1][2];
	result[2][2] = A[2][2];

	return 0; //success
}

int mtxInv_ThreebyThree(float A[3][3], float result[3][3])
{
	//TODO matrix inverse

	// Determinant
	float det1 = A[0][0] * ((A[1][1] * A[2][2]) - (A[2][1] * A[1][2]));
	float det2 = A[0][1] * ((A[1][0] * A[2][2]) - (A[2][0] * A[1][2]));
	float det3 = A[0][2] * ((A[1][0] * A[2][1]) - (A[2][0] * A[1][1]));
	float det = det1 - det2 + det3;

	// Transpose
	float trans[3][3] = {{0}};
	if (mtxTrns_ThreebyThree(A, trans))
		return 1;

	// Minors
	float m00 = (trans[1][1] * trans[2][2]) - (trans[2][1] * trans[1][2]);
	float m01 = (trans[1][0] * trans[2][2]) - (trans[2][0] * trans[1][2]);
	float m02 = (trans[1][0] * trans[2][1]) - (trans[2][0] * trans[1][1]);

	float m10 = (trans[0][1] * trans[2][2]) - (trans[2][1] * trans[0][2]);
	float m11 = (trans[0][0] * trans[2][2]) - (trans[2][0] * trans[0][2]);
	float m12 = (trans[0][0] * trans[2][1]) - (trans[2][0] * trans[0][1]);

	float m20 = (trans[0][1] * trans[1][2]) - (trans[1][1] * trans[0][2]);
	float m21 = (trans[0][0] * trans[1][2]) - (trans[1][0] * trans[0][2]);
	float m22 = (trans[0][0] * trans[1][1]) - (trans[1][0] * trans[0][1]);

	// Adjugate
	float adj[3][3] = {{m00, -m01, m02}, {-m10, m11, -m12}, {m20, -m21, m22}};

	// Inverse Solution
	result[0][0] = adj[0][0] / det;
	result[0][1] = adj[0][1] / det;
	result[0][2] = adj[0][2] / det;
	result[1][0] = adj[1][0] / det;
	result[1][1] = adj[1][1] / det;
	result[1][2] = adj[1][2] / det;
	result[2][0] = adj[2][0] / det;
	result[2][1] = adj[2][1] / det;
	result[2][2] = adj[2][2] / det;

	return 0; //success
}
