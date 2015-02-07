#include "RackDoNothing.h"

RackDoNothing::RackDoNothing()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);

	Requires(rack);
}

// Called just before this Command runs the first time
void RackDoNothing::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RackDoNothing::Execute()
{
	rack->doNothing();
}

// Make this return true when this Command no longer needs to run execute()
bool RackDoNothing::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RackDoNothing::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackDoNothing::Interrupted()
{

}
