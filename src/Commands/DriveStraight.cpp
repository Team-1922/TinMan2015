#include "DriveStraight.h"

DriveStraight::DriveStraight(float time, float throttle):
m_time(time), m_throttle(throttle)
{
	// Use Requires() here to declare subsystem dependencies
	 Requires(driveTrain);
	 SetTimeout(time);
}

// Called just before this Command runs the first time
void DriveStraight::Initialize()
{
	driveTrain->DriveStraight(m_throttle);
}

// Called repeatedly when this Command is scheduled to run
void DriveStraight::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void DriveStraight::End()
{
	driveTrain->StopMotors();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted()
{
	End();
}
