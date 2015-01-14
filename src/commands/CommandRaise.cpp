#include "CommandFlat.h"
#include "../Utilities.h"

CommandRaise::CommandRaise() :
	CommandBase("CommandRaise")
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackMotor);
}

// Called just before this Command runs the first time
void CommandRaise::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CommandRaise::Execute()
{

	float angle = rackMotor->getPotentiometer();


	if(angle > 90) //past top
	{
		//start at half speed just in case
		rackMotor->setMotor(-.5);
	}
	else //before top
	{
		rackMotor->setMotor(.5);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CommandRaise::IsFinished()
{
	float angle = rackMotor->getPotentiometer();

	//within a 5 degree threshold
	if(Utilities::isEqual(90, angle, 5))
		return true;
	else
		return false;
}

// Called once after isFinished returns true
void CommandRaise::End()
{
	rackMotor->setMotor(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandRaise::Interrupted()
{
	End();
}
