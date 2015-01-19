#include "Camera.h"
#include "../RobotMap.h"
#include "../Commands/CommandCameraStream.h"

Camera::Camera() :
		Subsystem("ExampleSubsystem")
{
    // create an image
	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	//the camera name (ex "cam0") can be found through the roborio web interface
	imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)imaqError) + "\n");
	}
	imaqError = IMAQdxConfigureGrab(session);
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxConfigureGrab error: " + std::to_string((long)imaqError) + "\n");
	}
}

Camera::~Camera()
{
}

void Camera::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new CommandCameraStream());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
