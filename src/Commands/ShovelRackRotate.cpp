#include "ShovelRackRotate.h"
#include "../subsystems/RackRotation.h"


ShovelRackRotate::ShovelRackRotate(double setPoint)
: m_setPoint(setPoint)
{
	Requires(shovelRotation);
	Requires(rackRotation);
}

// Called just before this Command runs the first time
void ShovelRackRotate::Initialize()
{
	// assume that the shovel is already in the right position - if it is not bad things will happen
	rackRotation->SetSetpoint(m_setPoint);
	rackRotation->Enable();
	shovelRotation->Enable();
}

// Called repeatedly when this Command is scheduled to run
void ShovelRackRotate::Execute()
{
	// update the shovel position at this location whenever execute is called. this way we slave the shovel to the rack
	// location - if we don't do it here then one could get ahead of the other
	shovelRotation->SetSetpoint(rackRotation->GetPotVoltage() - RobotMap::Shovel::pot90DegreeVoltage);
}

// Make this return true when this Command no longer needs to run execute()
bool ShovelRackRotate::IsFinished()
{
	return rackRotation->OnTarget();
}

// Called once after isFinished returns true
void ShovelRackRotate::End()
{
	rackRotation->Disable();
	shovelRotation->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelRackRotate::Interrupted()
{
	End();
}
