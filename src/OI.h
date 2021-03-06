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
	Joystick* GetDriverJoystick1();
	Joystick* GetDriverJoystick2();
	Joystick* GetOperatorJoystick();
	Joystick* GetDriverController();

	//returns a value between 0 and 1
	float GetOperatorThrottle();

private:
	Joystick* m_pDriverStick1;
	Joystick* m_pDriverStick2;
	Joystick* m_pOperatorStick;
	Joystick* m_pDriverController;
};

#endif /* OI_H_ */
