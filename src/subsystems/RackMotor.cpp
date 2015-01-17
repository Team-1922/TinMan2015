#include "RackMotor.h"
#include "../Commands/CommandRackDoNothing.h"
#include "../RobotMap.h"

RackMotor::RackMotor() :
	Subsystem("rackMotor")
{
	motor = new Jaguar(RobotMap::Rack::motorLoc);
	potentiometer = new OzPotentiometer(RobotMap::Rack::potentiometerLoc,
										RobotMap::Rack::potentiometerMinVal,
										RobotMap::Rack::potentiometerMaxVal,
										RobotMap::Rack::potentiometerTurnCount);
}

void RackMotor::setMotor(float level)
{
	motor->Set(level);
}

void RackMotor::InitDefaultCommand()
{
	SetDefaultCommand(new CommandRackDoNothing());
}

float RackMotor::getPotentiometer()
{
	return potentiometer->GetAngle();
}

float RackMotor::getPotentiometerRaw()
{
	float potVal = potentiometer->Get();

	return (potVal);
}
