/*
 * OI.h
 *
 */

#ifndef OI_H_
#define OI_H_

#include "WPILib.h"

class OI {
public:
	OI();
	Joystick* GetDriverJoystick();
	Joystick* GetOperatorJoystick();

private:
	Joystick* m_pDriverStick;
	Joystick* m_pOperatorStick;
};

#endif /* OI_H_ */
