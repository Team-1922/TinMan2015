#include "ShovelDoNothing.h"

ShovelDoNothing::ShovelDoNothing()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(camera);
}

// Called just before this Command runs the first time
void ShovelDoNothing::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ShovelDoNothing::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ShovelDoNothing::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ShovelDoNothing::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelDoNothing::Interrupted()
{

}
