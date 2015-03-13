#include "ShovelWheelsJoyControlled.h"
#include "Utilities.h"

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
	//y axis movement takes priority over twist
	float joyTwist = oi->GetOperatorJoystick()->GetTwist();
	float joyYAxis = oi->GetOperatorJoystick()->GetY();

	if(Utilities::isEqual(joyYAxis, 0.0f, 0.55f))
	{
		if(!Utilities::isEqual(joyTwist, 0.0f, 0.90f))
			shovel->RotateTote(joyTwist);
		else
			shovel->SetSuckWheels(0);
	}
	else
	{
		shovel->SetSuckWheels(joyYAxis);
	}
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
