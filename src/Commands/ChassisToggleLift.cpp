#include "ChassisToggleLift.h"

ChassisToggleLift::ChassisToggleLift()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(chassis);
}

// Called just before this Command runs the first time
void ChassisToggleLift::Initialize()
{
	if(chassis->getSolenoid())
		chassis->setSolenoid(false);
	else
		chassis->setSolenoid(true);
}

// Called repeatedly when this Command is scheduled to run
void ChassisToggleLift::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ChassisToggleLift::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ChassisToggleLift::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ChassisToggleLift::Interrupted()
{

}
