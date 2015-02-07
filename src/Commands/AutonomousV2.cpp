#include "AutonomousV2.h"
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

AutonomousV2::AutonomousV2() : CommandGroup("AutonomousV2")
{
	AddSequential(new CommandRackRaise);
}
