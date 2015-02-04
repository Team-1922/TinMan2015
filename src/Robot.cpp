#include "WPILib.h"
#include "Commands/Command.h"
#include "CommandBase.h"
#include "Commands/Autonomous.h"
#include "Commands/AutonomousV2.h"
#include "Commands/DriveStraight.h"
#include "Commands/ArcadeDrive.h"
#include "Commands/RaceDrive.h"
#include "Commands/TankDrive.h"

#include "Utilities.h"

class Robot: public IterativeRobot
{
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	SendableChooser *Chooser;
	SendableChooser *driveModeChooser;

	void RobotInit()
	{
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
	}
	
	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{
		//Retrieves selected Autonomous mode from SmartDashboard
		autonomousCommand =(Command*) Chooser->GetSelected();
		autonomousCommand->Start();
		//if (autonomousCommand != NULL)
		//	autonomousCommand->Start();
	}

	void AutonomousPeriodic()
	{
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
		Scheduler::GetInstance()->Run();

		SmartDashboard::PutNumber("Shovel Potentiometer", CommandBase::shovel->getPotentiometer());
		SmartDashboard::PutNumber("EncoderTurnCount", CommandBase::rackMotor->getEncCount());
		SmartDashboard::PutBoolean("EncoderDirection", CommandBase::rackMotor->getEncDirection());
		SmartDashboard::PutNumber("EncoderRate", CommandBase::rackMotor->getEncRate());
		SmartDashboard::PutBoolean("EncoderStopped", CommandBase::rackMotor->getEncStopped());
		SmartDashboard::PutData("Test Pneumatics and Drive Train", new DriveStraight());
		SmartDashboard::PutBoolean("Trigger Pressed", CommandBase::oi->GetOperatorJoystick()->GetButton(Joystick::kTriggerButton));
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

