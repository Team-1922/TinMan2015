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
#include "Commands/ShovelToggleGrab.h"
#include "Commands/RackToggleClaw.h"
#include "Commands/ShovelToggleCollect.h"
//#include "Commands/ChassisToggleLift.h"

#include "Commands/RackExtend.h"
#include "Commands/RackRetract.h"
#include "Commands/RackRotate.h"
#include "Commands/ShovelRackRotate.h"

#include "Commands/PrepareHumanStation.h"
#include "Commands/StoreTote.h"
#include "Commands/StackTotes.h"

#include "Commands/DriveDistance.h"

#include "Commands/RackPIDTune.h"


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


	//the operator controls
	JoystickButton* buttonToggleCollectSol = new JoystickButton(m_pOperatorStick, RobotMap::Controls::toggleCollectWheelSolenoid);
	JoystickButton* buttonToggleGrabSol = new JoystickButton(m_pOperatorStick, RobotMap::Controls::toggleGrabSolenoid);
	JoystickButton* buttonDumpGroup = new JoystickButton(m_pOperatorStick, RobotMap::Controls::dumpToteGroup);
	JoystickButton* buttonDump = new JoystickButton(m_pOperatorStick, RobotMap::Controls::dumpTote);
	JoystickButton* buttonPrepareHumanGroup = new JoystickButton(m_pOperatorStick, RobotMap::Controls::prepareHumanGroup);
	JoystickButton* buttonPrepareHuman = new JoystickButton(m_pOperatorStick, RobotMap::Controls::prepareHuman);
	JoystickButton* buttonRackStackGroup = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackStackGroup);
	JoystickButton* buttonRackStack = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackStack);
	JoystickButton* buttonRackFlatGroup = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackFlatGroup);
	JoystickButton* buttonRackFlat = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackFlat);


	buttonToggleCollectSol->WhenPressed(new ShovelToggleCollect());
	buttonToggleGrabSol->WhenPressed(new ShovelToggleGrab());
	buttonDumpGroup->WhenPressed(new StoreTote());
	buttonDump->WhenPressed(new ShovelRotate(RobotMap::Shovel::voltageDump));
	buttonPrepareHumanGroup->WhenPressed(new PrepareHumanStation());
	buttonPrepareHuman->WhenPressed(new ShovelRotate(RobotMap::Shovel::voltageFlat));
	buttonRackStackGroup->WhenPressed(new StackTotes());
	buttonRackStack->WhenPressed(new RackRotate(RobotMap::Rack::voltageStack));
	buttonRackFlatGroup->WhenPressed(new ShovelRackRotate(RobotMap::Rack::voltageDump));
	buttonRackFlat->WhenPressed(new RackRotate(RobotMap::Rack::voltageDump));

	//the drive controls
	JoystickButton* buttonExtendRack = new JoystickButton(m_pDriverStick1, 1);
	JoystickButton* buttonRetractRack = new JoystickButton(m_pDriverStick2, 1);

	buttonExtendRack->WhileHeld(new RackExtend());
	buttonRetractRack->WhileHeld(new RackRetract());


    /*
     * for tuning PID
     */
    /*JoystickButton* m_ButtonIncrementP = new JoystickButton(m_pDriverStick2, 8);
    JoystickButton* m_ButtonIncrementI = new JoystickButton(m_pDriverStick2, 10);
    JoystickButton* m_ButtonIncrementD = new JoystickButton(m_pDriverStick2, 12);

    JoystickButton* m_ButtonDecrementP = new JoystickButton(m_pDriverStick2, 7);
    JoystickButton* m_ButtonDecrementI = new JoystickButton(m_pDriverStick2, 9);
    JoystickButton* m_ButtonDecrementD = new JoystickButton(m_pDriverStick2, 11);


    m_ButtonIncrementP->WhenPressed(new RackPIDTune('P', 0.1f));
    m_ButtonIncrementI->WhenPressed(new RackPIDTune('I', 0.1f));
    m_ButtonIncrementD->WhenPressed(new RackPIDTune('D', 0.1f));

    m_ButtonDecrementP->WhenPressed(new RackPIDTune('P', -0.1f));
    m_ButtonDecrementI->WhenPressed(new RackPIDTune('I', -0.1f));
    m_ButtonDecrementD->WhenPressed(new RackPIDTune('D', -0.1f));*/

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

float OI::GetOperatorThrottle()
{
	//multiply by negative one to invert; add one to change maximum range to 0-2; then divide by two to normalize
	return (-1.0f * GetOperatorJoystick()->GetRawAxis(3)+1.0f) / 2;
}



