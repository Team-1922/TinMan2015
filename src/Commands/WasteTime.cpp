#include "WasteTime.h"

WasteTime::WasteTime(float howMuch)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	SetTimeout(howMuch);
}

// Called just before this Command runs the first time
void WasteTime::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void WasteTime::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool WasteTime::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void WasteTime::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WasteTime::Interrupted()
{

}
