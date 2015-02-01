/*
 * ArcadeDrive.h
 *
 *  Created on: Jan 15, 2015
 *      Author: MikeCaplan
 */


#ifndef ArcadeDrive_H_
#define ArcadeDrive_H_

#include "../CommandBase.h"
#include "WPILib.h"

class ArcadeDrive: public CommandBase {
public:
	ArcadeDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};



#endif
