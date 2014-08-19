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

#include "main.h"
//#include <complex.h>

DeltaConfig defaultConfig ={203.82,//RodLength
                            140,//BaseRadius
                            25,//EndEffectorRadius
                            150.0,//MaxZ
                            -10};//MinZ

//Prototypes
int formJacobian (float A, float B, float C, float Jex[3][3], float baseRad, float endEfRad, float rodLen);
int formInvJacobian (float A, float B, float C, float Jex[3][3], float Jinv[3][3]);
int mtxMlt_ThreeByOne (float A[3][3], float B[3], float result[3]);

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
    if((maxRad>(L-R))|| (Z<defaultConfig.MinZ)||(Z>(defaultConfig.MaxZ+L))){
        println_E("Outside of workspace x=");p_fl_E(X);print_E(" y=");p_fl_E(Y);print_E(" z=");p_fl_E(Z);print_E(" Bound radius=");p_fl_E((maxRad));
    	//printf("\r\nOutside of workspace x= %g y=%g z=%g Bound = %g",X,Y,Z,maxRad);
        return 1;//This is ourside the reachable work area
    }

    float SIN_60 = 0.8660254037844386;
    float COS_60 = 0.5;

// Values are in mm, Alpha, Beta, Gamma starts at 0 at the base platform.
    Alpha[0] = sqrt(Lsqr - (0 - X)*(0 - X)                  - (R - Y)*(R - Y))+Z;
    Beta[0]  = sqrt(Lsqr - (-SIN_60*R - X)*(-SIN_60*R - X)  - (-COS_60*R - Y)*(-COS_60*R - Y))+Z;
    Gamma[0]  = sqrt(Lsqr - (SIN_60*R - X)*(SIN_60*R - X)   - (-COS_60*R - Y)*(-COS_60*R - Y))+Z;

    if( abs(Alpha[0]-Beta[0])>L||
            abs(Alpha[0]-Gamma[0])>L||
            abs(Beta[0]-Alpha[0])>L||
            abs(Beta[0]-Gamma[0])>L||
            abs(Gamma[0]-Alpha[0])>L||
            abs(Gamma[0]-Beta[0])>L){
        println_E("Outside of workspace x=");p_fl_E(X);print_E(" y=");p_fl_E(Y);print_E(" z=");p_fl_E(Z);print_E(" Bound radius=");p_fl_E((maxRad));
        println_E("Alpha=");p_fl_E(Alpha[0]);
        print_E(" Beta=");p_fl_E(Beta[0]);
        print_E(" Gama=");p_fl_E(Gamma[0]);

        return 1;//This is ourside the reachable work area
    }

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


	// Form Inverse Jacobian
	float J[3][3] = {{0}};
	if (formJacobian(A, B, C, J, defaultConfig.BaseRadius, defaultConfig.EndEffectorRadius, defaultConfig.RodLength))
		return 2;
	float Jinv[3][3] = {{0}};
	if (formInvJacobian(A, B, C, J, Jinv))
		return 3;

	// Inverse calculation: jointVel = Jinv * taskVel
	float jointVel[3] = {0};
	float taskVel[3] = {Xd, Yd, Zd};
	if (mtxMlt_ThreeByOne(Jinv, taskVel, jointVel))
		return 4;

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
	if (formJacobian(A, B, C, J, defaultConfig.BaseRadius, defaultConfig.EndEffectorRadius, defaultConfig.RodLength))
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


/* Function: Form Jacobian Matrix
 * Inputs: current joint position (A, B, C) and robot configuration
 * Outputs: resulting 3x3 Jacobian matrix (Jex)
 */
