#include "RackSetpointHere.h"
#include "../Subsystems/RackRotation.h"
#include "../Utilities.h"

RackSetpointHere::RackSetpointHere()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackRotation);
}

// Called just before this Command runs the first time
void RackSetpointHere::Initialize()
{
	rackRotation->SetSetpoint(rackRotation->GetPotVoltage());
}

// Called repeatedly when this Command is scheduled to run
void RackSetpointHere::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool RackSetpointHere::IsFinished()
{
	return !Utilities::isEqual(CommandBase::oi->GetOperatorThrottle(), 0.0f, 0.15f);
}

// Called once after isFinished returns true
void RackSetpointHere::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackSetpointHere::Interrupted()
{

}
