#include "CommandRackFlat.h"
#include "../Utilities.h"
#include "../RobotMap.h"

CommandRackFlat::CommandRackFlat() :
	CommandBase("CommandFlat")
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackMotor);
}

// Called just before this Command runs the first time
void CommandRackFlat::Initialize()
{
	float angle = rackMotor->getPotentiometer();


	if(angle > RobotMap::Rack::flatAngle) //past top
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
void CommandRackFlat::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool CommandRackFlat::IsFinished()
{
	float angle = rackMotor->getPotentiometer();

	//if the rack is coming in towards the positive direction, then make sure it hasn't gone too far
	// but if the rack is coming towards the negative direction, make sure it hasn't gone too far in that direction
	if(angle > RobotMap::Rack::flatAngle)//the potentiometer is too far in the positive direction
		if(Utilities::getSign(rackMotor->getMotor()))//the motor is going in the positive direction
			return true;//therefore stop
		else
			return false;
	else //the potentiometer is too far in the negative direction
		if(!Utilities::getSign(rackMotor->getMotor()))//the motor is going in the negative direction
			return true;//therefore stop
		else
			return false;
}

// Called once after isFinished returns true
void CommandRackFlat::End()
{
	rackMotor->setMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandRackFlat::Interrupted()
{
	End();
}
