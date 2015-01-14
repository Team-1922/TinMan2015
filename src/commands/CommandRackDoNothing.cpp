#include "CommandRackDoNothing.h"

CommandRackDoNothing::CommandRackDoNothing()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);

	Requires(rackMotor);
}

// Called just before this Command runs the first time
void CommandRackDoNothing::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CommandRackDoNothing::Execute()
{
	rackMotor->doNothing();
}

// Make this return true when this Command no longer needs to run execute()
bool CommandRackDoNothing::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CommandRackDoNothing::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandRackDoNothing::Interrupted()
{

}
