#include "Shovel.h"
#include "../RobotMap.h"

Shovel::Shovel() :
		Subsystem("ExampleSubsystem"),
		motor(new Talon(RobotMap::Shovel::motorLoc)),
		potentiometer(new AnalogPotentiometer(1, 270, 135, 0))
{

}

void Shovel::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
