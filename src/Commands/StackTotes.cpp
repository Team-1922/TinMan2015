#include "TestCommandGroup.h"
#include "RackDoNothing.h"
#include "DriveStraight.h"


#include "ShovelRotate.h"
//#include "ChassisToggleLift.h"
#include "ShovelToggleGrab.h"
#include "ShovelRackRotate.h"
#include "StackTotes.h"
//#include "ChassisLift.h"
#include "ShovelSetGrab.h"
//#include "ShovelSetCollect.h"
#include "ShovelRackRotate.h"
#include "RackRotate.h"

#include <iostream>


StackTotes::StackTotes()
{
	// rotate the shovel to the storage position
	AddSequential(new ShovelSetGrab(true));

	//AddSequential(new ShovelSetCollect(true));

	// rotate the shovel to the storage position
	AddSequential(new ShovelRotate(RobotMap::Shovel::voltageDump + 0.1f));

	// lift the bot  IMPORTANT - need to lift the bot first because the shovel will be rotated past flat
	//TODO: undo this AddSequential(new ChassisLift(true));

	// rotate the rack and the shovel
	AddSequential(new ShovelRackRotate(RobotMap::Rack::voltageStack));

	// retract the shovel supports and drop the totes onto the platform
	AddSequential(new ShovelSetGrab(false));

	//rotate the rack back a little to prevent occelation
	AddSequential(new RackRotate(RobotMap::Rack::voltageStack + 0.25));

	// rotate the shovel back to horizontal, and the rack back to flat
	//AddSequential(new ShovelRotate(RobotMap::Shovel::voltageFlat));
	//AddSequential(new RackRotate(RobotMap::Rack::voltageDump));

	// drop the bot
	//AddSequential(new ChassisLift(false));
}
