#include "Autonomous.h"
#include "DriveStraight.h"
#include <iostream>

Autonomous::Autonomous() : CommandGroup("Autonomous")
{
	AddSequential(new DriveStraight(0.55f, 0.75f));
}
