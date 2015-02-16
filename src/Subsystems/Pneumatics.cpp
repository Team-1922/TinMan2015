#include "Subsystems/Pneumatics.h"
#include "../RobotMap.h"
#include "../Commands/TestPneumatics.h"

Pneumatics::Pneumatics() :
		Subsystem("ExampleSubsystem"),
		solenoid(0)//channel 0 to test
{

}

void Pneumatics::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new TestPneumatics());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
