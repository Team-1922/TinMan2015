#include "RackOpenClaw.h"

RackOpenClaw::RackOpenClaw()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rack);
}

// Called just before this Command runs the first time
void RackOpenClaw::Initialize()
{
	rack->setClaw(false);
}

// Called repeatedly when this Command is scheduled to run
void RackOpenClaw::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool RackOpenClaw::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void RackOpenClaw::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackOpenClaw::Interrupted()
{

}
