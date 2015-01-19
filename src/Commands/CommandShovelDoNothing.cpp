#include "CommandShovelDoNothing.h"

CommandShovelDoNothing::CommandShovelDoNothing()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(camera);
}

// Called just before this Command runs the first time
void CommandShovelDoNothing::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CommandShovelDoNothing::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool CommandShovelDoNothing::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CommandShovelDoNothing::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandShovelDoNothing::Interrupted()
{

}
