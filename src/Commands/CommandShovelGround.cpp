#include "CommandShovelGround.h"
#include "../Utilities.h"

CommandShovelGround::CommandShovelGround()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shovel);
}

// Called just before this Command runs the first time
void CommandShovelGround::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CommandShovelGround::Execute()
{
	float potAngle = shovel->getPotentiometer();

	if(potAngle < 0)
		shovel->setMotor(-.5);
	else
		shovel->setMotor(.5);
}

// Make this return true when this Command no longer needs to run execute()
bool CommandShovelGround::IsFinished()
{
	if(Utilities::isEqual(0, shovel->getPotentiometer(), 2))
		return true;
	else
		return false;
}

// Called once after isFinished returns true
void CommandShovelGround::End()
{
	shovel->setMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandShovelGround::Interrupted()
{
	End();
}
