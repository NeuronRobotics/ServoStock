/*
 ============================================================================
 Name        : RBE501-2014-Delta-Kinematics.c
 Author      : Kevin Harrington, Michael DiBlasi, Bill Calabro, Jared Heiser, and Krishna Matta
 Version     :
 Copyright   : BSD with attribution
 Description : The kinematics system for a Linear slide Delta
 ============================================================================

 This kinematics engine uses math from http://tinyurl.com/p8ce2rk

 https://docs.google.com/viewer?a=v&pid=forums&srcid=MTgyNjQwODAyMDkxNzQxMTUwNzIBMDc2NTg4NjQ0MjUxMTE1ODY5OTkBdmZiejRRR2phZjhKATQBAXYy

 */

#include <stdio.h>
#include "Kinematics.h"
#include "TestCases.h"

// Prototypes
int forwardKinematics( float * currentJointPositions,
					   float * outputTaskSpacePositionMatrix);
int inverseKinematics( float * currentTaskSpacePosition,
					   float *  outputJointSpacePositionVector);
int calculateJointSpaceVelocities(	float * currentTaskSpacePosition,
									float * desiredTaskSpaceVelocities,
									float * outputJointSpaceVelocities);
int calculateTaskSpaceVelocities(	float * currentJointSpacePosition,
								float * desiredJointSpaceVelocities,
								float * outputTaskSpaceVelocity);

// Definitions
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

//static DeltaConfig defaultConfig ={203.82,//RodLength
//							150,//BaseRadius
//							40.32,//EndEffectorRadius
//							400,//MaxZ
//							0};//MinZ


//Main Function - Issue#2
int main(void) {
	puts("Running basic kinematics test");

	// Stale Test Case
	/*
	float cartestian [4]={ 1,0,0,0};
	float joint [3] = {0,0,0};
	float cartestianSet[4] ={ 0,0,0,0//random values };
	float jointSet [3] = {0,0,0};
	if(inverseKinematics(cartestianSet, jointSet)){
		return 1;
	}
	printf("\r\nJoints A=%g B=%g C=%g",jointSet[0],jointSet[1],jointSet[2]);
	forwardKinematics(jointSet,cartestian);
	printf("\r\nSetting X=%g Y=%g Z=%g",cartestianSet[0],cartestianSet[1],cartestianSet[2]);
	printf("\r\nResult X=%g Y=%g Z=%g",cartestian[0],cartestian[1],cartestian[2]);
	*/

	// Workspace Test Case
	printf("\r\n\r\n2D Diamond Maximum Workspace Test Case \r\n");
	if (twoDEllipseWorkspace(63, 41))  //where angle length should be sqrt(sideLength * sideLength / 2)
		return 1;


	// Velocity Test Cases
	printf("\r\rInverse Velocity Wrap Test Case\r");
	float taskEx0[3] = {0, 0, 0};
	float taskVelEx0[3] = {100, 1000, 0};
	if (wrapInverseVelocity(taskEx0, taskVelEx0))
		return 1;

	printf("\r\rInverse Velocity Test Case 1\r");
	float taskEx1[3] = {0, -14.71, 21.35}; //joints at (160, 180, 180)
	float taskVelEx1[3] = {100, 0, 0};
	if (inverseVelocity(taskEx1, taskVelEx1))
		return 1;

	printf("\r\rInverse Velocity Test Case 2\r");
	float taskVelEx2[3] = {0, 100, 0};
	if (inverseVelocity(taskEx1, taskVelEx2))
		return 1;

	printf("\r\rInverse Velocity Test Case 3\r");
	float taskVelEx3[3] = {0, 0, 100};
	if (inverseVelocity(taskEx1, taskVelEx3))
		return 1;

	printf("\r\rInverse Velocity Test Case 4\r");
	float taskVelEx4[3] = {50, 100, 25};
	if (inverseVelocity(taskEx1, taskVelEx4))
		return 1;

	// Position Test Cases
	printf("\r\n\r\n2D Square Test Case \r\n");
	float initialPosition[3] = {0,0,0};
	if (twoDSquare(10, initialPosition))
		return 1;

	printf("\r\n\r\n2D Square Maximum Workspace Test Case \r\n");
	if (twoDSquare(69, initialPosition))
		return 1;

	printf("\r\n\r\n2D Square Outside Workspace Test Case \r\n");
	twoDSquare(70, initialPosition);

	printf("\r\n\r\n2D Circle Test Case \r\n");
	float origin[3] = {0,0,0};
	float testPoints[4][3] = {{0}};
	define2DCircle(10, 4, origin, &testPoints);
	float testPositions[4][3] = {{0}};
	float testJoints[4][3] = {{0}};
	if (threeDTestCase(4, testPoints, &testPositions, &testJoints))
		return 1;

	printf("\r\n\r\n2D Circle Maximum Workspace Test Case \r\n");
	float testPointsLarge[10][3] = {{0}};
	define2DCircle(69, 10, origin, &testPointsLarge);
	float testPositionsLarge[10][3] = {{0}};
	float testJointsLarge[10][3] = {{0}};
	if (threeDTestCase(10, testPointsLarge, &testPositionsLarge, &testJointsLarge))
		return 1;

	printf("\r\n\r\n2D Triangle Test Case of Length = 10 \r\n");
	float triagPoints[4][3] = {{0}};
	twoDTriangle(10, origin, &triagPoints);
	float triagPositions[4][3] = {{0}};
	float triagJoints[4][3] = {{0}};
	if (threeDTestCase(4, triagPoints, &triagPositions, &triagJoints))
		return 1;

	printf("\r\n\r\nDone");
	return 0;
}

