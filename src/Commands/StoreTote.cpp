#include "StoreTote.h"
#include "RobotMap.h"

#include "ShovelCloseWidth.h"
#include "ShovelRotate.h"

StoreTote::StoreTote()
{
	//this assumes the shovel is in position from the human station, and the rack is flat back

	AddSequential(new ShovelCloseWidth());
	AddSequential(new ShovelRotate(RobotMap::Shovel::voltageDump));
}
