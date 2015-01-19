#ifndef CommandCameraStream_H
#define CommandCameraStream_H

#include "../CommandBase.h"
#include "WPILib.h"

class CommandCameraStream: public CommandBase
{
public:
	CommandCameraStream();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
