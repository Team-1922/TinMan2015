#include "Drive.h"

Drive::Drive(float time, float leftMag, float rightMag)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(driveTrain);
	m_magnitudeLeft = leftMag;
	m_magnitudeRight = rightMag;
	SetTimeout(time);
}

Drive::Drive(float time, float mag)
{
	Requires(driveTrain);
	m_magnitudeLeft = mag;
	m_magnitudeRight = mag;
	SetTimeout(time);
}

// Called just before this Command runs the first time
void Drive::Initialize()
{
	driveTrain->setLeft(m_magnitudeLeft);
	driveTrain->setRight(m_magnitudeRight);
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void Drive::End()
{
	driveTrain->StopMotors();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted()
{
	End();
}
