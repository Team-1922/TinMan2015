#include "ShovelJoyControlled.h"
#include "Utilities.h"

ShovelJoyControlled::ShovelJoyControlled()
{
	Requires(shovelRotation);
}

// Called just before this Command runs the first time
void ShovelJoyControlled::Initialize()
{
	shovelRotation->Enable();
}

// Called repeatedly when this Command is scheduled to run
void ShovelJoyControlled::Execute()
{
	shovelRotation->SetSetpoint(oi->GetOperatorJoystick()->GetY());
}

// Make this return true when this Command no longer needs to run execute()
bool ShovelJoyControlled::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ShovelJoyControlled::End()
{
	shovelRotation->SetSetpoint(0);//stop moving, but don't fall
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelJoyControlled::Interrupted()
{
	End();
}
