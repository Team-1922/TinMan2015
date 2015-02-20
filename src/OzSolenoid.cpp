/*
 * OzSolenoid.cpp
 *
 *  Created on: Feb 19, 2015
 *      Author: Kevin
 */

#include "OzSolenoid.h"

OzSolenoid::OzSolenoid(const int extendChannel, const int retractChannel) :
#ifdef COMP_BOT
	m_pSolenoid(extendChannel, retractChannel)
#else
	m_pSolenoid(extendChannel)
#endif
{
	// TODO Auto-generated constructor stub
#ifdef COMP_BOT
	m_pSolenoid.Set(DoubleSolenoid::Value::kReverse);
#else
	m_pSolenoid.Set(false);
#endif
}

void OzSolenoid::Set(bool on)
{
#ifdef COMP_BOT
	m_pSolenoid.Set(on ? DoubleSolenoid::Value::kForward : DoubleSolenoid::Value::kReverse);
#else
	m_pSolenoid.Set(on);
#endif
}

bool OzSolenoid::Get()
{
#ifdef COMP_BOT
	return m_pSolenoid.Get() == DoubleSolenoid::Value::kForward ? true : false;
#else
	return m_pSolenoid.Get();
#endif
}

bool OzSolenoid::IsBlackListed()
{
#ifdef COMP_BOT
	return m_pSolenoid.IsFwdSolenoidBlackListed() || m_pSolenoid.IsRevSolenoidBlackListed();
#else
	return m_pSolenoid.IsBlackListed();
#endif
}

OzSolenoid::~OzSolenoid()
{
	// TODO Auto-generated destructor stub
}

