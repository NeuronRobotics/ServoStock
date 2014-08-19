#include "main.h"

//#include <Bowler/Debug.h>

float toDegrees(float radian){
	return radian*(180/3.14159);
}
float toRadian(float degree){
	return (degree/180)*3.14159;
}

float firstLink = 12.0*25.4;
float secondLink= 13.45*25.4;

int frog_calcInverse(float X, float Y, float Z, float *Alpha, float *Beta, float *Gamma){
	if(X<1){
		return 1;
	}
	float hypotinuse = sqrt((X*X)+(Y*Y)+(Z*Z));
	float xyAngleOffset = atan2(Y,X);
	float angleofInclanation = atan2(Z,X);
	//printf("\r\nAngles XY=%g ZY=%g Hyp=%g",toDegrees(xyAngleOffset),toDegrees(angleofInclanation),hypotinuse);

	// using c^2=a^2+b^2−2abcosθ

	float a= hypotinuse;
	float b=firstLink;
	float c= secondLink;

	float theta = acosf(((b*b)+(a*a)-(c*c))/(2*a*b));

	Alpha[0]=toDegrees(1*(theta+xyAngleOffset));
	Beta[0] =toDegrees(-1*(theta-xyAngleOffset));
	Gamma[0] = toDegrees(angleofInclanation);
    return 0;//SUCCESS
}

int frog_calcForward(float Alpha, float Beta, float Gamma, float * X, float *Y, float * Z){
	float xyAngleOffset = (Alpha+Beta)/2;
	float theta = toRadian(Alpha-xyAngleOffset);

	float c=firstLink;
	float b= secondLink;
	float B =theta;
	float angleofInclanation = toRadian(90) - toRadian(Gamma);

	float D = (c/b)*sinf(B);


	float C=asinf(D);

	float A=toRadian(180)-B-C;

	//printf("\r\nInterior Angles C=%g A=%g B=%g D=%g ",toDegrees(C),toDegrees(A),toDegrees(B),D);


	float hypotinuse=(b*sinf(A))/sin(B);
	//float hypotinuse =sqrt((b*b)+(2*a*b));

	//printf("\r\nFWD Angles XY=%g theta =%g Hyp=%g",xyAngleOffset,toDegrees(theta ),hypotinuse);

	if(D>1){
		//THis is not an achievable configuration
		//printf("\r\n!!FWD kinematics failed");
		return 1;
	}

	X[0]= hypotinuse * cosf(toRadian(xyAngleOffset))*	sinf(angleofInclanation);
	Y[0]= hypotinuse * sinf(toRadian(xyAngleOffset))*	sinf(angleofInclanation);
	Z[0]= hypotinuse * 									cosf(angleofInclanation);

    return 0;//success
}
