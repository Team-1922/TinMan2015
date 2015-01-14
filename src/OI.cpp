/*
 *
 *  Created on: Jan 13, 2015
 *      Author: MikeCaplan
 */
/*
 * OI.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: alex
 */

#include "OI.h"

#include "Commands/CommandRackExtend.h"
#include "Commands/CommandRackFlat.h"
#include "Commands/CommandRackRaise.h"


OI::OI() {
	stick= new Joystick(0);


    // Create some buttons
    JoystickButton* buttonA = new JoystickButton(stick, 5); //***change channels***
    JoystickButton* buttonB= new JoystickButton(stick, 6);
    JoystickButton* buttonC= new JoystickButton(stick, 7);


    // Connect the buttons to commands
  buttonA->WhenPressed(new CommandRackExtend());
  buttonB->WhenPressed(new CommandRackRaise());
  buttonC->WhenPressed(new CommandRackFlat());
}


Joystick* OI::GetJoystick() {
	return stick;
}



