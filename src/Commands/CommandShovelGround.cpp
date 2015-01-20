#include "CommandShovelGround.h"
#include "../Utilities.h"
#include "../RobotMap.h"

CommandShovelGround::CommandShovelGround()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shovel);
}

// Called just before this Command runs the first time
void CommandShovelGround::Initialize()
{
	float potAngle = shovel->getPotentiometer();

	if(potAngle > RobotMap::Shovel::groundAngle)
		shovel->setMotor(-.5);
	else
		shovel->setMotor(.5);
}

// Called repeatedly when this Command is scheduled to run
void CommandShovelGround::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool CommandShovelGround::IsFinished()
{
	if(Utilities::isEqual(RobotMap::Shovel::groundAngle, shovel->getPotentiometer(), 2))
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
