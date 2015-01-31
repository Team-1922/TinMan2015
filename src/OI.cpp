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
#include "Commands/CommandShovelDump.h"
#include "Commands/CommandShovelGround.h"
#include "Commands/CommandShovelHuman.h"
#include "Commands/CommandTestPneumatics.h"
#include "Commands/TestCommandGroup.h"
#include "Commands/RackDeploy.h"
#include "Commands/RackRetract.h"

#include "RobotMap.h"


OI::OI():
m_pDriverStick (NULL),
m_pOperatorStick (NULL)
{
	m_pDriverStick = new Joystick(0);
	m_pOperatorStick = new Joystick(1);

    // Create some buttons
    /*JoystickButton* buttonA = new JoystickButton(m_pDriverStick, RobotMap::Controls::extendRack);
    JoystickButton* buttonB= new JoystickButton(m_pDriverStick, RobotMap::Controls::raiseRack);
    JoystickButton* buttonC= new JoystickButton(m_pDriverStick, RobotMap::Controls::flatRack);
    JoystickButton* buttonD = new JoystickButton(m_pDriverStick, RobotMap::Controls::groundShovel);
    JoystickButton* buttonE = new JoystickButton(m_pDriverStick, RobotMap::Controls::humanShovel);
    JoystickButton* buttonF = new JoystickButton(m_pDriverStick, RobotMap::Controls::dumpShovel);

    JoystickButton* buttonTest = new JoystickButton(m_pDriverStick, 12);
    buttonTest->WhenPressed(new CommandTestPneumatics());

    JoystickButton* buttonBigTest = new JoystickButton(m_pDriverStick, 1);
    buttonBigTest->WhenPressed(new TestCommandGroup());


    // Connect the buttons to commands
	buttonA->WhenPressed(new CommandRackExtend());
	buttonB->WhenPressed(new CommandRackRaise());
	buttonC->WhenPressed(new CommandRackFlat());
	buttonD->WhenPressed(new CommandShovelGround());
	buttonE->WhenPressed(new CommandShovelHuman());
	buttonF->WhenPressed(new CommandShovelDump());*/

	JoystickButton* buttonDeploy = new JoystickButton(m_pOperatorStick, RobotMap::Controls::deployRack);
	buttonDeploy->WhenActive(new RackDeploy());
	JoystickButton* buttonRetract = new JoystickButton(m_pOperatorStick, RobotMap::Controls::retractRack);
	buttonRetract->WhenActive(new RackRetract());
}


Joystick* OI::GetDriverJoystick()
{
	return m_pDriverStick;
}

Joystick* OI::GetOperatorJoystick()
{
	return m_pOperatorStick;
}



