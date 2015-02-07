#include "AutonomousV2.h"
#include "RackDoNothing.h"

#include <iostream>

AutonomousV2::AutonomousV2() : CommandGroup("AutonomousV2")
{
	AddSequential(new RackDoNothing);
}
