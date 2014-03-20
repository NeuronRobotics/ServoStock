/*
 *       ============================================================================
 *		 Name        : TestCases.c
 *		 Author      : Bill Calabro, ...
 *		 Version     : --
 *		 Copyright   : --
 *		 Description : Test cases for kinematic models
 *		 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Kinematics.h"

/*
 * Calculate inverse and forward kinematics for a 2-D square in 3-D space.
 */
int twoDSquare ( int sideLength, float * initialPosition)
{
	// Counter Variables
	int i = 0;

	// Setup Arm Configuration Array
	float config[5][3] = {{0}};

	// Setup Arm Position Array
	int currentPosition[5][3] = {{0}};
	for (i = 0; i < 3; i++)
	{
		currentPosition[0][i] = initialPosition[i];
	}

	// Setup Desired Positions
	int desiredPosition[5][3] =
		{
			{0,0,0},  //start at initial position (0, 0, 0)
			{sideLength,0,0},  //step +X (a, 0, 0)
			{0,sideLength,0},  //step +Y (a, a, 0)
			{-sideLength,0,0},  //step -X (0, a, 0)
			{0,-sideLength,0}  //step -Y to end at initial position (0, 0, 0)
		};

	// Calculate Inverse for Each Step
	printf("\r\nInverse Calculations:");
	for (i = 0; i < 5; i++)
	{
		// Handle offset for initial position
		int lookupIndex = i - 1;
		if (lookupIndex < 0)
			lookupIndex = 0;  //initial assignment

		// Set next desired position
		float Xdes = currentPosition[lookupIndex][0] + desiredPosition[i][0];
		float Ydes = currentPosition[lookupIndex][1] + desiredPosition[i][1];
		float Zdes = currentPosition[lookupIndex][2] + desiredPosition[i][2];

		// Calculate inverse
		if (servostock_calcInverse(Xdes, Ydes, Zdes,
				&config[i][0], &config[i][1], &config[i][2])
			)
			return 1;

		// Assign position values on valid inverse
		currentPosition[i][0] = Xdes;
		currentPosition[i][1] = Ydes;
		currentPosition[i][2] = Zdes;

		// Print to Console
		printf("\r\nStep %d", i);
		printf("\rPosition: X=%d, Y=%d, Z=%d",
				currentPosition[i][0], currentPosition[i][1], currentPosition[i][2]);
		printf("\rCalculated Joints: A=%g, B=%g, C=%g",
				config[i][0], config[i][1], config[i][2]);
	}

	// Setup CalculatedArm Position Array
	float calculatedPosition[5][3] = {{0}};

	// Calculate Forward for Each Step
	printf("\r\nForward Calculations:");
	for (i = 0; i < 5; i++)
	{
		// Calculate Forward
		servostock_calcForward(config[i][0], config[i][1], config[i][2],
							   &calculatedPosition[i][0], &calculatedPosition[i][1], &calculatedPosition[i][2]
							   );

		// Print to Console
		printf("\r\nStep %d", i);
		printf("\rCalculated Position: X=%g, Y=%g, Z=%g",
				calculatedPosition[i][0], calculatedPosition[i][1], calculatedPosition[i][2]);
		printf("\rJoints: A=%g, B=%g, C=%g",
				config[i][0], config[i][1], config[i][2]);
	}

	//TODO plot graphically?

	//TODO return values?

	return 0;  //success
}

/*
 * Calculate inverse and forward kinematics for a generic 3-D model by a set of discrete points.
 * The 'positionCount' parameter must be of the same size as all three parameter arrays.
 */
