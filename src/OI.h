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
	Joystick* GetJoystick();

private:
	Joystick* stick;
};

#endif /* OI_H_ */
