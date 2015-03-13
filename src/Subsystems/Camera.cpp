#include "Camera.h"
#include "../RobotMap.h"
#include "../Commands/CameraStream.h"

Camera::Camera() :
		Subsystem("Camera")
{
	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	//the camera name (ex "cam0") can be found through the roborio web interface
#ifdef COMP_BOT
	imaqError = IMAQdxOpenCamera("cam1", IMAQdxCameraControlModeController, &session);
#else
	imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
#endif
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)imaqError) + "\n");
	}
	imaqError = IMAQdxConfigureGrab(session);
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxConfigureGrab error: " + std::to_string((long)imaqError) + "\n");
	}
}

void Camera::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new CameraStream());
}

void Camera::DrawOverlay()
{
	IMAQdxGrab(session, frame, true, NULL);
	if(imaqError != IMAQdxErrorSuccess) {
		//DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
	} else {
		imaqDrawLineOnImage(frame, frame, DrawMode::IMAQ_DRAW_VALUE, RobotMap::Camera::topLeft, 		RobotMap::Camera::topRight, 	RobotMap::Camera::rectColor);
		imaqDrawLineOnImage(frame, frame, DrawMode::IMAQ_DRAW_VALUE, RobotMap::Camera::topRight, 		RobotMap::Camera::bottomRight, 	RobotMap::Camera::rectColor);
		imaqDrawLineOnImage(frame, frame, DrawMode::IMAQ_DRAW_VALUE, RobotMap::Camera::bottomRight, 	RobotMap::Camera::bottomLeft, 	RobotMap::Camera::rectColor);
		imaqDrawLineOnImage(frame, frame, DrawMode::IMAQ_DRAW_VALUE, RobotMap::Camera::bottomLeft, 		RobotMap::Camera::topLeft, 		RobotMap::Camera::rectColor);

		imaqDrawLineOnImage(frame, frame, DrawMode::IMAQ_DRAW_VALUE, RobotMap::Camera::maxTopLeft, 		RobotMap::Camera::maxTopRight, 		RobotMap::Camera::maxRectColor);
		imaqDrawLineOnImage(frame, frame, DrawMode::IMAQ_DRAW_VALUE, RobotMap::Camera::maxTopRight, 	RobotMap::Camera::maxBottomRight, 	RobotMap::Camera::maxRectColor);
		imaqDrawLineOnImage(frame, frame, DrawMode::IMAQ_DRAW_VALUE, RobotMap::Camera::maxBottomRight, 	RobotMap::Camera::maxBottomLeft, 	RobotMap::Camera::maxRectColor);
		imaqDrawLineOnImage(frame, frame, DrawMode::IMAQ_DRAW_VALUE, RobotMap::Camera::maxBottomLeft, 	RobotMap::Camera::maxTopLeft, 		RobotMap::Camera::maxRectColor);
		CameraServer::GetInstance()->SetImage(frame);
	}
}

void Camera::StartAcquisition()
{
    // acquire images
	IMAQdxStartAcquisition(session);
}

void Camera::StopAcquisition()
{
    // stop image acquisition
	IMAQdxStopAcquisition(session);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
