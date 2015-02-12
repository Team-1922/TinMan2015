#include "RackToggleClaw.h"

RackToggleClaw::RackToggleClaw()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rack);
}

// Called just before this Command runs the first time
void RackToggleClaw::Initialize()
{
	if(rack->getClaw())
		rack->setClaw(false);
	else
		rack->setClaw(true);
}

// Called repeatedly when this Command is scheduled to run
void RackToggleClaw::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool RackToggleClaw::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void RackToggleClaw::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackToggleClaw::Interrupted()
{

}
