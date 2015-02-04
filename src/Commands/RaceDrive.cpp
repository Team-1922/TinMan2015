#include "RaceDrive.h"

RaceDrive::RaceDrive()
{
	Requires(driveTrain);
}

// Called just before this Command runs the first time
void RaceDrive::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RaceDrive::Execute()
{
	driveTrain->RaceDrivePeriodic(oi->GetDriverController());
}

// Make this return true when this Command no longer needs to run execute()
bool RaceDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RaceDrive::End()
{
	driveTrain->StopMotors();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaceDrive::Interrupted()
{
	End();
}
