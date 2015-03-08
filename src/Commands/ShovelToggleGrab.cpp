#include "ShovelToggleGrab.h"

ShovelToggleGrab::ShovelToggleGrab()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shovel);
}

// Called just before this Command runs the first time
void ShovelToggleGrab::Initialize()
{
	shovel->setGrabSolenoid(!shovel->getGrabSolenoid());
}

// Called repeatedly when this Command is scheduled to run
void ShovelToggleGrab::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ShovelToggleGrab::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ShovelToggleGrab::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelToggleGrab::Interrupted()
{

}