/**
 * Take the joint space positions and convert to a task space position
 * This should transform the output using the bed level calibration
 * Return 0 for success
 * Return error code for failure
 */
int forwardKinematics( float * currentJointPositions,
					   float * outputTaskSpacePositionMatrix
					){

	return servostock_calcForward(	currentJointPositions[0],
									currentJointPositions[1],
									currentJointPositions[2],
									&outputTaskSpacePositionMatrix[0],
									&outputTaskSpacePositionMatrix[1],
									&outputTaskSpacePositionMatrix[2]);
}

/**
 * Take the task space position and convert to a set of joint space positions
 * This should transform the input through the bed level calibration
 * Return 0 for success
 * Return error code for failure
 */
int inverseKinematics( float * currentTaskSpacePosition,
					   float *  outputJointSpacePositionVector
					){
	float X = currentTaskSpacePosition[0];
	float Y = currentTaskSpacePosition[1];
	float Z = currentTaskSpacePosition[2];

	return servostock_calcInverse(	X, Y, Z,
									&outputJointSpacePositionVector[0],
									&outputJointSpacePositionVector[1],
									&outputJointSpacePositionVector[2]);
}

/**
 * Take in the Task-space position and the desired velocities
 * load the target Joint-space velocities into the output vector
 * Return 0 for success
 * Return error code for failure
 */

int calculateJointSpaceVelocities(	float * currentTaskSpacePosition,
									float * desiredTaskSpaceVelocities,
									float * outputJointSpaceVelocities
								){
	float X = currentTaskSpacePosition[0];
	float Y = currentTaskSpacePosition[1];
	float Z = currentTaskSpacePosition[2];

	return servostock_velInverse(	X, Y, Z,
									desiredTaskSpaceVelocities[0],
									desiredTaskSpaceVelocities[1],
									desiredTaskSpaceVelocities[2],
									&outputJointSpaceVelocities[0],
									&outputJointSpaceVelocities[1],
									&outputJointSpaceVelocities[2]);

	return 0;
}

/**
 * Take in the current Joint-space position and desired velocities
 * load the target Task-space velocities into the output matrix
 * Return 0 for success
 * Return error code for failure
 */
int calculateTaskSpaceVelocities(	float * currentJointSpacePosition,
								float * desiredJointSpaceVelocities,
								float * outputTaskSpaceVelocity
							){
	float A = currentJointSpacePosition[0];
	float B = currentJointSpacePosition[1];
	float C = currentJointSpacePosition[2];

	return servostock_velForward(	A, B, C,
									desiredJointSpaceVelocities[0],
									desiredJointSpaceVelocities[1],
									desiredJointSpaceVelocities[2],
									&outputTaskSpaceVelocity[0],
									&outputTaskSpaceVelocity[1],
									&outputTaskSpaceVelocity[2]);

	return 0;
}

