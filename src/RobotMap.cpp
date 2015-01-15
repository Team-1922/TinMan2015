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

}

