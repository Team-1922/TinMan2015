#include "ShovelRotate.h"

ShovelRotate::ShovelRotate(double setPoint, bool holdPosition)
: m_setPoint(setPoint), m_holdPosition(holdPosition)
{
	Requires(shovelRotation);
}

// Called just before this Command runs the first time
void ShovelRotate::Initialize()
{
	shovelRotation->SetSetpoint(m_setPoint);
	shovelRotation->Enable();
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
	if(!m_holdPosition)
		shovelRotation->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelRotate::Interrupted()
{
	End();
}
