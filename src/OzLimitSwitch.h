/*
 * OzLimitSwitch.h
 *
 *  Created on: Feb 21, 2015
 *      Author: Kevin
 */

#ifndef OZLIMITSWITCH_H_
#define OZLIMITSWITCH_H_

#include "WPILib.h"

//this only matters on the practice bot
class OzLimitSwitch
{
	DigitalInput m_DigInput;
public:
	OzLimitSwitch(const int location);
	virtual ~OzLimitSwitch();

	bool Get();
};

#endif /* OZLIMITSWITCH_H_ */
