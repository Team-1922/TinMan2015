/*
 * OzPotentiometer.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: Kevin
 */

#include "OzPotentiometer.h"
#include "RobotMap.h"
#include "Utilities.h"
#include <cmath>

OzPotentiometer::OzPotentiometer(int channel, float fullRange, float offset) :
		AnalogPotentiometer(channel, fullRange, offset)
{
	//setup the potentiometer for rate
	m_LastTick = Utilities::getTime();
	m_LastAngle = Get();
	Tick();
}

OzPotentiometer::~OzPotentiometer()
{
	// TODO Auto-generated destructor stub
}

void OzPotentiometer::Tick()
{
	float currTime = Utilities::getTime();

	//don't tick too often
	if (currTime - m_LastTick < RobotMap::minPollWait)
		return;

	float currAngle = Get();

	//this is in degrees per second
	m_CurrSpeed = (currAngle - m_LastAngle) /
			/*	  --------------------------		*/
				  (currTime - m_LastTick);

	//this would be: change in angle divided by change in time = degrees/s

	//finally update the last tick time
	m_LastTick = currTime;
}

float OzPotentiometer::GetTurnRate()
{
	return m_CurrSpeed;
}
