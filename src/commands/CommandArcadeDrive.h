/*
 * ArcadeDrive.h
 *
 *  Created on: Jan 15, 2015
 *      Author: MikeCaplan
 */


#ifndef COMMANDARCADEDRIVE_H_
#define COMMANDARCADEDRIVE_H_

#include "../CommandBase.h"
#include "WPILib.h"

class CommandArcadeDrive: public CommandBase {
public:
	CommandArcadeDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};



#endif
