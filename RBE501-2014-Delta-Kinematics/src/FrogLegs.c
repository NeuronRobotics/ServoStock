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
	float hypotinuse = sqrt(X*X+Y*Y+Z*Z);
	float xyAngleOffset = atan2(X,Y);
	float angleofInclanation = atan2(Z,Y);
	printf("\r\nAngles XY=%g ZY=%g ",toDegrees(xyAngleOffset),toDegrees(angleofInclanation));


    return 0;//SUCCESS
}

int frog_calcForward(float Alpha, float Beta, float Gamma, float * X, float *Y, float * Z){



    return 0;//success
}
