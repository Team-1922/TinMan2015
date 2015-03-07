#include "TestCommandGroup.h"
#include "RackDoNothing.h"
#include "DriveStraight.h"


#include "ShovelRotate.h"
//#include "ChassisToggleLift.h"
#include "ShovelToggleWidth.h"
#include "ShovelRackRotate.h"
#include "StackTotes.h"
//#include "ChassisLift.h"
#include "ShovelCloseWidth.h"
#include "ShovelOpenWidth.h"
#include "ShovelRackRotate.h"
#include "RackRotate.h"

#include <iostream>


StackTotes::StackTotes()
{
	// rotate the shovel to the storage position
	AddSequential(new ShovelCloseWidth());

	// rotate the shovel to the storage position
	AddSequential(new ShovelRotate(RobotMap::Shovel::voltageDump));

	// lift the bot  IMPORTANT - need to lift the bot first because the shovel will be rotated past flat
	//TODO: undo this AddSequential(new ChassisLift(true));

	// rotate the rack and the shovel
	AddSequential(new ShovelRackRotate(RobotMap::Rack::voltageStack));

	// retract the shovel supports and drop the totes onto the platform
	AddSequential(new ShovelOpenWidth());

	// rotate the shovel back to horizontal, and the rack back to flat
	AddSequential(new ShovelRotate(RobotMap::Shovel::voltageFlat));
	AddSequential(new RackRotate(RobotMap::Rack::voltageDump));

	// drop the bot
	//AddSequential(new ChassisLift(false));
}
