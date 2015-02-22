/*
 * OzSolenoid.cpp
 *
 *  Created on: Feb 19, 2015
 *      Author: Kevin
 */

#include "OzSolenoid.h"

OzSolenoid::OzSolenoid(const int extendChannel, const int retractChannel) :
#ifdef COMP_BOT
	m_Solenoid(extendChannel, retractChannel)
#else
	m_Solenoid(extendChannel)
#endif
{
	// TODO Auto-generated constructor stub
#ifdef COMP_BOT
	m_Solenoid.Set(DoubleSolenoid::Value::kReverse);
#else
	m_Solenoid.Set(false);
#endif
}

void OzSolenoid::Set(bool on)
{
#ifdef COMP_BOT
	m_Solenoid.Set(on ? DoubleSolenoid::Value::kForward : DoubleSolenoid::Value::kReverse);
#else
	m_Solenoid.Set(on);
#endif
}

bool OzSolenoid::Get()
{
#ifdef COMP_BOT
	return m_Solenoid.Get() == DoubleSolenoid::Value::kForward ? true : false;
#else
	return m_Solenoid.Get();
#endif
}

bool OzSolenoid::IsBlackListed()
{
#ifdef COMP_BOT
	return m_Solenoid.IsFwdSolenoidBlackListed() || m_Solenoid.IsRevSolenoidBlackListed();
#else
	return m_Solenoid.IsBlackListed();
#endif
}

OzSolenoid::~OzSolenoid()
{
	// TODO Auto-generated destructor stub
}

