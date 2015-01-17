#include "RackMotor.h"
#include "../Commands/CommandRackDoNothing.h"
#include "../RobotMap.h"

RackMotor::RackMotor() :
	Subsystem("rackMotor")
{
	motor = new Jaguar(RobotMap::Rack::motorLoc);
	potentiometer = new AnalogPotentiometer(1,270.0,135.0);
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
	float potVal = potentiometer->Get();

	float maxDegVal = (RobotMap::Rack::potentiometerTurnCount * 360.0f);

	//(currentValue minus minimum value to get rid of offset (min is 0)) / (possibleRange);
	float percentTurned = fabs(potVal - RobotMap::Rack::potentiometerMinVal) / RobotMap::Rack::potentiometerRange;

	//multiplied percentage turned by the degree value get the number of degrees turned
	float degVal = percentTurned * maxDegVal;

	return (degVal);
}

float RackMotor::getPotentiometerRaw()
{
	float potVal = potentiometer->Get();

	return (potVal);
}
