#include "RackRetract.h"

RackRetract::RackRetract()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rack);
}

// Called just before this Command runs the first time
void RackRetract::Initialize()
{
	//Rack->setMotor(-.5);
}

// Called repeatedly when this Command is scheduled to run
void RackRetract::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool RackRetract::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void RackRetract::End()
{
	//Rack->setMotor(.5);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackRetract::Interrupted()
{
	//End();
}
