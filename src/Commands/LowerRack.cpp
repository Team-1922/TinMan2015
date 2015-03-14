#include "LowerRack.h"
#include "RackRotate.h"
#include "WasteTime.h"

LowerRack::LowerRack()
{
	//gradually lower the rack
	AddSequential(new RackRotate(RobotMap::Rack::voltageDump - 0.75));
	AddSequential(new WasteTime(0.25f));
	AddSequential(new RackRotate(RobotMap::Rack::voltageDump - 0.60));
	AddSequential(new WasteTime(0.25f));
	AddSequential(new RackRotate(RobotMap::Rack::voltageDump - 0.50));
	AddSequential(new WasteTime(0.25f));
	AddSequential(new RackRotate(RobotMap::Rack::voltageDump - 0.30));
	AddSequential(new RackRotate(RobotMap::Rack::voltageDump - 0.20));
	AddSequential(new WasteTime(0.25f));
	AddSequential(new RackRotate(RobotMap::Rack::voltageDump - 0.10));
	AddSequential(new RackRotate(RobotMap::Rack::voltageDump, false));
}
