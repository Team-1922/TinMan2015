#include "CommandRackRaise.h"
#include "../Utilities.h"
#include "../RobotMap.h"

CommandRackRaise::CommandRackRaise() :
	CommandBase("CommandRackRaise")
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackMotor);
}

// Called just before this Command runs the first time
void CommandRackRaise::Initialize()
{

	float angle = rackMotor->getPotentiometer();


	if(angle > RobotMap::Rack::raiseAngle) //past top
	{
		//start at half speed just in case
		rackMotor->setMotor(-.5);
	}
	else //before top
	{
		rackMotor->setMotor(.5);
	}
}

// Called repeatedly when this Command is scheduled to run
void CommandRackRaise::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool CommandRackRaise::IsFinished()
{
	float angle = rackMotor->getPotentiometer();

	//within a 5 degree threshold
	if(Utilities::isEqual(RobotMap::Rack::raiseAngle, angle, 5.0f))
		return true;
	else
		return false;
}

// Called once after isFinished returns true
void CommandRackRaise::End()
{
	rackMotor->setMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandRackRaise::Interrupted()
{
	End();
}
