#include "CameraStream.h"

CameraStream::CameraStream()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(camera);
}

// Called just before this Command runs the first time
void CameraStream::Initialize()
{
	camera->StartAcquisition();
}

// Called repeatedly when this Command is scheduled to run
void CameraStream::Execute()
{
	camera->DrawOverlay();
}

// Make this return true when this Command no longer needs to run execute()
bool CameraStream::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CameraStream::End()
{
	camera->StopAcquisition();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CameraStream::Interrupted()
{
	End();
}
