#ifndef Drive_H
#define Drive_H

#include "../CommandBase.h"
#include "WPILib.h"

class Drive: public CommandBase
{
	float m_magnitudeLeft;
	float m_magnitudeRight;
public:
	Drive(float time, float leftVal, float rightVal);
	Drive(float time, float magnitude);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
