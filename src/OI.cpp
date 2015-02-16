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

#include "Commands/TestCommandGroup.h"
#include "Commands/TestPneumatics.h"
#include "Commands/RackDeploy.h"
#include "Commands/RackRetract.h"

#include "Commands/SwitchJoyCombined.h"
#include "Commands/SwitchJoyRack.h"
#include "Commands/SwitchJoyShovel.h"

#include "Commands/ShovelToggleWidth.h"
#include "Commands/RackToggleClaw.h"


#include "RobotMap.h"


OI::OI():
m_pDriverStick1 (NULL),
m_pDriverStick2(NULL),
m_pOperatorStick (1),
m_pDriverController(NULL)
{
	m_pDriverStick1 = new Joystick(RobotMap::Controls::driverJoy1);
	m_pDriverStick2 = new Joystick(RobotMap::Controls::driverJoy2);
	m_pOperatorStick = new Joystick(RobotMap::Controls::operatorJoy);
	m_pDriverController = new Joystick(RobotMap::Controls::controller);

    // Create some buttons
    /*JoystickButton* buttonA = new JoystickButton(m_pDriverStick, RobotMap::Controls::extendRack);
    JoystickButton* buttonB= new JoystickButton(m_pDriverStick, RobotMap::Controls::raiseRack);
    JoystickButton* buttonC= new JoystickButton(m_pDriverStick, RobotMap::Controls::flatRack);
    JoystickButton* buttonD = new JoystickButton(m_pDriverStick, RobotMap::Controls::groundShovel);
    JoystickButton* buttonE = new JoystickButton(m_pDriverStick, RobotMap::Controls::humanShovel);
    JoystickButton* buttonF = new JoystickButton(m_pDriverStick, RobotMap::Controls::dumpShovel);

    JoystickButton* buttonTest = new JoystickButton(m_pDriverStick, 12);
    buttonTest->WhenPressed(new TestPneumatics());

    JoystickButton* buttonBigTest = new JoystickButton(m_pDriverStick, 1);
    buttonBigTest->WhenPressed(new TestCommandGroup());*/


    // Connect the buttons to commands
    /*
	buttonA->WhenPressed(new CommandRackExtend());
	buttonB->WhenPressed(new CommandRackRaise());
	buttonC->WhenPressed(new CommandRackFlat());
	buttonD->WhenPressed(new CommandShovelGround());
	buttonE->WhenPressed(new CommandShovelHuman());
	buttonF->WhenPressed(new CommandShovelDump());

	JoystickButton* buttonDeploy = new JoystickButton(m_pOperatorStick, RobotMap::Controls::extendRack);
	buttonDeploy->WhenActive(new RackDeploy());
	JoystickButton* buttonRetract = new JoystickButton(m_pOperatorStick, RobotMap::Controls::retractRack);
	buttonRetract->WhenActive(new RackRetract());*/
    JoystickButton* buttonTest = new JoystickButton(m_pOperatorStick, Joystick::kDefaultTriggerButton);
    buttonTest->WhenPressed(new TestPneumatics());

    JoystickButton* buttonShovelJoy = new JoystickButton(m_pOperatorStick, RobotMap::Controls::shovelJoyControlled);
    JoystickButton* buttonRackJoy = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackJoyControlled);
    JoystickButton* buttonBothJoy = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackShovelCombined);
    JoystickButton* buttonToggleShovel = new JoystickButton(m_pOperatorStick, RobotMap::Controls::shovelWidthToggle);
    JoystickButton* buttonToggleRack = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackClawToggle);


    buttonShovelJoy->WhenPressed(new SwitchJoyShovel());
    buttonRackJoy->WhenPressed(new SwitchJoyRack());
    buttonBothJoy->WhenPressed(new SwitchJoyCombined());
    buttonToggleShovel->WhenPressed(new ShovelToggleWidth());
    buttonToggleRack->WhenPressed(new RackToggleClaw());

    //TODO: setup all of the commands that take controls
}


Joystick* OI::GetDriverJoystick1()
{
	return m_pDriverStick1;
}

Joystick* OI::GetDriverJoystick2()
{
	return m_pDriverStick2;
}

Joystick* OI::GetOperatorJoystick()
{
	return m_pOperatorStick;
}

Joystick* OI::GetDriverController()
{
	return m_pDriverController;
}



