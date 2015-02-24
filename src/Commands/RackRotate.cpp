#include "RackRotate.h"

RackRotate::RackRotate(double setPoint, bool holdPosition)
: m_setPoint(setPoint), m_holdPosition(holdPosition)
{
	Requires(rackRotation);
}

// Called just before this Command runs the first time
void RackRotate::Initialize()
{
	rackRotation->SetSetpoint(m_setPoint);
	rackRotation->Enable();
}

// Called repeatedly when this Command is scheduled to run
void RackRotate::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool RackRotate::IsFinished()
{
	return rackRotation->OnTarget();
}

// Called once after isFinished returns true
void RackRotate::End()
{
	//rackRotation->SetSetpointRelative(0);
	if(!m_holdPosition)
		rackRotation->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackRotate::Interrupted()
{
	End();
}
