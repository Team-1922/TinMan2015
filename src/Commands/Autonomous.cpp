#include "Autonomous.h"
#include "DriveStraight.h"
#include <iostream>

Autonomous::Autonomous() : CommandGroup("Autonomous")
{
	AddSequential(new DriveStraight(2.0f, 0.5f));
}
