#include "PrepareHumanStation.h"
#include "ShovelOpenWidth.h"
#include "ShovelRotate.h"
#include "RobotMap.h"

PrepareHumanStation::PrepareHumanStation()
{

	//this doesn't assume anything, and closes the width before turning just in case it has to pass the rack
	// even though that would probably never happen.

	AddSequential(new ShovelOpenWidth());
	AddSequential(new ShovelRotate(RobotMap::Shovel::voltageFlat));
}
