#include "Autonomous.h"
#include "ShovelDoNothing.h"
#include <iostream>

Autonomous::Autonomous() : CommandGroup("Autonomous")
{
	AddSequential(new ShovelDoNothing());
}
