#include "ShovelToggleWidth.h"

ShovelToggleWidth::ShovelToggleWidth()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shovel);
}

// Called just before this Command runs the first time
void ShovelToggleWidth::Initialize()
{
	if(shovel->getSolenoid())
		shovel->setSolenoid(false);
	else
		shovel->setSolenoid(true);
}

// Called repeatedly when this Command is scheduled to run
void ShovelToggleWidth::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ShovelToggleWidth::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ShovelToggleWidth::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelToggleWidth::Interrupted()
{

}
