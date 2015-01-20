#include "CommandRackExtend.h"
#include "../Utilities.h"
#include "../RobotMap.h"

CommandRackExtend::CommandRackExtend() :
	CommandBase("CommandExtend")
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackMotor);

	//testing before potentiometer
	//SetTimeout(3);
}

// Called just before this Command runs the first time
void CommandRackExtend::Initialize()
{

	float angle = rackMotor->getPotentiometer();


	if(angle > RobotMap::Rack::extendAngle) //past top
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
void CommandRackExtend::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool CommandRackExtend::IsFinished()
{
	float angle = rackMotor->getPotentiometer();

	//within a 5 degree threshold
	if(Utilities::isEqual(RobotMap::Rack::extendAngle, angle, 5.0f))
		return true;
	else
		return false;
}

// Called once after isFinished returns true
void CommandRackExtend::End()
{
	rackMotor->setMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandRackExtend::Interrupted()
{
	End();
}
