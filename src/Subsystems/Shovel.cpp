#include "Shovel.h"
#include "../RobotMap.h"
#include "../Commands/CommandShovelDoNothing.h"

Shovel::Shovel() :
		Subsystem("ExampleSubsystem"),
		motor(new Talon(RobotMap::Shovel::motorLoc)),
		potentiometer(new OzPotentiometer(RobotMap::Shovel::potentiometerLoc,
										RobotMap::Shovel::potentiometerMinVal,
										RobotMap::Shovel::potentiometerMaxVal,
										RobotMap::Shovel::potentiometerTurnCount)),
										m_solenoid(RobotMap::Shovel::solenoidId)
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
	return getAngle();
}

float Shovel::getPotentiometerRaw()
{
	return potentiometer->Get();
}

float Shovel::getAngle()
{
	//get the angle
	float potVal = potentiometer->GetAngle();

	//subtract the offset defined by the 'lift' position
	return potVal - RobotMap::Shovel::liftAngle;
}


void  Shovel::setMotor(float val)
{
	motor->Set(val);
}

void Shovel::extendShelf()
{
	m_solenoid.Set(true);
}

void Shovel::retractShelf()
{
	m_solenoid.Set(false);
}
