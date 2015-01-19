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
	~Camera();
	void InitDefaultCommand();

	IMAQdxSession 	getSession(){return session;	}
	Image*			getFrame()	{return frame;		}
	IMAQdxError 	getError()	{return imaqError;	}

};

#endif
