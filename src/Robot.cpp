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

#include "Commands/ShovelToggleWidth.h"
#include "Subsystems/RackRotation.h"

#include "Utilities.h"

class Robot: public IterativeRobot
{
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	SendableChooser *Chooser;
	SendableChooser *driveModeChooser;
	Command* currentDriveMode;

	SendableChooser *operatorJoyControl;
	Command* currentOperatorJoyMode;

	void RobotInit()
	{
		Utilities::startTimer();
		CommandBase::init();
		//autonomousCommand = new ExampleCommand();
		lw = LiveWindow::GetInstance();

		CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		//Initializes a chooser item in the SmartDashboard to select the Autonomous Mode for the round
		Chooser = new SendableChooser();
		Chooser->AddDefault("Default Program", new Autonomous);
		Chooser->AddObject("Other Autonomous", new AutonomousV2);
		SmartDashboard::PutData("Autonomous Mode", Chooser);

		SmartDashboard::PutData("Shovel Width Toggle", new ShovelToggleWidth());

		//this is for switchible drive modes
		driveModeChooser = new SendableChooser();
		driveModeChooser->AddDefault("Controller Drive", new RaceDrive);
		driveModeChooser->AddObject("Arcade Drive", new ArcadeDrive);
		driveModeChooser->AddObject("Tank Drive", new TankDrive);
		SmartDashboard::PutData("Drive Mode", driveModeChooser);

		//this is for switching which thing the joystick operator is controlling
		operatorJoyControl = new SendableChooser();
		operatorJoyControl->AddDefault("Control Rack", new SwitchJoyRack());
		operatorJoyControl->AddObject("Control Shovel", new SwitchJoyShovel());
		operatorJoyControl->AddObject("Control Both", new SwitchJoyCombined());
		SmartDashboard::PutData("Operator Control Mode", operatorJoyControl);


	}
	
	void UniversalPeriodic()
	{
		CommandBase::shovelRotation->TickPotentiometer();
		CommandBase::rackRotation->TickPotentiometer();
	}

	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{
		//Retrieves selected Autonomous mode from SmartDashboard
		autonomousCommand =(Command*) Chooser->GetSelected();
		if(autonomousCommand)//just to be sure
			autonomousCommand->Start();
		//if (autonomousCommand != NULL)
		//	autonomousCommand->Start();
	}

	void AutonomousPeriodic()
	{
		//update this BEFORE running commands
		UniversalPeriodic();
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit()
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		//if (autonomousCommand != NULL)
		//	autonomousCommand->Cancel();
	}

	void TeleopPeriodic()
	{
		//update this BEFORE running commands
		UniversalPeriodic();
		Scheduler::GetInstance()->Run();

		//the drive and operator modes
		Command* curDrive = (Command*)driveModeChooser->GetSelected();
		if(curDrive != currentDriveMode)
		{
			currentDriveMode = curDrive;
			currentDriveMode->Start();
		}

		//TODO: this will be changed with buttons, and will not reflect back upon this radio box
		Command* curOp = (Command*)operatorJoyControl->GetSelected();
		if(curOp != currentOperatorJoyMode)
		{
			currentOperatorJoyMode = curOp;
			currentOperatorJoyMode->Start();
		}


		//display all potentially useful information to the user

		/*
		 * Controls
		 */

		SmartDashboard::PutNumber("Operator Control Mode", RobotMap::Controls::currOpMode);


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

		/*
		 * Shovel Information
		 */
		//SmartDashboard::PutNumber("Shovel Angle", CommandBase::shovel->getPotentiometer());
		//SmartDashboard::PutNumber("Shovel Motor (Deg/s)", CommandBase::shovel->getTurnRate());
		//SmartDashboard::PutNumber("Shovel Motor (-1 to 1)", CommandBase::shovel->getMotor());
		SmartDashboard::PutNumber("Shovel Setpoint", CommandBase::shovelRotation->GetSetpoint());
		SmartDashboard::PutNumber("Shovel Voltage", CommandBase::shovelRotation->GetPotVoltage());
		SmartDashboard::PutNumber("Shovel Solenoid", CommandBase::shovel->getSolenoid());
		SmartDashboard::PutBoolean("Shovel Wide Right", CommandBase::shovel->GetShovelWideRight());
		SmartDashboard::PutBoolean("Shovel Wide Left", CommandBase::shovel->GetShovelWideLeft());
		//this is only going to affect the practice bot
#ifndef COMP_BOT
		SmartDashboard::PutBoolean("Shovel Rotate Stop Backward", CommandBase::shovelRotation->GetLimRotationBackward());
		SmartDashboard::PutBoolean("Shovel Rotate Stop Forward", CommandBase::shovelRotation->GetLimRotationForward());
#endif

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
#ifndef COMP_BOT
		SmartDashboard::PutBoolean("Rack Rotate Stop Backward", CommandBase::rackRotation->GetLimRotationBackward());
		SmartDashboard::PutBoolean("Rack Rotate Stop Forward", CommandBase::rackRotation->GetLimRotationForward());
#endif



		/*
		 * Chassis
		 */
		SmartDashboard::PutBoolean("Chassis Solenoid", CommandBase::chassis->getSolenoid());

	}

	void TestPeriodic()
	{
		/*Solenoid* pShovelSolenoid = new Solenoid(RobotMap::Shovel::shovelWidthSol);
		lw->AddActuator("Shovel", "Solenoid", pShovelSolenoid);*/
		lw->Run();

		SmartDashboard::PutNumber("Rack Voltage", CommandBase::rackRotation->GetPotVoltage());


	}


};

START_ROBOT_CLASS(Robot);

