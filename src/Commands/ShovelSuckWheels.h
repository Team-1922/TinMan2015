#ifndef ShovelSuckWheels_H
#define ShovelSuckWheels_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShovelSuckWheels: public CommandBase
{
	float m_magnitudeLeft;
	float m_magnitudeRight;
public:
	ShovelSuckWheels(float time, float magnitudeLeft, float magnitudeRight);
	ShovelSuckWheels(float time, float magnitude);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
