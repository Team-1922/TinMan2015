#include "RackExtend.h"

RackExtend::RackExtend()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(rack);
}

// Called just before this Command runs the first time
void RackExtend::Initialize()
{
	rack->setExtendMotor(0.5f);
}

// Called repeatedly when this Command is scheduled to run
void RackExtend::Execute()
{
	//monitor limit switch?
}

// Make this return true when this Command no longer needs to run execute()
bool RackExtend::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RackExtend::End()
{
	rack->setExtendMotor(0.0f);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackExtend::Interrupted()
{
	End();
}
