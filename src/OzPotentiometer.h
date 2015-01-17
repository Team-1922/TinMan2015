/*
 * OzPotentiometer.h
 *
 *  Created on: Jan 17, 2015
 *      Author: Kevin
 */

#ifndef OZPOTENTIOMETER_H_
#define OZPOTENTIOMETER_H_

#include "WPILib.h"

class OzPotentiometer: public AnalogPotentiometer
{

	float minValue;
	float maxValue;
	float turnCount;
	float range;
public:
	OzPotentiometer(int channel, float minVal, float maxVal, float turnCnt);
	virtual ~OzPotentiometer();

	//get the angle in degrees, where 0 degrees is all the way to the right
	float GetAngle();
};

#endif /* OZPOTENTIOMETER_H_ */
