#include "RackMotor.h"
#include "../RobotMap.h"

RackMotor::RackMotor() :
	Subsystem("rackMotor")
{
	motor = new Jaguar(4);
	potentiometer = new AnalogPotentiometer(1,270.0,135.0);
}

void RackMotor::setMotor(float level)
{
	motor->Set(level);
}

float RackMotor::getPotentiometer()
{
	float potVal = potentiometer->Get();

	float maxDegVal = (RobotMap::potentiometerTurnCount * 360.0f);

	//(currentValue minus minimum value to get rid of offset (min is 0)) / (possibleRange);
	float percentTurned = fabs(potVal - RobotMap::potentiometerMinVal) / RobotMap::potentiometerRange;

	//multiplied percentage turned by the degree value get the number of degrees turned
	float degVal = percentTurned * maxDegVal;

	return (degVal);
}

float RackMotor::getPotentiometerRaw()
{
	float potVal = potentiometer->Get();

	return (potVal);
}
