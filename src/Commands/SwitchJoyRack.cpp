#include "SwitchJoyRack.h"

SwitchJoyRack::SwitchJoyRack()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void SwitchJoyRack::Initialize()
{
	RobotMap::Controls::currOpMode = OperatorMode::kRack;
}

// Called repeatedly when this Command is scheduled to run
void SwitchJoyRack::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool SwitchJoyRack::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void SwitchJoyRack::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SwitchJoyRack::Interrupted()
{

}
