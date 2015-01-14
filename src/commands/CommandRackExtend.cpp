#include <commands/CommandRackFlat.h>

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

}

// Called repeatedly when this Command is scheduled to run
void CommandRackExtend::Execute()
{
	//start at half speed just in case
	rackMotor->setMotor(.5);
}

// Make this return true when this Command no longer needs to run execute()
bool CommandRackExtend::IsFinished()
{

	//test before potentiometer
	/*if(IsTimedOut())
		return true;
	else
		return false;*/


	if(rackMotor->getPotentiometer() >= 180)
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
