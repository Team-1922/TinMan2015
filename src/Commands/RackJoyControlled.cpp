#include "RackJoyControlled.h"

RackJoyControlled::RackJoyControlled()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackRotation);
}

// Called just before this Command runs the first time
void RackJoyControlled::Initialize()
{
	rackRotation->SetSetpoint(rackRotation->GetPotVoltage()); // try to hold it where it is current located (hopefully in the stored location)
	rackRotation->Enable();
}

// Called repeatedly when this Command is scheduled to run
void RackJoyControlled::Execute()
{
#if 0  // just try to get the rack rotating correctly at this time
	//in either case, the max rate is limited by the rack
	if(RobotMap::Controls::currOpMode == kRack || RobotMap::Controls::currOpMode == kBoth)
	{
		rack->setMotorRate(oi->GetOperatorJoystick()->GetY() * (float)RobotMap::Rack::rackMotorMaxSpeed);
	}
#endif

	// compute the amount of change that the operator is trying to making (a lot or a little).
	// then set the relative position forward
	if(RobotMap::Controls::currOpMode == kRack || RobotMap::Controls::currOpMode == kBoth)
	{
		double targetDelta = oi->GetOperatorJoystick()->GetY() * 0.25;

		double newRelativeLocation = rackRotation->GetPotVoltage() + targetDelta;

		// if the operator is trying to move the rack outside the range then we won't try to change the relative position - sort of a soft limit switch
		if (RobotMap::Rack::withinRotationRange(newRelativeLocation)) {
			rackRotation->SetSetpointRelative(targetDelta);
		}
	}
	else
	{
		rackRotation->SetSetpointRelative(0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RackJoyControlled::IsFinished()
{

	//for now, never quit, but this will change
	return false;
}

// Called once after isFinished returns true
void RackJoyControlled::End()
{
	// rack->setMotor(0.0f);
	rackRotation->SetSetpointRelative(0);//stop moving, but don't fall
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackJoyControlled::Interrupted()
{
	End();
}
