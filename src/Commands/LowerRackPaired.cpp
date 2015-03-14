#include "LowerRackPaired.h"
#include "ShovelRackRotate.h"
#include "WasteTime.h"

LowerRackPaired::LowerRackPaired()
{
	//gradually lower the rack
	AddSequential(new ShovelRackRotate(RobotMap::Rack::voltageDump - 0.75));
	AddSequential(new WasteTime(0.25f));
	AddSequential(new ShovelRackRotate(RobotMap::Rack::voltageDump - 0.60));
	AddSequential(new WasteTime(0.25f));
	AddSequential(new ShovelRackRotate(RobotMap::Rack::voltageDump - 0.50));
	AddSequential(new WasteTime(0.25f));
	AddSequential(new ShovelRackRotate(RobotMap::Rack::voltageDump - 0.30));
	AddSequential(new ShovelRackRotate(RobotMap::Rack::voltageDump - 0.20));
	AddSequential(new WasteTime(0.25f));
	AddSequential(new ShovelRackRotate(RobotMap::Rack::voltageDump - 0.10));
	AddSequential(new ShovelRackRotate(RobotMap::Rack::voltageDump));
}
