#include "StoreTote.h"
#include "RobotMap.h"

#include "ShovelSetGrab.h"
#include "ShovelRotate.h"

#include "ShovelSetCollect.h"
#include "WasteTime.h"

StoreTote::StoreTote()
{
	//this assumes the shovel is in position from the human station, and the rack is flat back

	AddSequential(new ShovelSetGrab(true));
	AddSequential(new ShovelSetCollect(true));
	AddSequential(new WasteTime(0.1f));
	AddSequential(new ShovelSetCollect(false));
	AddSequential(new WasteTime(0.4f));//give time for the pneumatics to actuate correctly
	AddSequential(new ShovelRotate(RobotMap::Shovel::voltageDump));
	AddSequential(new ShovelSetGrab(false));
}
