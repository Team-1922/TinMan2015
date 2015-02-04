/*
 * OzPotentiometer.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: Kevin
 */

#include "OzPotentiometer.h"
#include <cmath>

OzPotentiometer::OzPotentiometer(int channel, float minVal, float maxVal, float turnCnt) :
		AnalogPotentiometer(channel, maxVal, minVal),
		minValue(minVal), maxValue(maxVal), turnCount(turnCnt)
{
	range = fabs(maxVal - minVal);
}

OzPotentiometer::~OzPotentiometer()
{
	// TODO Auto-generated destructor stub
}

float OzPotentiometer::GetAngle()
{
	float potVal = this->Get();

	float maxDegVal = (turnCount * 360.0f);

	//(currentValue minus minimum value to get rid of offset (min is 0)) / (possibleRange);
	float percentTurned = fabs(potVal - minValue) / range;
	//multiplied percentage turned by the degree value get the number of degrees turned
	float degVal = percentTurned * maxDegVal;

	return (degVal);
}
