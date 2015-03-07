#ifndef Camera_H
#define Camera_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Camera: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	IMAQdxSession session;
	Image *frame;
	IMAQdxError imaqError;
public:
	Camera();
	void InitDefaultCommand();

	void DrawOverlay();
	void StartAcquisition();
	void StopAcquisition();
};

#endif
