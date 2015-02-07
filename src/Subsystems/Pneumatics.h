#ifndef Pneumatics_sys_H
#define Pneumatics_sys_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Pneumatics: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Solenoid solenoid;

public:
	Pneumatics();
	void InitDefaultCommand();

	//set the solenoid state (true = open, false = closed)
	void setSolenoid(bool state) {solenoid.Set(state);}
};

#endif
