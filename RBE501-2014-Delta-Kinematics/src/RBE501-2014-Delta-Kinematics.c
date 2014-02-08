/*
 ============================================================================
 Name        : RBE501-2014-Delta-Kinematics.c
 Author      : Kevin Harrington
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================

 This kinematics engine uses math from http://tinyurl.com/p8ce2rk

 https://docs.google.com/viewer?a=v&pid=forums&srcid=MTgyNjQwODAyMDkxNzQxMTUwNzIBMDc2NTg4NjQ0MjUxMTE1ODY5OTkBdmZiejRRR2phZjhKATQBAXYy

 */

#include <stdio.h>

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


int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */


	return 0;
}

/**
 * Take the joint space positions and convert to a task space position
 * This should transform the output using the bed level calibration
 */
int forwardKinematics( float * currentJointPositions,
					   float ** outputTaskSpacePositionMatrix
					){
	return 0;
}

/**
 * Take the task space position and convert to a set of joint space positions
 * This should transform the input through the bed level calibration
 */
int inverseKinematics( float ** currentTaskSpacePosition,
					   float *  outputJointSpacePositionVector
					){
	return 0;
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

