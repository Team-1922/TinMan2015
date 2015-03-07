#include "ShovelSuckWheels.h"

ShovelSuckWheels::ShovelSuckWheels(float time, float leftVal, float rightVal)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shovel);
	this->m_magnitudeLeft = leftVal;
	this->m_magnitudeRight = rightVal;
	SetTimeout(time);
}

ShovelSuckWheels::ShovelSuckWheels(float time, float magnitude)
{
	Requires(shovel);
	m_magnitudeLeft = magnitude;
	m_magnitudeRight = magnitude;
	SetTimeout(time);
}

// Called just before this Command runs the first time
void ShovelSuckWheels::Initialize()
{
	shovel->SetSuckWheelLeft(m_magnitudeLeft);
	shovel->SetSuckWheelRight(m_magnitudeRight);
}

// Called repeatedly when this Command is scheduled to run
void ShovelSuckWheels::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ShovelSuckWheels::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void ShovelSuckWheels::End()
{
	shovel->SetSuckWheels(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShovelSuckWheels::Interrupted()
{
	End();
}
