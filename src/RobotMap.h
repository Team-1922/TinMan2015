/*
 * RobotMap.h
 *
 *  Created on: Jan 14, 2015
 *      Author: Kevin
 */

#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

#include <cmath>

namespace RobotMap
{
	namespace Controls
	{
		//TODO: Change these locations
		//The control for rasing, extending, and "flatting" the rack
		const int raiseRack = 5;
		const int extendRack= 6;
		const int flatRack  = 7;

		//the controls for the three shovel positions
		const int groundShovel = 8;
		const int humanShovel  = 9;
		const int dumpShovel   = 10;
	}

	namespace Rack
	{
		//the angles of each of the positions in degrees
		const float extendAngle = 135;
		const float raiseAngle  = 90;
		const float flatAngle   = 0;

		//the number of turns
		const float potentiometerTurnCount 	= 0.75f;

		//the minimum bound of potentiometer
		const float potentiometerMinVal 	= 145.776f;

		//the maximum bound of potentiometer
		const float potentiometerMaxVal 	= 223.2f;

		//the range of the two above values
		const float potentiometerRange		= fabs(potentiometerMaxVal - potentiometerMinVal);

		//the location of the rack motor
		const int   motorLoc = 4;
		const int   potentiometerLoc = 1;
	}

	//the drive train constants
	namespace DriveTrain
	{

		//the locations of the motors
		const int frontLeft  = 0;
		const int rearLeft   = 1;
		const int frontRight = 2;
		const int rearRight  = 3;

	}

	namespace Shovel
	{
		//the angles of each of the positions in degrees
		const float dumpAngle   = 90;
		const float groundAngle = 0;
		const float humanAngle  = 45;
		const float liftAngle   = -30;
		const float storeAngle  = 135;

		//the motor location for the shovel
		const int motorLoc = 5;

		//the number of turns
		const float potentiometerTurnCount 	= 0.75f;//TODO: get real values for a different potentiometer

		//the minimum bound of potentiometer
		const float potentiometerMinVal 	= 145.776f;

		//the maximum bound of potentiometer
		const float potentiometerMaxVal 	= 223.2f;

		//the range of the two above values
		const float potentiometerRange		= fabs(potentiometerMaxVal - potentiometerMinVal);

		const int   potentiometerLoc = 1;
	}
}



#endif /* ROBOTMAP_H_ */