int formJacobian (float A, float B, float C, float Jex[3][3], float baseRad, float endEfRad, float rodLen)
{
	//Output from MatlabScript.md 'J'

	float t2 = baseRad*(3.0/2.0);
	float t3 = endEfRad*(3.0/2.0);
	float t4 = t2-t3;
	float t5 = A-B;
	float t6 = t4*t5;
	float t7 = A-C;
	float t28 = t4*t7;
	float t8 = t6-t28;
	float t9 = baseRad*(4.33E2/5.0E2);
	float t10 = endEfRad*(4.33E2/5.0E2);
	float t11 = t9-t10;
	float t30 = t5*t11;
	float t31 = t7*t11;
	float t12 = t30+t31;
	float t16 = baseRad*(1.0/2.0);
	float t17 = endEfRad*(1.0/2.0);
	float t13 = t16-t17;
	float t14 = t11*t11;
	float t15 = baseRad-endEfRad;
	float t18 = t13*t13;
	float t19 = A*A;
	float t20 = t15*t15;
	float t22 = B*B;
	float t23 = t14+t18-t19-t20+t22;
	float t24 = C*C;
	float t25 = t14+t18-t19-t20+t24;
	float t33 = t11*t23*(1.0/2.0);
	float t34 = t11*t25*(1.0/2.0);
	float t35 = t4*t11*t15*2.0;
	float t21 = t33+t34+t35;
	float t36 = t4*t23*(1.0/2.0);
	float t37 = t4*t25*(1.0/2.0);
	float t26 = t36-t37;
	float t27 = t4*t4;
	float t29 = t8*t8;
	float t32 = t12*t12;
	float t39 = t12*t21*2.0;
	float t40 = t8*t26*2.0;
	float t41 = A*t14*t27*8.0;
	float t38 = t39+t40-t41;
	float t42 = t29*4.0;
	float t43 = t32*4.0;
	float t44 = t14*t27*1.6E1;
	float t45 = t42+t43+t44;
	float t46 = baseRad*(4.33E2/2.5E2);
	float t47 = endEfRad*(4.33E2/2.5E2);
	float t48 = t46-t47;
	float t49 = t21*t21;
	float t50 = t26*t26;
	float t51 = rodLen*rodLen;
	float t52 = t19-t51;
	float t53 = t14*t27*t52*4.0;
	float t54 = t49+t50+t53;
	float t55 = t14*t27*8.0;
	float t56 = A*t11*t12*4.0;
	float t57 = t14*t27*4.0;
	float t58 = t29+t32+t57;
	float t59 = t38*t38;
	float t64 = t45*t54;
	float t60 = t59-t64;
	float t61 = 1.0/t4;
	float t62 = 1.0/t11;
	float t63 = 1.0/t58;
	float t65 = 1.0/sqrt(t60);
	float t66 = t11*t21*2.0;
	float t67 = t4*t26*2.0;
	float t68 = sqrt(t60);
	float t69 = t39+t40-t41+t68;
	float t70 = 1.0/(t58*t58);
	float t71 = t4*t8*8.0;
	float t72 = t11*t12*8.0;
	float t73 = C*t4*t8*2.0;
	float t74 = t4*t63*t69*(1.0/2.0);
	float t75 = t4*t8*2.0;
	float t76 = t11*t12*2.0;
	float t84 = t21*t48*2.0;
	float t77 = t55+t56-t84;
	float t78 = t38*t77*2.0;
	float t108 = A*t11*t21*4.0;
	float t79 = t41-t108;
	float t80 = t45*t79;
	float t81 = t12*t48*t54*8.0;
	float t82 = t78+t80+t81;
	float t83 = t65*t82*(1.0/2.0);
	float t85 = t71+t72;
	float t86 = B*t4*t26*2.0;
	float t87 = B*t11*t21*2.0;
	float t88 = t86+t87;
	float t89 = t45*t88;
	float t94 = B*t4*t8*2.0;
	float t95 = B*t11*t12*2.0;
	float t90 = t66+t67-t94-t95;
	float t91 = t38*t90*2.0;
	float t110 = t54*t85;
	float t92 = t89+t91-t110;
	float t93 = t65*t92*(1.0/2.0);
	float t96 = t75+t76;
	float t97 = t71-t72;
	float t98 = t54*t97;
	float t99 = C*t4*t26*2.0;
	float t112 = C*t11*t21*2.0;
	float t100 = t99-t112;
	float t105 = C*t11*t12*2.0;
	float t101 = t66-t67+t73-t105;
	float t102 = t38*t101*2.0;
	float t113 = t45*t100;
	float t103 = t98+t102-t113;
	float t104 = t65*t103*(1.0/2.0);
	float t106 = t11*t63*t69*(1.0/2.0);
	float t107 = t75-t76;
	float t109 = t55+t56+t83-t84;
	float t111 = t66+t67+t93-t94-t95;
	float t114 = t66-t67+t73+t104-t105;

	Jex[0][0] = t61*t62*(t8*t63*(t55+t56+t83-t21*t48*2.0)*(1.0/2.0)+t8*t12*t48*t69*t70)*(-1.0/2.0);
	Jex[0][1] = t61*t62*(t74+B*t4+t8*t63*(t66+t67+t93-B*t4*t8*2.0-B*t11*t12*2.0)*(1.0/2.0)-t8*t69*t70*t96*(1.0/2.0))*(-1.0/2.0);
	Jex[0][2] = t61*t62*(t74+C*t4-t8*t63*(t66-t67+t73+t104-C*t11*t12*2.0)*(1.0/2.0)-t8*t69*t70*t107*(1.0/2.0))*(1.0/2.0);
	Jex[1][0] = t61*t62*(A*t11*2.0+t48*t63*t69*(1.0/2.0)-t12*t63*t109*(1.0/2.0)-t32*t48*t69*t70)*(1.0/2.0);
	Jex[1][1] = t61*t62*(t106+B*t11+t12*t63*t111*(1.0/2.0)-t12*t69*t70*t96*(1.0/2.0))*(-1.0/2.0);
	Jex[1][2] = t61*t62*(t106+C*t11+t12*t63*t114*(1.0/2.0)+t12*t69*t70*t107*(1.0/2.0))*(-1.0/2.0);
	Jex[2][0] = t63*t109*(1.0/2.0)+t12*t48*t69*t70;
	Jex[2][1] = t63*t111*(1.0/2.0)-t69*t70*t96*(1.0/2.0);
	Jex[2][2] = t63*t114*(1.0/2.0)+t69*t70*t107*(1.0/2.0);

	return 0; //success
}



