#ifndef Shovel_H
#define Shovel_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shovel: public Subsystem
{
private:

	SpeedController* motor;
	AnalogPotentiometer* potentiometer;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Shovel();
	void InitDefaultCommand();

	float getPotentiometer();
	float getPotentiometerRaw();
	void  setMotor(float val);
};

#endif
