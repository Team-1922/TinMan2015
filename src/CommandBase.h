#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

//#include <Subsystems/Pneumatics.h>
#include "Subsystems/Rack.h"
#include "Subsystems/RackRotation.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Shovel.h"
#include "Subsystems/Camera.h"
//#include "Subsystems/Chassis.h"
#include "Subsystems/ShovelRotation.h"
#include <string>
#include "Commands/Command.h"
#include "OI.h"
#include "WPILib.h"


/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command
{
public:
	CommandBase(char const *name);
	CommandBase();
	virtual ~CommandBase();

	static void init();
	// Create a single static instance of all of your subsystems
	static Shovel *shovel;
	static Rack *rack;
	static OI *oi;
	static DriveTrain *driveTrain;
	//static Pneumatics* pneumatics;
	static Camera* camera;
	//static Chassis* chassis;
	static RackRotation* rackRotation; // this is a PID system
	static ShovelRotation* shovelRotation;
};

#endif
