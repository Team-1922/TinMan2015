#include "Autonomous.h"
#include "DriveDistance.h"
#include <iostream>
#include "WasteTime.h"
#include "ShovelSetGrab.h"
#include "ShovelSuckWheels.h"
#include "ShovelSetCollect.h"
#include "DriveRotate.h"
#include "Drive.h"

Autonomous::Autonomous() : CommandGroup("Autonomous")
{
	//KEEP THIS; THIS IS THE MAGIC AUTONOMOUS
	//AddSequential(new Drive(0.55f, 0.75f));

	//have the collect wheels grab the tote
	AddSequential(new ShovelSetCollect(true));

	//starting with the back pointing the human station, and the shovel has a tote basically already in it, but not touching
	AddSequential(new ShovelSuckWheels(0.4f, -0.75f, -0.75f));//Apparently this function with only two floats in "ambiguous"

	//apply solenoid pressure
	AddSequential(new ShovelSetGrab(true));

	//turn 90 degrees clockwise
	AddSequential(new DriveRotate(-90.0f));

	//drive forwards a little
	//AddSequential(new Drive(0.6f, 0.75f));
	AddSequential(new DriveDistance(60.0f));//drive 5 feet
}
