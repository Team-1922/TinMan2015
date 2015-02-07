#include "SwitchJoyShovel.h"

SwitchJoyShovel::SwitchJoyShovel()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void SwitchJoyShovel::Initialize()
{
	RobotMap::Controls::currOpMode = OperatorMode::kShovel;
}

// Called repeatedly when this Command is scheduled to run
void SwitchJoyShovel::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool SwitchJoyShovel::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void SwitchJoyShovel::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SwitchJoyShovel::Interrupted()
{

}
