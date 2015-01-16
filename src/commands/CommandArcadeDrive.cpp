/*
 * CommandArcadeDrive.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: MikeCaplan
 */

#include "CommandArcadeDrive.h"


CommandArcadeDrive::CommandArcadeDrive ()
{
	Requires(driveTrain);
}

void CommandArcadeDrive::Initialize()
{
}

void CommandArcadeDrive::Execute()
{
	driveTrain->ArcadeDrive(oi->GetJoystick());

}

void CommandArcadeDrive::Interrupted()
{
	End();
}

bool CommandArcadeDrive::IsFinished()
{
	return (false);

}

void CommandArcadeDrive::End()
{
	driveTrain->StopMotors();

}