int threeDTestCase (int positionCount, const float desiredPositions[][3], float calculatedJoints[][3], float calculatedPositions[][3])
{
	// Counter Variables
	int i = 0;

	// Calculate Inverse for Each Step
	printf("\r\nInverse Calculations:");
	for (i = 0; i < positionCount; i++)
	{
		// Calculate inverse
		if (servostock_calcInverse(desiredPositions[i][0], desiredPositions[i][1], desiredPositions[i][2],
				&calculatedJoints[i][0], &calculatedJoints[i][1], &calculatedJoints[i][2])
			)
			return 1;

		// Print to Console
		printf("\r\nStep %d", i);
		printf("\rPosition: X=%g, Y=%g, Z=%g",
				desiredPositions[i][0], desiredPositions[i][1], desiredPositions[i][2]);
		printf("\rCalculated Joints: A=%g, B=%g, C=%g",
				calculatedJoints[i][0], calculatedJoints[i][1], calculatedJoints[i][2]);
	}

	// Calculate Forward for Each Step
	printf("\r\nForward Calculations:");
	for (i = 0; i < positionCount; i++)
	{
		// Calculate Forward
		if (servostock_calcForward(calculatedJoints[i][0], calculatedJoints[i][1], calculatedJoints[i][2],
							   &calculatedPositions[i][0], &calculatedPositions[i][1], &calculatedPositions[i][2]
							   ))
			return 1;

		// Print to Console
		printf("\r\nStep %d", i);
		printf("\rCalculated Position: X=%g, Y=%g, Z=%g",
				calculatedPositions[i][0], calculatedPositions[i][1], calculatedPositions[i][2]);
		printf("\rJoints: A=%g, B=%g, C=%g",
				calculatedJoints[i][0], calculatedJoints[i][1], calculatedJoints[i][2]);
	}

	//TODO plot graphically?

	return 0;  //success
}

/*
 * Generate a set of data points to define a 2-D circle at a fixed height in the z-direction.
 * The 'steCount' parameter must be of the same size as the 'dataPoints' parameter fist array.
 */
void define2DCircle (int radius, int stepCount, float * origin, float dataPoints[][3])
{
	// Setup Variables
	float alphaStep = (2 * M_PI) / stepCount;
	float alpha = 0;
	float x = 0;
	float y = 0;

	// Define Zeroth Point
	dataPoints[0][0] = radius + origin[0];
	dataPoints[0][1] = origin[1];
	dataPoints[0][2] = origin[2];

	// Define Each Point
	int i = 0;  //counter
	for (i = 1; i < stepCount; i++)
	{
		alpha = alpha + alphaStep;
		x = cos(alpha) * radius;
		y = sin(alpha) * radius;

		if (x < 0.01 && x > -0.01)
			x = 0;
		if (y < 0.01 && y > -0.01)
			y = 0;

		dataPoints[i][0] = x;
		dataPoints[i][1] = y;
		dataPoints[i][2] = origin[2];
	}
}

/*
 * Calculate inverse and forward kinematics for a 2-D equilateral triangle in 3-D space.
 * Triangle top faces in the Y direction with center located at the specified origin
 */
void twoDTriangle (int length, float * origin, float dataPoints[][3])
{
	// Setup Variables
	float x = 0;
	float y = 0;
	float z = 0;

	// Define Zeroth Point
	// Origin should be at center of triangle
	x = origin[0];
	y = (length * sin(30 * M_PI / 180))/sin(120 * M_PI / 180) + origin[1]; //y=length*sin(30)/sin(120) based on law of sines
	z = origin[2];

	dataPoints[0][0] = x;
	dataPoints[0][1] = y;
	dataPoints[0][2] = z;

	x = x + length/2; //add half of 1 side since equilateral
	y = y - (length/2)*sqrt(3); //subtract height of triangle due to 30-60-90 triangle

	dataPoints[1][0] = x;
	dataPoints[1][1] = y;
	dataPoints[1][2] = z;

	x = x - length; //move to other side of triangle

	dataPoints[2][0] = x;
	dataPoints[2][1] = y;
	dataPoints[2][2] = z;

	x = x + length/2; //return to zeroth point
	y = y + (length/2)*sqrt(3); //return to zeroth point

	dataPoints[3][0] = x;
	dataPoints[3][1] = y;
	dataPoints[3][2] = z;
}

