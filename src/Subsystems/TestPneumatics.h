#ifndef TestPneumatics_H
#define TestPneumatics_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class TestPneumatics: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Solenoid solenoid;

public:
	TestPneumatics();
	void InitDefaultCommand();

	//set the solenoid state (true = open, false = closed)
	void setSolenoid(bool state) {solenoid.Set(state);}
};

#endif
