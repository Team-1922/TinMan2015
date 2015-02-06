#include "RackJoyControlled.h"

RackJoyControlled::RackJoyControlled()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rack);
}

// Called just before this Command runs the first time
void RackJoyControlled::Initialize()
{
	rack->resetEncoder();
}

// Called repeatedly when this Command is scheduled to run
void RackJoyControlled::Execute()
{
	//in either case, the max rate is limited by the rack
	if(RobotMap::Controls::currOpMode == kRack || RobotMap::Controls::currOpMode == kBoth)
	{
		rack->setMotorRate(oi->GetOperatorJoystick()->GetY() * (float)RobotMap::Rack::rackMotorMaxSpeed);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RackJoyControlled::IsFinished()
{

	//for now, never quit, but this will change
	return false;
}

// Called once after isFinished returns true
void RackJoyControlled::End()
{
	rack->setMotor(0.0f);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackJoyControlled::Interrupted()
{
	End();
}
