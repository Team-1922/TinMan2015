#include "WPILib.h"
#include "Commands/Command.h"
#include "CommandBase.h"
#include "Commands/Autonomous.h"
#include "Commands/AutonomousV2.h"
#include "Commands/DriveStraight.h"
#include "Commands/ArcadeDrive.h"
#include "Commands/RaceDrive.h"
#include "Commands/TankDrive.h"
#include "Commands/SwitchJoyCombined.h"
#include "Commands/SwitchJoyRack.h"
#include "Commands/SwitchJoyShovel.h"

#include "Commands/ShovelToggleGrab.h"
#include "Subsystems/RackRotation.h"

#include "Utilities.h"

#include "Commands/RackSetpointHere.h"

class Robot: public IterativeRobot
{
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	SendableChooser *Chooser;
	SendableChooser *driveModeChooser;
	Command* currentDriveMode;

	PowerDistributionPanel pdp;

	SendableChooser *operatorJoyControl;
	Command* currentOperatorJoyMode;

	RackSetpointHere* rackSetSetpointCurrentAngle;

	long counter = 0;


	void RobotInit()
	{

		Utilities::startTimer();
		CommandBase::init();

		rackSetSetpointCurrentAngle = new RackSetpointHere();

		//this is BAD (well its good, but we are not setup to use it yet)
		//get the voltage offsets for the subsystems; NOTE: this is not really used in teleop, so we can put it here
		//RobotMap::Shovel::voltageOffset = CommandBase::rackRotation->GetPotVoltage();
		//RobotMap::Rack::voltageOffset   = CommandBase::shovelRotation->GetPotVoltage();


		//autonomousCommand = new ExampleCommand();
		lw = LiveWindow::GetInstance();

		CameraServer::GetInstance()->SetQuality(75);
		//the camera name (ex "cam0") can be found through the roborio web interface
		//CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		//Initializes a chooser item in the SmartDashboard to select the Autonomous Mode for the round
		/*Chooser = new SendableChooser();
		Chooser->AddDefault("Default Program", new Autonomous);/
		Chooser->AddObject("Other Autonomous", new AutonomousV2);
		SmartDashboard::PutData("Autonomous Mode", Chooser);

		//SmartDashboard Test code~~~
		SmartDashboard::PutData("Shovel Width Toggle", new ShovelToggleWidth());*/


		//this is for switchible drive modes
		/*driveModeChooser = new SendableChooser();
		driveModeChooser->AddDefault("Controller Drive", new RaceDrive);
		driveModeChooser->AddObject("Arcade Drive", new ArcadeDrive);
		driveModeChooser->AddObject("Tank Drive", new TankDrive);
		SmartDashboard::PutData("Drive Mode", driveModeChooser);*/

		//this is for switching which thing the joystick operator is controlling
		/*operatorJoyControl = new SendableChooser();
		operatorJoyControl->AddDefault("Control Rack", new SwitchJoyRack());
		operatorJoyControl->AddObject("Control Shovel", new SwitchJoyShovel());
		operatorJoyControl->AddObject("Control Both", new SwitchJoyCombined());
		SmartDashboard::PutData("Operator Control Mode", operatorJoyControl);*/


	}
	
	void UniversalPeriodic()
	{
		CommandBase::shovelRotation->TickPotentiometer();
		CommandBase::rackRotation->TickPotentiometer();
		//pdp.ClearStickyFaults();
	}

	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{
		RobotMap::Mode = false;
		counter = 0;

		CommandBase::driveTrain->Disable();

		//Retrieves selected Autonomous mode from SmartDashboard
		autonomousCommand = new Autonomous();
		if(autonomousCommand)//just to be sure
			autonomousCommand->Start();
		//if (autonomousCommand != NULL)
		//	autonomousCommand->Start();
	}

	void AutonomousPeriodic()
	{
		++counter;

		//update this BEFORE running commands
		UniversalPeriodic();
		Scheduler::GetInstance()->Run();
		//SmartDashboard::PutBoolean("Autonomous is working:", RobotMap::AutonomousEnabled);

		SmartDashboard::PutNumber("Counter", counter);
	}

	void TeleopInit()
	{
		counter = 0;
		RobotMap::Mode = true;
		CommandBase::driveTrain->Disable();
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		//if (autonomousCommand != NULL)
		//	autonomousCommand->Cancel();
	}

