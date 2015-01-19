#include "TestPneumatics.h"
#include "../RobotMap.h"
#include "../Commands/CommandTestPneumatics.h"

TestPneumatics::TestPneumatics() :
		Subsystem("ExampleSubsystem"),
		solenoid(0)//channel 0 to test
{

}

void TestPneumatics::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new CommandTestPneumatics());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
