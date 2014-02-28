/*
 ============================================================================
 Name        : RBE501-2014-Delta-Kinematics.c
 Author      : Kevin Harrington, Michael DiBlasi
 Version     :
 Copyright   : BSD with attribution
 Description : The kinematics system for a Linear slide Delta
 ============================================================================

 This kinematics engine uses math from http://tinyurl.com/p8ce2rk

 https://docs.google.com/viewer?a=v&pid=forums&srcid=MTgyNjQwODAyMDkxNzQxMTUwNzIBMDc2NTg4NjQ0MjUxMTE1ODY5OTkBdmZiejRRR2phZjhKATQBAXYy

 */

#include <stdio.h>

int servostock_calcInverse(float X, float Y, float Z, float *Alpha, float *Beta, float *Gama);
int servostock_calcForward(float Alpha, float Beta, float Gama, float * X, float *Y, float * Z);

float positionMatrix[4][4] = {
								{1,0,0,0},
								{0,1,0,0},
								{0,0,1,0},
								{0,0,0,1}
							  };

float jointVector[3] = {0,0,0};

float bedLevelMatrix[4][4] = {
								{1,0,0,0},
								{0,1,0,0},
								{0,0,1,0},
								{0,0,0,1}
							  };

typedef struct _DeltaConfig{
	float RodLength;
	float BaseRadius;
	float EndEffectorRadius;
	float MaxZ;
	float MinZ;
}DeltaConfig;

DeltaConfig defaultConfig ={203.82,//RodLength
							150,//BaseRadius
							40.32,//EndEffectorRadius
							400,//MaxZ
							0};//MinZ


int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */


	return 0;
}

/**
 * Take the joint space positions and convert to a task space position
 * This should transform the output using the bed level calibration
 * Return 0 for success
 * Return error code for failure
 */
int forwardKinematics( float * currentJointPositions,
					   float ** outputTaskSpacePositionMatrix
					){

	return servostock_calcForward(	currentJointPositions[0],
									currentJointPositions[1],
									currentJointPositions[2],
									&outputTaskSpacePositionMatrix[3][0],
									&outputTaskSpacePositionMatrix[3][1],
									&outputTaskSpacePositionMatrix[3][2]);
}

/**
 * Take the task space position and convert to a set of joint space positions
 * This should transform the input through the bed level calibration
 * Return 0 for success
 * Return error code for failure
 */
int inverseKinematics( float ** currentTaskSpacePosition,
					   float *  outputJointSpacePositionVector
					){
	float X = currentTaskSpacePosition[3][0];
	float Y = currentTaskSpacePosition[3][1];
	float Z = currentTaskSpacePosition[3][2];

	return servostock_calcInverse(	X, Y, Z,
									&outputJointSpacePositionVector[0],
									&outputJointSpacePositionVector[1],
									&outputJointSpacePositionVector[2]);
}

/**
 * Take in the task space position and the current task space velocities
 * load the target joint velocities into the output vector
 * Return 0 for success
 * Return error code for failure
 */

int calculateJointSpaceVelocities(	float ** currentTaskSpaceVelocities,
									float ** currentTaskSpacePosition,
									float *  outputJointSpaceVelocities
								){

	return 0;
}

/**
 * Take in the current Joint space velocities and the task space position
 * load the target task space velocities into the output matrix
 * Return 0 for success
 * Return error code for failure
 */
int calculateTaskSpaceVelocity(	float *  currentJointSpaceVelocities,
								float ** currentTaskSpacePosition,
								float ** outputTaskSpaceVelocity
							){

	return 0;
}

