#include "RackPIDTune.h"

RackPIDTune::RackPIDTune(char ch, float delta)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(rackRotation);
	m_letter = ch;
	m_delta = delta;
}

// Called just before this Command runs the first time
void RackPIDTune::Initialize()
{
	if(m_letter == 'P')
	{
		rackRotation->SetP(rackRotation->GetP() + m_delta);
	}
	else if(m_letter == 'I')
	{
		rackRotation->SetI(rackRotation->GetI() + m_delta);
	}
	else if(m_letter == 'D')
	{
		rackRotation->SetD(rackRotation->GetD() + m_delta);
	}
}

// Called repeatedly when this Command is scheduled to run
void RackPIDTune::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool RackPIDTune::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void RackPIDTune::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RackPIDTune::Interrupted()
{

}
