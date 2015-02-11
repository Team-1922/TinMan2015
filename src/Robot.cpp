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

#include "Utilities.h"

class Robot: public IterativeRobot
{
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	SendableChooser *Chooser;
	SendableChooser *driveModeChooser;
	SendableChooser *operatorJoyControl;

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

		//this is for switchible drive modes
		driveModeChooser = new SendableChooser();
		driveModeChooser->AddDefault("Controller Drive", new RaceDrive);
		driveModeChooser->AddObject("Arcade Drive", new ArcadeDrive);
		driveModeChooser->AddObject("Tank Drive", new TankDrive);

		//this is for switching which thing the joystick operator is controlling
		operatorJoyControl = new SendableChooser();
		operatorJoyControl->AddDefault("Control Rack", new SwitchJoyRack());
		operatorJoyControl->AddObject("Control Shovel", new SwitchJoyShovel());
		operatorJoyControl->AddObject("Control Both", new SwitchJoyCombined());
	}
	
	void UniversalPeriodic()
	{
		CommandBase::shovel->tickPotentiometer();
		CommandBase::rack->tickPotentiometer();
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

		//display all potentially useful information to the user


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
		SmartDashboard::PutNumber("Shovel Angle", CommandBase::shovel->getPotentiometer());
		SmartDashboard::PutNumber("Shovel Motor (Deg/s)", CommandBase::shovel->getTurnRate());


		/*
		 * Rack Information
		 */
		SmartDashboard::PutNumber("Rack Angle", CommandBase::rack->getPotentiometer());
		SmartDashboard::PutNumber("Rack Motor (Deg/s)", CommandBase::rack->getTurnRate());


		/*
		 * Chassis
		 */
		SmartDashboard::PutBoolean("Chassis Solenoid", CommandBase::chassis->getSolenoid());

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);


//part of ROBOTMAP
namespace RobotMap
{
namespace Controls
{
	OperatorMode currOpMode = kRack;
}
}

