#include "CommandFlat.h"

CommandExtend::CommandExtend()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackMotor);

	//what should this be?
	SetTimeout(10);
}

// Called just before this Command runs the first time
void CommandExtend::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CommandExtend::Execute()
{
	//only do something if the arm is not in the extend position
	if(rackMotor.getPotentiometer() < 180)
	{
		//start at half speed just in case
		rackMotor.setMotor(.5);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CommandExtend::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CommandExtend::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandExtend::Interrupted()
{

}
