#ifndef Shovel_H
#define Shovel_H

#include "Commands/Subsystem.h"
#include "../OzPotentiometer.h"
#include "WPILib.h"

class Shovel: public Subsystem
{
private:

	SpeedController* motor;
	OzPotentiometer* potentiometer;
	Solenoid solenoid;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Shovel();
	void InitDefaultCommand();

	void  doNothing(){}
	float getPotentiometer();
	float getPotentiometerRaw();
	void  setMotor(float val);

	void retractShelf();
	void extendShelf();

};

#endif
