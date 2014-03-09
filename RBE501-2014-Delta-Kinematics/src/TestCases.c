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
