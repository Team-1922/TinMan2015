#include "ShovelJoyControlled.h"
#include "Utilities.h"

ShovelJoyControlled::ShovelJoyControlled()
{
	Requires(shovelRotation);
}

// Called just before this Command runs the first time
void ShovelJoyControlled::Initialize()
{
	shovelRotation->SetSetpoint(shovelRotation->GetPotVoltage()); // try to hold it where it is current located (hopefully in the stored location)
	shovelRotation->Enable();
}

// Called repeatedly when this Command is scheduled to run
void ShovelJoyControlled::Execute()
{
#if 0
	if(RobotMap::Controls::currOpMode == kShovel)
	{
		shovel->setMotorRate(oi->GetOperatorJoystick()->GetY() * (float)RobotMap::Shovel::shovelMotorMaxSpeed);
	}
	else if(RobotMap::Controls::currOpMode == kBoth)
	{
		//when using both, make sure to set the limit to the one with the lower max speed
		shovel->setMotorRate(oi->GetOperatorJoystick()->GetY() * (float)RobotMap::Rack::rackMotorMaxSpeed);
	}
#endif

	// compute the amount of change that the operator is trying to making (a lot or a little).
	// then set the relative position forward
	double targetDelta = 0;
	float joyYVal = oi->GetOperatorJoystick()->GetY();
	if(fabs(joyYVal) > 0.1f)
		targetDelta = joyYVal * 0.25;

	if(RobotMap::Controls::currOpMode == kShovel && fabs(joyYVal) > 0.0f)
	{
		double newRelativeLocation = shovelRotation->GetPotVoltage() + targetDelta;

		// if the operator is trying to move the shovel outside the range then we won't try to change the relative position - sort of a soft limit switch
		if (RobotMap::Shovel::withinRotationRange(newRelativeLocation)) {
			shovelRotation->SetSetpoint(shovelRotation->GetPotVoltage() + targetDelta);
		}

	}
	else if(RobotMap::Controls::currOpMode == kRack || fabs(joyYVal) > 0.1f)
	{
		rackRotation->SetSetpointRelative(0);
	}
	else if(RobotMap::Controls::currOpMode == kBoth)
	{
		//this is the SLAVE
		//rackRotation->SetSetpointRelative(targetDelta);

		double newLocation = rackRotation->GetPotVoltage() + RobotMap::Shovel::pot90DegreeVoltageFromRack;

		if (RobotMap::Shovel::withinRotationRange(newLocation))
		{
			//flip the sign because the potentiometers are going opposite directions
			shovelRotation->SetSetpoint(newLocation);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShovelJoyControlled::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ShovelJoyControlled::End()
{
	shovelRotation->SetSetpointRelative(0);//stop moving, but don't fall
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelJoyControlled::Interrupted()
{
	End();
}
