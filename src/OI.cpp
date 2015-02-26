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
//#include "Commands/TestPneumatics.h"
#include "Commands/RackRetract.h"

#include "Commands/SwitchJoyCombined.h"
#include "Commands/SwitchJoyRack.h"
#include "Commands/SwitchJoyShovel.h"

#include "Commands/ShovelRotate.h"
#include "Commands/ShovelToggleWidth.h"
#include "Commands/RackToggleClaw.h"
#include "Commands/ChassisToggleLift.h"

#include "Commands/RackExtend.h"
#include "Commands/RackRetract.h"
#include "Commands/RackRotate.h"

#include "Commands/PrepareHumanStation.h"
#include "Commands/StoreTote.h"
#include "Commands/StackTotes.h"


#include "RobotMap.h"


OI::OI():
m_pDriverStick1 (nullptr),
m_pDriverStick2(nullptr),
m_pOperatorStick (nullptr),
m_pDriverController(nullptr)
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
    //JoystickButton* buttonTest = new JoystickButton(m_pOperatorStick, Joystick::kDefaultTriggerButton);
    //buttonTest->WhenPressed(new TestPneumatics());

	//the three operator modes
    //JoystickButton* buttonShovelJoy = new JoystickButton(m_pOperatorStick, RobotMap::Controls::shovelJoyControlled);
    //JoystickButton* buttonRackJoy = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackJoyControlled);
    //JoystickButton* buttonBothJoy = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackShovelCombined);

	//the four different Command Groups
	JoystickButton* buttonHumanStation = new JoystickButton(m_pOperatorStick, RobotMap::Controls::prepareHuman);
	JoystickButton* buttonDumpTote = new JoystickButton(m_pOperatorStick, RobotMap::Controls::dumpTote);
	JoystickButton* buttonRackFlat = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackFlat);
	JoystickButton* buttonStackTotes = new JoystickButton(m_pOperatorStick, RobotMap::Controls::stackTotes);


    //the three solenoid toggle buttons
    JoystickButton* buttonToggleShovel = new JoystickButton(m_pOperatorStick, RobotMap::Controls::shovelWidthToggle);
    JoystickButton* buttonToggleClaw = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackClawToggle);
    JoystickButton* buttonToggleChassis = new JoystickButton(m_pOperatorStick, RobotMap::Controls::chassisLiftToggle);

    //the two buttons for extending/retracting the rack
    JoystickButton* buttonExtendRack = new JoystickButton(m_pOperatorStick, RobotMap::Controls::extendRack);
    JoystickButton* buttonRetractRack = new JoystickButton(m_pOperatorStick, RobotMap::Controls::retractRack);


    //buttonShovelJoy->WhenPressed(new ShovelRotate(4.0));
    //buttonRackJoy->WhenPressed(new SwitchJoyRack());
    //buttonBothJoy->WhenPressed(new SwitchJoyCombined());

    buttonHumanStation->WhenPressed(new PrepareHumanStation());
    buttonDumpTote->WhenPressed(new StoreTote());
    buttonRackFlat->WhenPressed(new RackRotate(RobotMap::Rack::voltageDump, false));
    buttonStackTotes->WhenPressed(new StackTotes());


    buttonToggleShovel->WhenPressed(new ShovelToggleWidth());
    buttonToggleClaw->WhenPressed(new RackToggleClaw());
    buttonToggleChassis->WhenPressed(new ChassisToggleLift());

    //have these call repeatedly when held down
    buttonExtendRack->WhileHeld(new RackExtend());
    buttonRetractRack->WhileHeld(new RackRetract());

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



