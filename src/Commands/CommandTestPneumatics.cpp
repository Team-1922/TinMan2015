#include "CommandTestPneumatics.h"

CommandTestPneumatics::CommandTestPneumatics()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(pneumatics);

	SetTimeout(3);
}

// Called just before this Command runs the first time
void CommandTestPneumatics::Initialize()
{
	pneumatics->setSolenoid(1);

	SmartDashboard::PutBoolean("TestSolnoidSoftware", true);
}

// Called repeatedly when this Command is scheduled to run
void CommandTestPneumatics::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool CommandTestPneumatics::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void CommandTestPneumatics::End()
{
	pneumatics->setSolenoid(0);
	SmartDashboard::PutBoolean("TestSolnoidSoftware", false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandTestPneumatics::Interrupted()
{
	End();
}
