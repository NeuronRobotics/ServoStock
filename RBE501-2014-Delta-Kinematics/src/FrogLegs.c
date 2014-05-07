#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
//#include <Bowler/Debug.h>

float toDegrees(float radian){
	return radian*(180/3.14159);
}
float toRadian(float degree){
	return (degree/180)*3.14159;
}

float firstLink = 12.0;
float secondLink=13.45;

int frog_calcInverse(float X, float Y, float Z, float *Alpha, float *Beta, float *Gamma){
	if(X<1){
		return 1;
	}
	float hypotinuse = sqrt((X*X)+(Y*Y)+(Z*Z));
	float xyAngleOffset = atan2(Y,X);
	float angleofInclanation = atan2(Z,X);
	printf("\r\nAngles XY=%g ZY=%g Hyp=%g",toDegrees(xyAngleOffset),toDegrees(angleofInclanation),hypotinuse);

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



    return 0;//success
}
