
#include "main.h"


int box_calcInverse(float X, float Y, float Z, float *Alpha, float *Beta, float *Gamma){

	Alpha[0]=X;
	Beta[0] =Y;
	Gamma[0] = Z;
    return 0;//SUCCESS
}

int box_calcForward(float Alpha, float Beta, float Gamma, float * X, float *Y, float * Z){

	X[0]= Alpha;
	Y[0]= Beta;
	Z[0]= Gamma;

    return 0;//success
}

