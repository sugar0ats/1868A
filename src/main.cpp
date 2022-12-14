/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontLeft            motor         1               
// FrontRight           motor         3               
// BackLeft             motor         2               
// BackRight            motor         4               
// Controller1          controller                    
// Rollers              motor         11              
// Intake               motor         12              
// FlywheelNonSparkly   motor         13              
// FlywheelSparkly      motor         14              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  FrontLeft.spinFor(forward, 280, degrees, false);
  FrontRight.spinFor(forward, 280, degrees, false);
  BackLeft.spinFor(forward, 280, degrees, false);
  BackRight.spinFor(forward, 280, degrees, false);
  Rollers.spinFor(forward, 100, degrees); // roll the roller to desired color

  wait(3000, msec);

  FrontLeft.spinFor(reverse, 360 * 20, degrees, false); // back up
  FrontRight.spinFor(reverse, 360 * 20, degrees, false);
  BackLeft.spinFor(reverse, 360 * 20, degrees, false);
  BackRight.spinFor(reverse, 360 * 20, degrees, false);

  FlywheelSparkly.spinFor(forward, 360 * 600, degrees,false);
  FlywheelNonSparkly.spinFor(forward, 360 * 600, degrees,false);

  wait(1000,msec);

  FrontLeft.spinFor(forward, 360*20, degrees, false); // turning 90 degrees to the right
  //FrontRight.spinFor(reverse, 360*20, degrees, false);
  BackLeft.spinFor(forward, 360*20, degrees, false);
  //BackRight.spinFor(reverse, 360*20, degrees, false);

  wait(1000, msec);

  FrontLeft.spinFor(reverse, 360 * 75, degrees, false); // going to goal
  FrontRight.spinFor(reverse, 360 * 75, degrees, false);
  BackLeft.spinFor(reverse, 360 * 75, degrees, false);
  BackRight.spinFor(reverse, 360 * 75, degrees);

  wait(1000, msec);

  Intake.spinFor(forward, 2000, degrees, false);
  


  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// ~~~~~~~~~~~~ helper functions below ~~~~~~~~~~~~

int rollerSpeed = 30;
int intakeSpeed = 200;
int flywheelSpeed = 600; 

void spinRollers() {
  if (Controller1.ButtonB.pressing()) {
    Rollers.spin(forward, rollerSpeed, rpm);
  } else if (Controller1.ButtonX.pressing()) {
    Rollers.spin(reverse, rollerSpeed, rpm);
  } else {
    Rollers.stop(hold);
  }
}

// void spinIntakeAndRollers() {
//     if (Controller1.ButtonA.pressing()) {
//       Intake.spin(forward, intakeSpeed, rpm);
//     } else if (Controller1.ButtonY.pressing()) {
//       Intake.spin(reverse, intakeSpeed, rpm);
//     } else if (Controller1.ButtonR1.pressing()) {
//       FlywheelSparkly.spin(forward, flywheelSpeed, rpm);
//       FlywheelNonSparkly.spin(forward, flywheelSpeed, rpm);
//       Intake.spin(forward, intakeSpeed, rpm);
//     } else {
//       FlywheelSparkly.stop();
//       FlywheelNonSparkly.stop();
//       Intake.stop(hold);
//     }
// }

bool spinFlywheel = false;

void doSpinFlywheel() {
  spinFlywheel = true;
}
void dontSpinFlywheel() {
  spinFlywheel = false;
}

void spinIntakeAndFlywheel() {
    if (Controller1.ButtonA.pressing()) {
      Intake.spin(forward, intakeSpeed, rpm);
    } else if (Controller1.ButtonY.pressing()) {
      Intake.spin(reverse, intakeSpeed, rpm);
    } else if (Controller1.ButtonR1.pressing()) {
      Intake.spin(forward, intakeSpeed, rpm);
    } else {
      Intake.stop(hold);
    }

    Controller1.ButtonR1.pressed(doSpinFlywheel);
    Controller1.ButtonR2.pressed(dontSpinFlywheel);
}

// void shootDisks() {
//   if (Controller1.ButtonR1.pressing()) {
//     FlywheelSparkly.spin(forward, flywheelSpeed, rpm);
//     FlywheelNonSparkly.spin(forward, flywheelSpeed, rpm);
//     Intake.spin(forward, intakeSpeed, rpm);

//   } else {
//     FlywheelSparkly.stop();
//     FlywheelNonSparkly.stop();
//     Intake.stop(hold);
//   }
// }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void driverControl() {
  // 4 motors: upper left (1), upper right (2), lower left (3), lower right (4)
  // left joystick: forward and backward + sideways (axes 3 and 4)
  // right joystick: turning (axes 1)

  int forwardVal = Controller1.Axis3.position(percent);
  int sidewaysVal = Controller1.Axis4.position(percent);
  int turnVal = Controller1.Axis1.position(percent);

  int deadband = 3;

  if (abs(forwardVal) < deadband && abs(sidewaysVal) < deadband && abs(turnVal) < deadband) {
    FrontLeft.stop(hold);
    FrontRight.stop(hold);
    BackLeft.stop(hold);
    BackRight.stop(hold);
    
  } else {
    FrontLeft.spin(forward, (forwardVal + sidewaysVal + turnVal), percent);
    FrontRight.spin(forward, (forwardVal - sidewaysVal - turnVal), percent);
    BackLeft.spin(forward, (forwardVal - sidewaysVal + turnVal), percent);
    BackRight.spin(forward, (forwardVal + sidewaysVal - turnVal), percent);
    // 12/08 negated turnVal because axis 1 was coded backwards. hope it works lol
    // update ehehe it works !!! i (julia) am so smart :D
  }

}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    driverControl();

    //roller motor movement
    spinRollers();

    spinIntakeAndFlywheel();

    if (spinFlywheel) {
      FlywheelSparkly.spin(forward, flywheelSpeed, rpm);
      FlywheelNonSparkly.spin(forward, flywheelSpeed, rpm);
    } else {
      FlywheelSparkly.stop();
      FlywheelNonSparkly.stop();
    }

    //shootDisks();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  //Competition.autonomous(autonomous);

  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
