#include "StoreTote.h"
#include "RobotMap.h"

#include "ShovelSetGrab.h"
#include "ShovelRotate.h"

#include "ShovelSetCollect.h"

StoreTote::StoreTote()
{
	//this assumes the shovel is in position from the human station, and the rack is flat back

	AddSequential(new ShovelSetGrab(true));
	AddSequential(new ShovelSetCollect(false));
	AddSequential(new ShovelRotate(RobotMap::Shovel::voltageDump));
	AddSequential(new ShovelSetGrab(false));
}
