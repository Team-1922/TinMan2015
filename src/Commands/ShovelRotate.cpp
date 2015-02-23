#include "ShovelRotate.h"
#include "Utilities.h"

ShovelRotate::ShovelRotate(double setPoint)
: m_setPoint(setPoint)
{
	Requires(shovelRotation);
}

// Called just before this Command runs the first time
void ShovelRotate::Initialize()
{
	shovelRotation->SetSetpoint(m_setPoint);
}

// Called repeatedly when this Command is scheduled to run
void ShovelRotate::Execute()
{
//	shovelRotation->enable();
}

// Make this return true when this Command no longer needs to run execute()
bool ShovelRotate::IsFinished()
{
	return shovelRotation->OnTarget();
//	return shovelRotation->onTarget();
}

// Called once after isFinished returns true
void ShovelRotate::End()
{
	shovelRotation->SetSetpointRelative(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelRotate::Interrupted()
{
	End();
}
