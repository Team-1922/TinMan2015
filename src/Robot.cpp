#include "WPILib.h"
#include "DriveTrain.h"

class Robot: public IterativeRobot
{
    DriveTrain myRobot; // robot drive system
    Joystick stick; // only joystick
    LiveWindow *lw;
    int autoLoopCounter;
    Solenoid mySole;
    Compressor myComp;

public:
    Robot() :
        myRobot(0, 1, 2, 3),    // these must be initialized in the same order
        stick(1),               // as they are declared above.
        lw(nullptr),
        autoLoopCounter(0),
        mySole(1),
        myComp(0)
    {
        //start once and forget
        myComp.Start();

        myRobot.SetExpiration(0.1);
    }

private:
    void RobotInit()
    {
        lw = LiveWindow::GetInstance();
    }

    void AutonomousInit()
    {
        autoLoopCounter = 0;
    }

    void AutonomousPeriodic()
    {
        if(autoLoopCounter < 100) //Check if we've completed 100 loops (approximately 2 seconds)
        {
            myRobot.Drive(-0.5f, 0.0f);     // drive forwards half speed
            autoLoopCounter++;
        }
        else 
        {
            myRobot.Drive(0.0f, 0.0f);      // stop robot
        }
    }

    void TeleopInit()
    {

    }

    void TeleopPeriodic()
    {
        myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)

        if (IsOperatorControl() && IsEnabled())
        {
            mySole.Set(stick.GetTrigger());
        }
    }

    void TestPeriodic()
    {
        lw->Run();
    }
};

START_ROBOT_CLASS(Robot);
