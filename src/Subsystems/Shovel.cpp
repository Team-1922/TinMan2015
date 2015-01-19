#include "Shovel.h"
#include "../RobotMap.h"
#include "../Commands/CommandShovelDoNothing.h"

Shovel::Shovel() :
		Subsystem("ExampleSubsystem"),
		motor(new Talon(RobotMap::Shovel::motorLoc)),
		potentiometer(new OzPotentiometer(RobotMap::Shovel::potentiometerLoc,
										RobotMap::Shovel::potentiometerMinVal,
										RobotMap::Shovel::potentiometerMaxVal,
										RobotMap::Shovel::potentiometerTurnCount))
{

}

void Shovel::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new CommandShovelDoNothing());
	//TODO: default command
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


float Shovel::getPotentiometer()
{
	//get the angle
	float potVal = potentiometer->GetAngle();

	//subtract the offset defined by the 'lift' position
	return potVal - RobotMap::Shovel::liftAngle;
}

float Shovel::getPotentiometerRaw()
{
	return potentiometer->Get();
}

void  Shovel::setMotor(float val)
{
	motor->Set(val);
}
