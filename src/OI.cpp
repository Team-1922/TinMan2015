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

	//the four different Command Groups
	JoystickButton* buttonShovelFlat = new JoystickButton(m_pOperatorStick, RobotMap::Controls::prepareHuman);
	JoystickButton* buttonShovelDump = new JoystickButton(m_pOperatorStick, RobotMap::Controls::dumpTote);
	JoystickButton* buttonRackFlat = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackFlat);
	JoystickButton* buttonRackStack = new JoystickButton(m_pOperatorStick, RobotMap::Controls::stackTotes);
	//JoystickButton* buttonRackPickContainer = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackContainer);
	JoystickButton* buttonRackShovelStack = new JoystickButton(m_pOperatorStick, RobotMap::Controls::stackRackShovelSame);

	JoystickButton* buttonTestDriveDistance = new JoystickButton(m_pOperatorStick, 1);//trigger

    //the three solenoid toggle buttons
    JoystickButton* buttonToggleShovelGrab = new JoystickButton(m_pOperatorStick, RobotMap::Controls::shovelGrabToggle);
    JoystickButton* buttonToggleShovelCollect = new JoystickButton(m_pOperatorStick, RobotMap::Controls::shovelCollectToggle);
    //JoystickButton* buttonToggleClaw = new JoystickButton(m_pOperatorStick, RobotMap::Controls::rackClawToggle);
    //JoystickButton* buttonToggleChassis = new JoystickButton(m_pOperatorStick, RobotMap::Controls::chassisLiftToggle);

    //the two buttons for extending/retracting the rack
    JoystickButton* buttonExtendRack = new JoystickButton(m_pOperatorStick, RobotMap::Controls::extendRack);
    JoystickButton* buttonRetractRack = new JoystickButton(m_pOperatorStick, RobotMap::Controls::retractRack);


    //buttonShovelJoy->WhenPressed(new ShovelRotate(4.0));
    //buttonRackJoy->WhenPressed(new SwitchJoyRack());
    //buttonBothJoy->WhenPressed(new SwitchJoyCombined());

    buttonShovelFlat->WhenPressed(new ShovelRotate(RobotMap::Shovel::voltageFlat, false));
    buttonShovelDump->WhenPressed(new ShovelRotate(RobotMap::Shovel::voltageDump));
    buttonRackFlat->WhenPressed(new RackRotate(RobotMap::Rack::voltageDump, false));
    buttonRackStack->WhenPressed(new RackRotate(RobotMap::Rack::voltageStack));
    //buttonRackPickContainer->WhenPressed(new RackRotate(RobotMap::Rack::voltagePickContainer));
    buttonRackShovelStack->WhenPressed(new ShovelRackRotate(RobotMap::Rack::voltageStack));

    buttonToggleShovelGrab->WhenPressed(new ShovelToggleGrab());
    buttonToggleShovelCollect->WhenPressed(new ShovelToggleCollect());
    //buttonToggleClaw->WhenPressed(new RackToggleClaw());
    //buttonToggleChassis->WhenPressed(new ChassisToggleLift());

    //have these call repeatedly when held down
    buttonExtendRack->WhileHeld(new RackExtend());
    buttonRetractRack->WhileHeld(new RackRetract());

    buttonTestDriveDistance->WhenPressed(new DriveDistance(12));


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



