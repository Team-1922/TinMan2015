#ifndef DriveTrain_H
#define DriveTrain_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class DriveTrain: public Subsystem
{
private:

	SpeedController* frontLeft;
	SpeedController* rearLeft;
	SpeedController* frontRight;
	SpeedController* rearRight;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	DriveTrain();
	~DriveTrain();
	void InitDefaultCommand();

	void StopMotors();
	void ArcadeDrive(Joystick* stick);
};

#endif
