#include "ShovelRackRotate.h"
#include "Utilities.h"
#include "../Subsystems/RackRotation.h"
#include "../Subsystems/ShovelRotation.h"


ShovelRackRotate::ShovelRackRotate(double rackSetpoint)
: m_rackSetpoint(rackSetpoint)
{
	Requires(shovelRotation);
	Requires(rackRotation);
}

// Called just before this Command runs the first time
void ShovelRackRotate::Initialize()
{
	// assume that the shovel is already in the right position - if it is not bad things will happen
	rackRotation->SetSetpoint(m_rackSetpoint);
	//shovelRotation->SetSetpoint(m_shovelSetpoint);
	rackRotation->Enable();
	shovelRotation->Enable();
}

// Called repeatedly when this Command is scheduled to run
void ShovelRackRotate::Execute()
{
	// update the shovel position at this location whenever execute is called. this way we slave the shovel to the rack
	// location - if we don't do it here then one could get ahead of the other; HA: REMEMBER THE 90 degree offset (i.e. 1 volt), subtract, because we are entering the RACK angle
	shovelRotation->SetSetpoint(Utilities::getShovelSetpointFromRackVoltage(rackRotation->GetPotVoltage() - RobotMap::Shovel::pot90DegreeVoltageFromRack));
}

// Make this return true when this Command no longer needs to run execute()
bool ShovelRackRotate::IsFinished()
{
	return rackRotation->OnTarget();
}

// Called once after isFinished returns true
void ShovelRackRotate::End()
{
	//DON"T disable, because we DO want to keep both of the objects supported
	//rackRotation->Disable();
	//shovelRotation->Disable();

	//if this is interrupted, then make sure it stops where it is
	shovelRotation->SetSetpoint(shovelRotation->GetPotVoltage());
	rackRotation->SetSetpoint(rackRotation->GetPotVoltage());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelRackRotate::Interrupted()
{
	End();
}
