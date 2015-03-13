#include "PrepareHumanStation.h"
#include "ShovelRotate.h"
#include "RobotMap.h"
#include "ShovelSetGrab.h"
#include "ShovelSetCollect.h"

PrepareHumanStation::PrepareHumanStation()
{

	//this doesn't assume anything, and closes the width before turning just in case it has to pass the rack
	// even though that would probably never happen.

	AddSequential(new ShovelSetGrab(false));
	AddSequential(new ShovelSetCollect(false));
	AddSequential(new ShovelRotate(RobotMap::Shovel::voltageFlat));
}
