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

	//information for potentiometer rate
	float m_CurrSpeed = 0.0f;//deg/s
	float m_LastTick = 0.0f;//s
	float m_LastAngle = 0.0f;//deg

public:
	OzPotentiometer(int channel, float fullRange, float offset);
	virtual ~OzPotentiometer();

	//returns the rate in degrees per second
	float GetTurnRate();

	// this is used to get rate information from the potentiometer, call this once per cycle
	void Tick();
};

#endif /* OZPOTENTIOMETER_H_ */
