#include "InterruptRackShovel.h"

#include "RackRotate.h"
#include "ShovelRotate.h"

InterruptRackShovel::InterruptRackShovel()
{
	//stop the shovel and the rack
	AddParallel(new RackRotate(CommandBase::rackRotation->GetPotVoltage()));
	AddParallel(new ShovelRotate(CommandBase::shovelRotation->GetPotVoltage()));
}
