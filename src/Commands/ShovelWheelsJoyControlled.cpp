#include "ShovelWheelsJoyControlled.h"

ShovelWheelsJoyControlled::ShovelWheelsJoyControlled()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shovel);
}

// Called just before this Command runs the first time
void ShovelWheelsJoyControlled::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ShovelWheelsJoyControlled::Execute()
{
	shovel->SetSuckWheels(oi->GetOperatorJoystick()->GetY());
}

// Make this return true when this Command no longer needs to run execute()
bool ShovelWheelsJoyControlled::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ShovelWheelsJoyControlled::End()
{
	shovel->SetSuckWheels(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelWheelsJoyControlled::Interrupted()
{
	End();
}
