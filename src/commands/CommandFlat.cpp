#include "CommandFlat.h"

CommandFlat::CommandFlat()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackMotor);

	//what should this be?
	SetTimeout(10);
}

// Called just before this Command runs the first time
void CommandFlat::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CommandFlat::Execute()
{
	//only do something if the arm is not in the flat position
	if(rackMotor.getPotentiometer() > 0)
	{
		//start at half speed just in case
		rackMotor.setMotor(-.5);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CommandFlat::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CommandFlat::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandFlat::Interrupted()
{

}
