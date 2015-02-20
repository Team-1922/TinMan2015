/*
 * OzSolenoid.h
 *
 *  Created on: Feb 19, 2015
 *      Author: Kevin
 */

#ifndef OZSOLENOID_H_
#define OZSOLENOID_H_

#include "WPILib.h"
#include "RobotMap.h"

class OzSolenoid
{
#ifdef COMP_BOT
	DoubleSolenoid m_pSolenoid;
#else
	Solenoid m_pSolenoid;
#endif

public:
	//the first channel use the only one used with the practice bot
	OzSolenoid(const int extendChannel, const int retractChannel);
	virtual ~OzSolenoid();

	void Set(bool on);
	bool Get();
	bool IsBlackListed();
};

#endif /* OZSOLENOID_H_ */