	void TeleopPeriodic()
	{

		++counter;

		//update this BEFORE running commands
		UniversalPeriodic();
		Scheduler::GetInstance()->Run();


		//command for stopping the rack at its current position
		if(Utilities::isEqual(CommandBase::oi->GetOperatorThrottle(), 0.0f, 0.15f))
			rackSetSetpointCurrentAngle->Run();

		//ONLY ONE DRIVE MODE
		//the drive and operator modes
		/*Command* curDrive = (Command*)driveModeChooser->GetSelected();
		if(curDrive != currentDriveMode)
		{
			currentDriveMode = curDrive;
			currentDriveMode->Start();
		}*/

		//THIS IS NO LONGER BEING USED
		//TODO: this will be changed with buttons, and will not reflect back upon this radio box
		/*Command* curOp = (Command*)operatorJoyControl->GetSelected();
		if(curOp != currentOperatorJoyMode)
		{
			currentOperatorJoyMode = curOp;
			currentOperatorJoyMode->Start();
		}*/


		//display all potentially useful information to the user

		/*
		 * Controls
		 */

		//SmartDashboard::PutNumber("Operator Control Mode", RobotMap::Controls::currOpMode);


		/*
		 * Drive Train information
		 */
		SmartDashboard::PutNumber("Left Motor (RPM)",
				CommandBase::driveTrain->getEncRateLeft() *
				(CommandBase::driveTrain->getEncDirectionLeft() ? 1 : -1));
		SmartDashboard::PutNumber("Right Motor (RPM)",
				CommandBase::driveTrain->getEncRateRight() *
				(CommandBase::driveTrain->getEncDirectionRight() ? 1 : -1));
		SmartDashboard::PutNumber("Left Motor (-1 to 1)",
				CommandBase::driveTrain->getLeft());
		SmartDashboard::PutNumber("Right Motor (-1 to 1)",
				CommandBase::driveTrain->getRight());
		SmartDashboard::PutString("Drive Train Command", CommandBase::driveTrain->GetCurrentCommand()->GetName());

		/*
		 * Shovel Information
		 */
		//SmartDashboard::PutNumber("Shovel Angle", CommandBase::shovel->getPotentiometer());
		//SmartDashboard::PutNumber("Shovel Motor (Deg/s)", CommandBase::shovel->getTurnRate());
		//SmartDashboard::PutNumber("Shovel Motor (-1 to 1)", CommandBase::shovel->getMotor());
		SmartDashboard::PutNumber("Shovel Setpoint", CommandBase::shovelRotation->GetSetpoint());
		SmartDashboard::PutNumber("Shovel Voltage", CommandBase::shovelRotation->GetPotVoltage());
		SmartDashboard::PutNumber("Shovel Grab Solenoid", CommandBase::shovel->getGrabSolenoid());
		SmartDashboard::PutNumber("Shovel Collect Solenoid", CommandBase::shovel->getCollectSolenoid());
		SmartDashboard::PutNumber("Shovel Collect Left", CommandBase::shovel->GetSuckWheelLeft());
		SmartDashboard::PutNumber("Shovel Collect Right", CommandBase::shovel->GetSuckWheelRight());
		SmartDashboard::PutBoolean("Shovel Reed", CommandBase::shovelRotation->GetReed());

		/*
		 * Rack Information
		 */
		//SmartDashboard::PutNumber("Rack Angle", CommandBase::rack->getPotentiometer());
		//SmartDashboard::PutNumber("Rack Potentiometer Rate", CommandBase::rack->getTurnRate());
		//SmartDashboard::PutNumber("Rack Motor (-1 to 1)", CommandBase::rack->getMotor());
		SmartDashboard::PutNumber("Rack Setpoint", CommandBase::rackRotation->GetSetpoint());
		SmartDashboard::PutNumber("Rack Voltage", CommandBase::rackRotation->GetPotVoltage());
		SmartDashboard::PutNumber("Claw Solenoid", CommandBase::rack->getClaw());
		//this is only going to affect the practice bot

		SmartDashboard::PutNumber("Rack P", CommandBase::rackRotation->GetP());
		SmartDashboard::PutNumber("Rack I", CommandBase::rackRotation->GetI());
		SmartDashboard::PutNumber("Rack D", CommandBase::rackRotation->GetD());




		SmartDashboard::PutNumber("Counter", counter);



		/*
		 * Chassis
		 */
		//SmartDashboard::PutBoolean("Chassis Solenoid", CommandBase::chassis->getSolenoid());

	}

	void TestPeriodic()
	{
		/*Solenoid* pShovelSolenoid = new Solenoid(RobotMap::Shovel::shovelWidthSol);
		lw->AddActuator("Shovel", "Solenoid", pShovelSolenoid);*/
		lw->Run();

		//SmartDashboard::PutNumber("Rack Voltage", CommandBase::rackRotation->GetPotVoltage());


	}


};

START_ROBOT_CLASS(Robot);

