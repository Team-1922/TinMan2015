#include "Autonomous.h"
#include "CommandRackDoNothing.h"
#include "CommandRackExtend.h"
#include "CommandRackFlat.h"
#include "CommandRackRaise.h"
#include "CommandShovelDump.h"
#include "CommandShovelGround.h"
#include "CommandShovelHuman.h"
#include "CommandShovelLift.h"
#include "CommandShovelStore.h"

#include <iostream>

Autonomous::Autonomous() : CommandGroup("Autonomous") {
	AddSequential(new CommandRackDoNothing());
}
