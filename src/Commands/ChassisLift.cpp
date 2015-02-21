#include "ChassisLift.h"

ChassisLift::ChassisLift(bool lift)
: m_lift (lift)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(chassis);
}

// Called just before this Command runs the first time
void ChassisLift::Initialize()
{
	chassis->setSolenoid(m_lift);
}

// Called repeatedly when this Command is scheduled to run
void ChassisLift::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ChassisLift::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ChassisLift::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ChassisLift::Interrupted()
{

}
