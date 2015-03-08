#include "DriveDistance.h"

DriveDistance::DriveDistance(float distance)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(driveTrain);

	m_distanceInches = distance;
}

// Called just before this Command runs the first time
void DriveDistance::Initialize()
{
	//set the setpoint to the distance relative to the current position
	driveTrain->SetSetpoint(driveTrain->getEncDistanceLeft() + m_distanceInches);
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute()
{
	//do nothing
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished()
{
	return driveTrain->OnTarget();
}

// Called once after isFinished returns true
void DriveDistance::End()
{
	driveTrain->SetSetpoint(driveTrain->ReturnPIDInput());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted()
{
	End();
}
