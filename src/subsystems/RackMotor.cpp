#include <subsystems/RackMotor.h>

RackMotor::RackMotor() :
	Subsystem("rackMotor")
{
	motor = new Jaguar(1);
	potentiometer = new AnalogPotentiometer(1,270.0,135.0);
}

void RackMotor::setMotor(float level)
{
	motor->Set(level);
}

float RackMotor::getPotentiometer()
{
	float potVal = potentiometer->Get();

	return (potVal);
}
