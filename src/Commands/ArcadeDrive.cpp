/*
 * ArcadeDrive.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: MikeCaplan
 */

#include "ArcadeDrive.h"


ArcadeDrive::ArcadeDrive ()
{
	Requires(driveTrain);
}

void ArcadeDrive::Initialize()
{
}

void ArcadeDrive::Execute()
{
	driveTrain->ArcadeDrivePeriodic(oi->GetDriverJoystick());

}

void ArcadeDrive::Interrupted()
{
	End();
}

bool ArcadeDrive::IsFinished()
{
	return (false);

}

void ArcadeDrive::End()
{
	driveTrain->StopMotors();

}
