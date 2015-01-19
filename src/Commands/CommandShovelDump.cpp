#include "CommandShovelDump.h"
#include "../Utilities.h"

CommandShovelDump::CommandShovelDump()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shovel);
}

// Called just before this Command runs the first time
void CommandShovelDump::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CommandShovelDump::Execute()
{
	float potAngle = shovel->getPotentiometer();

	if(potAngle < 90)
		shovel->setMotor(-.5);
	else
		shovel->setMotor(.5);
}

// Make this return true when this Command no longer needs to run execute()
bool CommandShovelDump::IsFinished()
{
	if(Utilities::isEqual(90, shovel->getPotentiometer(), 2))
		return true;
	else
		return false;
}

// Called once after isFinished returns true
void CommandShovelDump::End()
{
	shovel->setMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandShovelDump::Interrupted()
{
	End();
}
