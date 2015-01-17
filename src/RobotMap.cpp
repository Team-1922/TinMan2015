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
}
namespace Rack
{
	const float potentiometerTurnCount 	= 0.75f;
	const float potentiometerMinVal 	= 145.776f;
	const float potentiometerMaxVal 	= 223.2f;
	const float potentiometerRange		= fabs(potentiometerMaxVal - potentiometerMinVal);
	const int   motorLoc = 4;
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
const int motorLoc = 5;
const float potentiometerTurnCount;//TODO: get these values
const float potentiometerMinVal;
const float potentiometerMaxVal;
const float potentiometerRange = fabs(potentiometerMaxVal - potentiometerMinVal);;
}

}

