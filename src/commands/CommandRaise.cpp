#include "CommandFlat.h"

CommandRaise::ExampleCommand()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackMotor);

	//what should this be?
	SetTimeout(10);
}

// Called just before this Command runs the first time
void CommandRaise::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CommandRaise::Execute()
{
	//only do something if the arm is not in the raise position
	if(rackMotor.getPotentiometer() == 90)
		return;

	if(rackMotor.getPotentiometer() > 90) //past top
	{
		//start at half speed just in case
		rackMotor.setMotor(-.5);
	}
	else //before top
	{
		rackMotor.setMotor(.5);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CommandRaise::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CommandRaise::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandRaise::Interrupted()
{

}
