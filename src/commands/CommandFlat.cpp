#include "CommandFlat.h"

CommandFlat::CommandFlat() :
	CommandBase("CommandFlat")
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackMotor);
}

// Called just before this Command runs the first time
void CommandFlat::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CommandFlat::Execute()
{
	//start at half speed just in case
	rackMotor->setMotor(-.5);
}

// Make this return true when this Command no longer needs to run execute()
bool CommandFlat::IsFinished()
{
	if( rackMotor->getPotentiometer() <= 0)
		return true;
	else
		return false;
}

// Called once after isFinished returns true
void CommandFlat::End()
{
	rackMotor->setMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandFlat::Interrupted()
{
	End();
}
