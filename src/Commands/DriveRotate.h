#ifndef DriveRotate_H
#define DriveRotate_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveRotate: public CommandBase
{
	float m_angleDegrees;
public:
	//positive is counter-clockwise relative to bird's eye view
	DriveRotate(float degrees);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
