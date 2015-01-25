#ifndef RACK_MOTOR_H
#define RACK_MOTOR_H

#include "../OzPotentiometer.h"
#include "Commands/Subsystem.h"
#include "WPILib.h"

class RackMotor: public Subsystem
{

private:
	SpeedController* motor;
	OzPotentiometer* potentiometer;

public:
	RackMotor();
	void InitDefaultCommand();

	void doNothing(){}
	void setMotor(float level);
	float getMotor(){return motor->Get();}
	float getPotentiometer();
	float getPotentiometerRaw();


};

#endif
