#include "ShovelToggleCollect.h"

ShovelToggleCollect::ShovelToggleCollect()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shovel);
}

// Called just before this Command runs the first time
void ShovelToggleCollect::Initialize()
{
	bool val = !shovel->getCollectSolenoid();
	shovel->setCollectSolenoid(val);
	shovel->setGrabSolenoid(val);
}

// Called repeatedly when this Command is scheduled to run
void ShovelToggleCollect::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ShovelToggleCollect::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ShovelToggleCollect::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelToggleCollect::Interrupted()
{

}
