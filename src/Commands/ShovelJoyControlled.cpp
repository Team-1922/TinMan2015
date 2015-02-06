#include "ShovelJoyControlled.h"

ShovelJoyControlled::ShovelJoyControlled()
{
	Requires(shovel);
}

// Called just before this Command runs the first time
void ShovelJoyControlled::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ShovelJoyControlled::Execute()
{
	if(RobotMap::Controls::currOpMode == kShovel)
	{
		shovel->setMotorRate(oi->GetOperatorJoystick()->GetY() * (float)RobotMap::Shovel::shovelMotorMaxSpeed);
	}
	else if(RobotMap::Controls::currOpMode == kBoth)
	{
		//when using both, make sure to set the limit to the one with the lower max speed
		shovel->setMotorRate(oi->GetOperatorJoystick()->GetY() * (float)RobotMap::Rack::rackMotorMaxSpeed);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShovelJoyControlled::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ShovelJoyControlled::End()
{
	shovel->setMotor(0.0f);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelJoyControlled::Interrupted()
{
	End();
}
