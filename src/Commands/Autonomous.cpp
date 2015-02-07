#include "Autonomous.h"
#include "RackDoNothing.h"

#include <iostream>

Autonomous::Autonomous() : CommandGroup("Autonomous")
{
	AddSequential(new RackDoNothing());
}
