/*
 * OzLimitSwitch.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: Kevin
 */

#include "OzLimitSwitch.h"

OzLimitSwitch::OzLimitSwitch(const int loc) :
	m_DigInput(loc)
{
	// TODO Auto-generated constructor stub

}

OzLimitSwitch::~OzLimitSwitch() {
	// TODO Auto-generated destructor stub
}

bool OzLimitSwitch::Get()
{
#ifdef COMP_BOT
	return m_DigInput.Get();
#else
	return false;
#endif
}
