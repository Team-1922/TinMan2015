#ifndef DriveStraight_H
#define DriveStraight_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveStraight: public CommandBase
{
private:
	float m_time;
	float m_throttle;
public:
	DriveStraight(float time, float throttle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
