#include <Subsystems/Rack.h>
#include "CommandBase.h"
#include "Commands/Scheduler.h"
#include "Utilities.h"

// Initialize a single static instance of all of your subsystems to NULL
Rack* CommandBase::rack = NULL;
OI* CommandBase::oi = NULL;
DriveTrain* CommandBase::driveTrain = NULL;
Shovel* CommandBase::shovel = NULL;
Camera* CommandBase::camera = NULL;
Pneumatics* CommandBase::pneumatics = NULL;
Chassis* CommandBase::chassis = NULL;

CommandBase::CommandBase(char const *name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

CommandBase::~CommandBase()
{
	SAFE_DELETE(rack);
	SAFE_DELETE(oi);
	SAFE_DELETE(driveTrain);
	SAFE_DELETE(shovel);
	SAFE_DELETE(camera);
	SAFE_DELETE(pneumatics);
	SAFE_DELETE(chassis);
}

void CommandBase::init()
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	rack = new Rack();
	driveTrain = new DriveTrain();
	shovel = new Shovel();
	camera = new Camera();
	pneumatics = new Pneumatics();
	oi = new OI();
	chassis = new Chassis();
}
