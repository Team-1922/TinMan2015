#include "CommandCameraStream.h"

CommandCameraStream::CommandCameraStream()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(camera);
}

// Called just before this Command runs the first time
void CommandCameraStream::Initialize()
{
    // acquire images
	IMAQdxStartAcquisition(session);
}

// Called repeatedly when this Command is scheduled to run
void CommandCameraStream::Execute()
{

	IMAQdxSession session 	= camera->getSession();
	Image *frame 			= camera->getFrame();
	IMAQdxError imaqError	= camera->getError();


    // grab an image, draw the circle, and provide it for the camera server which will
    // in turn send it to the dashboard.
	IMAQdxGrab(session, frame, true, NULL);
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
	} else {
		imaqDrawShapeOnImage(frame, frame, { 10, 10, 100, 100 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL, 0.0f);
		CameraServer::GetInstance()->SetImage(frame);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool CommandCameraStream::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CommandCameraStream::End()
{
    // stop image acquisition
	IMAQdxStopAcquisition(camera->getSession());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CommandCameraStream::Interrupted()
{

}
