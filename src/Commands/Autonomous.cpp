#include "Autonomous.h"
//#include "DriveStraight.h"
#include <iostream>
#include "WasteTime.h"
#include "ShovelCloseWidth.h"
#include "ShovelSuckWheels.h"
#include "Drive.h"

Autonomous::Autonomous() : CommandGroup("Autonomous")
{
	//KEEP THIS; THIS IS THE MAGIC AUTONOMOUS
	//AddSequential(new Drive(0.55f, 0.75f));

	//starting with the back pointing the human station, and the shovel has a tote basically already in it, but not touching
	AddSequential(new ShovelSuckWheels(0.4f, -0.75f, -0.75));//aparently this function with only two floats in "ambiguous"

	//apply solenoid pressure
	AddSequential(new ShovelCloseWidth());

	//turn left
	AddSequential(new Drive(0.5f, 0.3f, -0.3f));

	//drive forwards a little
	AddSequential(new Drive(0.6f, 0.75f));
}
