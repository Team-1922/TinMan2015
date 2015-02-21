#include "TestCommandGroup.h"
#include "RackDoNothing.h"
#include "DriveStraight.h"


#include "ShovelRotate.h"
#include "ChassisToggleLift.h"
#include "ShovelToggleWidth.h"
#include "ShovelRackRotate.h"
#include "StackTotes.h"
#include "ChassisLift.h"
#include "ShovelCloseWidth.h"
#include "ShovelOpenWidth.h"
#include "ShovelRackRotate.h"

#include <iostream>


StackTotes::StackTotes()
{
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.

	//AddParallel(new TestPneumatics());
	//AddParallel(new DriveStraight());
	//AddParallel(new CommandRackExtend());

	// rotate the shovel to the storage position
	AddSequential(new ShovelCloseWidth());

	// rotate the shovel to the storage position
	AddSequential(new ShovelRotate(RobotMap::Shovel::voltageDump));

	// lift the bot  IMPORTANT - need to lift the bot first because the shovel will be rotated past flat
	AddSequential(new ChassisLift(true));

	// rotate the rack and the shovel
	AddSequential(new ShovelRackRotate(RobotMap::Rack::voltageStack));

	// retract the shovel supports and drop the totes onto the platform
	AddSequential(new ShovelOpenWidth());

	// rotate the shovel back to horizontal
	AddSequential(new ShovelRotate(RobotMap::Shovel::voltageFlat));

	// drop the bot
	AddSequential(new ChassisLift(false));






}
