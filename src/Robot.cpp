#include <commands/CommandRackFlat.h>
#include "WPILib.h"
#include "Commands/Command.h"
#include "CommandBase.h"
#include "Commands/Autonomous.h"
#include "Commands/AutonomousV2.h"
#include "Commands/TestCommandGroup.h"

#include "Utilities.h"

class Robot: public IterativeRobot
{
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	SendableChooser *Chooser;

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

		SmartDashboard::PutNumber("PotentiometerValueAngle", CommandBase::rackMotor->getPotentiometer());
		SmartDashboard::PutNumber("PotentiometerValueRaw",   CommandBase::rackMotor->getPotentiometerRaw());
		SmartDashboard::PutNumber("EncoderTurnCount", CommandBase::rackMotor->getEncCount());
		SmartDashboard::PutBoolean("EncoderDirection", CommandBase::rackMotor->getEncDirection());
		SmartDashboard::PutNumber("EncoderRate", CommandBase::rackMotor->getEncRate());
		SmartDashboard::PutBoolean("EncoderStopped", CommandBase::rackMotor->getEncStopped());
		SmartDashboard::PutData("Test Pneumatics and Drive Train", new TestCommandGroup());
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

