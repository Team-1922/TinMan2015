#include "DriveRotate.h"

DriveRotate::DriveRotate(float degrees) : m_angleDegrees(degrees)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(driveTrain);
}

// Called just before this Command runs the first time
void DriveRotate::Initialize()
{
	driveTrain->setIsRotating(true);
	//since it is going counter clockwise, the left wheels will have to move in the opposite direction, so subtract
	//to get the distance to set, take the circumference of the circle created by the middle drive wheels and take the percentage of the angle
	driveTrain->SetSetpoint(driveTrain->ReturnPIDInput() -
			(m_angleDegrees / 360.0f)*RobotMap::DriveTrain::middleDriveRotateCircumference);
}

// Called repeatedly when this Command is scheduled to run
void DriveRotate::Execute()
{
	//do nothing
}

// Make this return true when this Command no longer needs to run execute()
bool DriveRotate::IsFinished()
{
	return driveTrain->OnTarget();
}

// Called once after isFinished returns true
void DriveRotate::End()
{
	driveTrain->SetSetpoint(driveTrain->ReturnPIDInput());
	driveTrain->setIsRotating(false);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveRotate::Interrupted()
{
	End();
}