/* Function: Form Inverse Jacobian Matrix
 * Inputs: current joint position (A, B, C) and 3x3 Jacobian matrix (Jex)
 * Outputs: resulting 3x3 inverse Jacobian matrix (Jinv)
 */
int formInvJacobian (float A, float B, float C, float Jex[3][3], float Jinv[3][3])
{
    float crealf();
	_Complex a11 = Jex[0][0];
	_Complex a12 = Jex[0][1];
	_Complex a13 = Jex[0][2];
	_Complex a21 = Jex[1][0];
	_Complex a22 = Jex[1][1];
	_Complex a23 = Jex[1][2];
	_Complex a31 = Jex[2][0];
	_Complex a32 = Jex[2][1];
	_Complex a33 = Jex[2][2];

	float t2 = crealf(a11);
	float t3 = crealf(a22);
	float t4 = crealf(a12);
	float t5 = crealf(a21);
	float t6 = crealf(a23);
	float t7 = crealf(a13);
	float t8 = crealf(a33);
	float t9 = crealf(a31);
	float t10 = crealf(a32);
	float t11 = a11*a22*a33*t2*t3*t8;
	float t12 = a11*a22*a33*t4*t6*t9;
	float t13 = a11*a22*a33*t5*t7*t10;
	float t14 = a11*a23*a32*t2*t6*t10;
	float t15 = a11*a23*a32*t4*t5*t8;
	float t16 = a11*a23*a32*t3*t7*t9;
	float t17 = a12*a21*a33*t2*t6*t10;
	float t18 = a12*a21*a33*t4*t5*t8;
	float t19 = a12*a21*a33*t3*t7*t9;
	float t20 = a12*a23*a31*t2*t3*t8;
	float t21 = a12*a23*a31*t4*t6*t9;
	float t22 = a12*a23*a31*t5*t7*t10;
	float t23 = a13*a21*a32*t2*t3*t8;
	float t24 = a13*a21*a32*t4*t6*t9;
	float t25 = a13*a21*a32*t5*t7*t10;
	float t26 = a13*a22*a31*t2*t6*t10;
	float t27 = a13*a22*a31*t4*t5*t8;
	float t28 = a13*a22*a31*t3*t7*t9;
	float t31 = a11*a22*a33*t2*t6*t10;
	float t32 = a11*a22*a33*t4*t5*t8;
	float t33 = a11*a22*a33*t3*t7*t9;
	float t34 = a11*a23*a32*t2*t3*t8;
	float t35 = a11*a23*a32*t4*t6*t9;
	float t36 = a11*a23*a32*t5*t7*t10;
	float t37 = a12*a21*a33*t2*t3*t8;
	float t38 = a12*a21*a33*t4*t6*t9;
	float t39 = a12*a21*a33*t5*t7*t10;
	float t40 = a12*a23*a31*t2*t6*t10;
	float t41 = a12*a23*a31*t4*t5*t8;
	float t42 = a12*a23*a31*t3*t7*t9;
	float t43 = a13*a21*a32*t2*t6*t10;
	float t44 = a13*a21*a32*t4*t5*t8;
	float t45 = a13*a21*a32*t3*t7*t9;
	float t46 = a13*a22*a31*t2*t3*t8;
	float t47 = a13*a22*a31*t4*t6*t9;
	float t48 = a13*a22*a31*t5*t7*t10;
	float t29 = t11+t12+t13+t14+t15+t16+t17+t18+t19+t20+t21+t22+t23+t24+t25+t26+t27+t28-t31-t32-t33-t34-t35-t36-t37-t38-t39-t40-t41-t42-t43-t44-t45-t46-t47-t48;
	float t30 = 1.0/t29;
	float t49 = a21*a32*t2*t3;
	float t50 = a22*a31*t4*t5;
	float t51 = a21*a33*t2*t6;
	float t52 = a23*a31*t5*t7;
	float t53 = a22*a33*t4*t6;
	float t54 = a23*a32*t3*t7;
	float t111 = a21*a32*t4*t5;
	float t112 = a22*a31*t2*t3;
	float t113 = a21*a33*t5*t7;
	float t114 = a23*a31*t2*t6;
	float t115 = a22*a33*t3*t7;
	float t116 = a23*a32*t4*t6;
	float t55 = t49+t50+t51+t52+t53+t54-t111-t112-t113-t114-t115-t116;
	float t56 = a21*a32*t2*t10;
	float t57 = a22*a31*t4*t9;
	float t58 = a21*a33*t2*t8;
	float t59 = a23*a31*t7*t9;
	float t60 = a22*a33*t4*t8;
	float t61 = a23*a32*t7*t10;
	float t117 = a21*a32*t4*t9;
	float t118 = a22*a31*t2*t10;
	float t119 = a21*a33*t7*t9;
	float t120 = a23*a31*t2*t8;
	float t121 = a22*a33*t7*t10;
	float t122 = a23*a32*t4*t8;
	float t62 = t56+t57+t58+t59+t60+t61-t117-t118-t119-t120-t121-t122;
	float t63 = a21*a32*t3*t9;
	float t64 = a22*a31*t5*t10;
	float t65 = a21*a33*t6*t9;
	float t66 = a23*a31*t5*t8;
	float t67 = a22*a33*t6*t10;
	float t68 = a23*a32*t3*t8;
	float t123 = a21*a32*t5*t10;
	float t124 = a22*a31*t3*t9;
	float t125 = a21*a33*t5*t8;
	float t126 = a23*a31*t6*t9;
	float t127 = a22*a33*t3*t8;
	float t128 = a23*a32*t6*t10;
	float t69 = t63+t64+t65+t66+t67+t68-t123-t124-t125-t126-t127-t128;
	float t70 = a11*a32*t2*t3;
	float t71 = a12*a31*t4*t5;
	float t72 = a11*a33*t2*t6;
	float t73 = a13*a31*t5*t7;
	float t74 = a12*a33*t4*t6;
	float t75 = a13*a32*t3*t7;
	float t129 = a11*a32*t4*t5;
	float t130 = a12*a31*t2*t3;
	float t131 = a11*a33*t5*t7;
	float t132 = a13*a31*t2*t6;
	float t133 = a12*a33*t3*t7;
	float t134 = a13*a32*t4*t6;
	float t76 = t70+t71+t72+t73+t74+t75-t129-t130-t131-t132-t133-t134;
	float t77 = a11*a32*t2*t10;
	float t78 = a12*a31*t4*t9;
	float t79 = a11*a33*t2*t8;
	float t80 = a13*a31*t7*t9;
	float t81 = a12*a33*t4*t8;
	float t82 = a13*a32*t7*t10;
	float t135 = a11*a32*t4*t9;
	float t136 = a12*a31*t2*t10;
	float t137 = a11*a33*t7*t9;
	float t138 = a13*a31*t2*t8;
	float t139 = a12*a33*t7*t10;
	float t140 = a13*a32*t4*t8;
	float t83 = t77+t78+t79+t80+t81+t82-t135-t136-t137-t138-t139-t140;
	float t84 = a11*a32*t3*t9;
	float t85 = a12*a31*t5*t10;
	float t86 = a11*a33*t6*t9;
	float t87 = a13*a31*t5*t8;
	float t88 = a12*a33*t6*t10;
	float t89 = a13*a32*t3*t8;
	float t90 = a11*a22*t2*t3;
	float t91 = a12*a21*t4*t5;
	float t92 = a11*a23*t2*t6;
	float t93 = a13*a21*t5*t7;
	float t94 = a12*a23*t4*t6;
	float t95 = a13*a22*t3*t7;
	float t141 = a11*a22*t4*t5;
	float t142 = a12*a21*t2*t3;
	float t143 = a11*a23*t5*t7;
	float t144 = a13*a21*t2*t6;
	float t145 = a12*a23*t3*t7;
	float t146 = a13*a22*t4*t6;
	float t96 = t90+t91+t92+t93+t94+t95-t141-t142-t143-t144-t145-t146;
	float t97 = a11*a22*t2*t10;
	float t98 = a12*a21*t4*t9;
	float t99 = a11*a23*t2*t8;
	float t100 = a13*a21*t7*t9;
	float t101 = a12*a23*t4*t8;
	float t102 = a13*a22*t7*t10;
	float t147 = a11*a22*t4*t9;
	float t148 = a12*a21*t2*t10;
	float t149 = a11*a23*t7*t9;
	float t150 = a13*a21*t2*t8;
	float t151 = a12*a23*t7*t10;
	float t152 = a13*a22*t4*t8;
	float t103 = t97+t98+t99+t100+t101+t102-t147-t148-t149-t150-t151-t152;
	float t104 = a11*a22*t3*t9;
	float t105 = a12*a21*t5*t10;
	float t106 = a11*a23*t6*t9;
	float t107 = a13*a21*t5*t8;
	float t108 = a12*a23*t6*t10;
	float t109 = a13*a22*t3*t8;
	float t153 = a11*a22*t5*t10;
	float t154 = a12*a21*t3*t9;
	float t155 = a11*a23*t5*t8;
	float t156 = a13*a21*t6*t9;
	float t157 = a12*a23*t3*t8;
	float t158 = a13*a22*t6*t10;
	float t110 = t104+t105+t106+t107+t108+t109-t153-t154-t155-t156-t157-t158;

	float A11 = t9*t30*t55-t5*t30*t62-t2*t30*t69;
	float A12 = t2*t30*(t84+t85+t86+t87+t88+t89-a12*a31*t3*t9-a12*a33*t3*t8-a11*a33*t5*t8-a11*a32*t5*t10-a13*a31*t6*t9-a13*a32*t6*t10)-t9*t30*t76+t5*t30*t83;
	float A13 = t9*t30*t96-t5*t30*t103-t2*t30*t110;
	float A21 = -t3*t30*t62+t10*t30*t55-t4*t30*t69;
	float A22 = t4*t30*(t84+t85+t86+t87+t88+t89-a12*a31*t3*t9-a12*a33*t3*t8-a11*a33*t5*t8-a11*a32*t5*t10-a13*a31*t6*t9-a13*a32*t6*t10)+t3*t30*t83-t10*t30*t76;
	float A23 = -t3*t30*t103+t10*t30*t96-t4*t30*t110;
	float A31 = t8*t30*t55-t6*t30*t62-t7*t30*t69;
	float A32 = t7*t30*(t84+t85+t86+t87+t88+t89-a12*a31*t3*t9-a12*a33*t3*t8-a11*a33*t5*t8-a11*a32*t5*t10-a13*a31*t6*t9-a13*a32*t6*t10)-t8*t30*t76+t6*t30*t83;
	float A33 = t8*t30*t96-t6*t30*t103-t7*t30*t110;

	Jinv[0][0] = A11;
	Jinv[0][1] = A12;
	Jinv[0][2] = A13;
	Jinv[1][0] = A21;
	Jinv[1][1] = A22;
	Jinv[1][2] = A23;
	Jinv[2][0] = A31;
	Jinv[2][1] = A32;
	Jinv[2][2] = A33;

	return 0; //success
}


/* Function: Matrix Multiply 3x3 and 3x1
 * Inputs: 3x3 matrix (A) and 3x1 matrix (B)
 * Outputs: resulting 3x1 matrix (result)
 */
int mtxMlt_ThreeByOne (float A[3][3], float B[3], float result[3])
{

	result[0] = (A[0][0] * B[0]) + (A[0][1] * B[1]) + (A[0][2] * B[2]);
	result[1] = (A[1][0] * B[0]) + (A[1][1] * B[1]) + (A[1][2] * B[2]);
	result[2] = (A[2][0] * B[0]) + (A[2][1] * B[1]) + (A[2][2] * B[2]);

	return 0; //success
}
