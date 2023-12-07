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


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor armMotor = motor(PORT10, ratio18_1, false);
motor armMotor2 = motor (PORT9, ratio18_1, false);
motor LeftDriveSmart = motor(PORT7, ratio6_1, false);
motor RightDriveSmart = motor(PORT8, ratio6_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 317.5, 117.475, mm, 1);

//configure controllers
controller Controller1 = controller(primary);




// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

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
  Brain.Screen.print("Running auto");
  LeftDriveSmart.setVelocity(100, percent);
  RightDriveSmart.setVelocity(100, percent);
  // score first ball
  Drivetrain.driveFor(forward, 120, inches);
  Drivetrain.turnFor(right, 220, degrees);
  Drivetrain.driveFor(forward, 40, inches);
  // 
}

//spin function
void spin(void) {
    //motor on port 10 is forward and motor in port 9 is in reverse on nov 17
    armMotor.spin(forward);
    armMotor2.spin(reverse);
  }

void spinrev(void) {
  //motor on port 9 is forward and motor in port 10 is in reverse on nov 17
    armMotor.spin(reverse);
    armMotor2.spin(forward);
}

void stop_motor(void) {
  armMotor.stop();
  armMotor2.stop();
}

void runOnDriverControl(void) {
  Brain.Screen.setFont(mono20);
  Brain.Screen.print("Running teleop");

  armMotor.setVelocity(25, percent);
  armMotor2.setVelocity(25, percent);

  while (true) {
    
    Controller1.ButtonL1.pressed(spin);
    Controller1.ButtonL1.released(stop_motor);
    Controller1.ButtonR1.pressed(spinrev);
    Controller1.ButtonR1.released(stop_motor);
    Brain.Screen.setCursor(500,-100);
    Brain.Screen.clearScreen();
    Brain.Screen.setPenColor(blue);
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(0, 0, 100, 100);

    
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
  runOnAutonomous();
//   // runOnDriverControl();
  // Competition.autonomous(runOnAutonomous);
  Competition.drivercontrol(runOnDriverControl);

  while (true) {
    wait(0.05, seconds);
  }

}
