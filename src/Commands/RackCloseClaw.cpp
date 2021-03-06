#include "RackCloseClaw.h"

RackCloseClaw::RackCloseClaw()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rack);
}

// Called just before this Command runs the first time
void RackCloseClaw::Initialize()
{
	rack->setClaw(false);
}

// Called repeatedly when this Command is scheduled to run
void RackCloseClaw::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool RackCloseClaw::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void RackCloseClaw::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackCloseClaw::Interrupted()
{

}
