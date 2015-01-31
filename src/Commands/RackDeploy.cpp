#include "RackDeploy.h"

RackDeploy::RackDeploy()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackMotor);
}

// Called just before this Command runs the first time
void RackDeploy::Initialize()
{
	rackMotor->setMotor(.5);
}

// Called repeatedly when this Command is scheduled to run
void RackDeploy::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool RackDeploy::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RackDeploy::End()
{
	rackMotor->setMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackDeploy::Interrupted()
{
	End();
}
