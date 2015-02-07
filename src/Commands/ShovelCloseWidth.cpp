#include "ShovelCloseWidth.h"

ShovelCloseWidth::ShovelCloseWidth()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shovel);
}

// Called just before this Command runs the first time
void ShovelCloseWidth::Initialize()
{
	shovel->extendShelf();
}

// Called repeatedly when this Command is scheduled to run
void ShovelCloseWidth::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ShovelCloseWidth::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ShovelCloseWidth::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelCloseWidth::Interrupted()
{

}
