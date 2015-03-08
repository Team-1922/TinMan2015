#include "ShovelSetGrab.h"

ShovelSetGrab::ShovelSetGrab(bool on) : m_on(on)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shovel);
}

// Called just before this Command runs the first time
void ShovelSetGrab::Initialize()
{
	shovel->setGrabSolenoid(m_on);
}

// Called repeatedly when this Command is scheduled to run
void ShovelSetGrab::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ShovelSetGrab::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ShovelSetGrab::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelSetGrab::Interrupted()
{

}
