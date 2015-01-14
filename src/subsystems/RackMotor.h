#ifndef RACK_MOTOR_H
#define RACK_MOTOR_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class RackMotor: public Subsystem
{

private:
	SpeedController* motor;
	AnalogPotentiometer* potentiometer;

public:
	RackMotor();
	void InitDefaultCommand() {}

	void doNothing(){}
	void setMotor(float level);
	float getPotentiometer();


}

#endif
