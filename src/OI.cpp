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

#include "Commands/CommandExtend.h"
#include "Commands/CommandFlat.h"
#include "Commands/CommandRaise.h"


OI::OI() {
	stick= new Joystick(0);


    // Create some buttons
    JoystickButton* buttonA = new JoystickButton(stick, 5); //***change channels***
    JoystickButton* buttonB= new JoystickButton(stick, 6);
    JoystickButton* buttonC= new JoystickButton(stick, 7);


    // Connect the buttons to commands
  buttonA->WhenPressed(new CommandExtend());
  buttonB->WhenPressed(new CommandRaise());
  buttonC->WhenPressed(new CommandFlat());
}


Joystick* OI::GetJoystick() {
	return stick;
}



