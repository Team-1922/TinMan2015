#ifndef CameraStream_H
#define CameraStream_H

#include "../CommandBase.h"
#include "WPILib.h"

class CameraStream: public CommandBase
{
public:
	CameraStream();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
