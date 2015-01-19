/*
 * RobotMap.cpp
 *
 *  Created on: Jan 14, 2015
 *      Author: Kevin
 */

#include "RobotMap.h"
#include <cmath>

namespace RobotMap
{
namespace Controls
{
//TODO: change these locations (they suck)
	const int raiseRack = 5;
	const int extendRack= 6;
	const int flatRack  = 7;

	const int groundShovel = 8;
	const int humanShovel  = 9;
	const int dumpShovel   = 10;
}
namespace Rack
{
	const float extendAngle = 135;
	const float raiseAngle  = 90;
	const float flatAngle   = 0;

	const float potentiometerTurnCount 	= 0.75f;
	const float potentiometerMinVal 	= 145.776f;
	const float potentiometerMaxVal 	= 223.2f;
	const float potentiometerRange		= fabs(potentiometerMaxVal - potentiometerMinVal);
	const int   motorLoc = 4;
	const int   potentiometerLoc = 1;
}

namespace DriveTrain
{

	const int frontLeft  = 0;
	const int rearLeft   = 1;
	const int frontRight = 2;
	const int rearRight  = 3;

}
namespace Shovel
{
	const float dumpAngle   = 90;
	const float groundAngle = 0;
	const float humanAngle  = 45;
	const float liftAngle   = -30;
	const float storeAngle  = 135;

	const int motorLoc = 5;
	const float potentiometerTurnCount  = 0;//TODO: get these values
	const float potentiometerMinVal 	= 0;
	const float potentiometerMaxVal 	= 0;
	const float potentiometerRange = fabs(potentiometerMaxVal - potentiometerMinVal);;
	const int   potentiometerLoc = 2;
}

}

