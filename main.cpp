#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;

// Robot configuration code.

motor armMotor = motor(PORT10, ratio18_1, false);
motor LeftDriveSmart = motor(PORT4, ratio6_1, false);
motor RightDriveSmart = motor(PORT5, ratio6_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 317.5, 117.475, mm, 1);

controller Controller1 = controller(primary);

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {Merivale High School}                                    */
/*    Created:      {11/23/2022}                                              */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;
competition Competition;

void runOnAutonomous(void) {
  
}

void spin(void) {
  armMotor.spin(forward);
}

void stop_motor(void) {
  armMotor.stop();
}

void runOnDriverControl(void) {
  Brain.Screen.print("Running teleop");

  armMotor.setVelocity(50, percent);

  
  while (true) {
    // arm 
    Controller1.ButtonL1.pressed(spin);
    Controller1.ButtonL1.released(stop_motor);

    // drivetrain
    if (Controller1.Axis3.position() > 0.0) {
      LeftDriveSmart.setVelocity((Controller1.Axis3.position() + Controller1.Axis4.position())/1.5, percent);
      RightDriveSmart.setVelocity((Controller1.Axis3.position() - Controller1.Axis4.position())/1.5, percent);
    }

    else {
      RightDriveSmart.setVelocity((Controller1.Axis3.position() + Controller1.Axis4.position())/1.5, percent);
      LeftDriveSmart.setVelocity((Controller1.Axis3.position() - Controller1.Axis4.position())/1.5, percent);
    }
    
    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward); 
  }

}

int main() {
  
  runOnDriverControl();
  // Competition.autonomous(runOnAutonomous);
  Competition.drivercontrol(runOnDriverControl);

  while (true) {
    wait(0.05, seconds);
  }

}
