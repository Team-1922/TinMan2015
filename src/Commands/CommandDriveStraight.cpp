#include "CommandDriveStraight.h"

CommandDriveStraight::CommandDriveStraight()
{
	// Use Requires() here to declare subsystem dependencies
	 Requires(driveTrain);
	 SetTimeout(5);
}

// Called just before this Command runs the first time
void CommandDriveStraight::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CommandDriveStraight::Execute()
{
	driveTrain->DriveStraight(0.5);


}

// Make this return true when this Command no longer needs to run execute()
bool CommandDriveStraight::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void CommandDriveStraight::End()
{
	driveTrain->StopMotors();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandDriveStraight::Interrupted()
{
	End();
}
