#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "WPILib.h"

class DriveTrain{
public:
	DriveTrain();
	~DriveTrain();

	void ozDrive(Joystick* stick); //see what the joystick will pass and add arguments


private:
	Talon *frontLeft;
	Talon *rearLeft;
	Talon *frontRight;
	Talon *rearRight;


};

#endif
