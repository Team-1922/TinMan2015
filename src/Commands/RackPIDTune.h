#ifndef RackPIDTune_H
#define RackPIDTune_H

#include "../CommandBase.h"
#include "WPILib.h"

class RackPIDTune: public CommandBase
{
	char m_letter;
	float m_delta;
public:
	RackPIDTune(char ch, float delta);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
