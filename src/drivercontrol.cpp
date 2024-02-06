#include "main.h"
#include "drivercontrol.hpp"
#include "devices.hpp"
#include "pros/rtos.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// . . .
// 
//  DRIVER CONTROL
//
// . . .

void set_drive_to_coast() {
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftTop.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightTop.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void set_drive_to_hold() {
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

double left_curve_function(double x, double left_curve_scale) {
  if (left_curve_scale != 0) {
    // if (CURVE_TYPE)
    return (powf(2.718, -(left_curve_scale / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(left_curve_scale / 10)))) * x;
    // else
    // return powf(2.718, ((abs(x)-127)*RIGHT_CURVE_SCALE)/100)*x;
  }
  return x;
}

void set_tank(int l_stick, int r_stick) {
    leftFront.move_voltage(l_stick * (12000.0 / 127.0));
    leftBack.move_voltage(l_stick * (12000.0 / 127.0));
    leftTop.move_voltage(l_stick * (12000.0 / 127.0));

    rightFront.move_voltage(r_stick * (12000.0 / 127.0));
    rightBack.move_voltage(r_stick * (12000.0 / 127.0));
    rightTop.move_voltage(r_stick * (12000.0 / 127.0));
}

void tank_drive(double curve) {
    // Put the joysticks through the curve function
    int l_stick = left_curve_function(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), curve);
    int r_stick = left_curve_function(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), curve);

    // Set robot to l_stick and r_stick, check joystick threshold, set active brake
    set_tank(l_stick, r_stick);
}

void resetPistons() {
  horzWingsOut = false;
  vertWingsOut = false;
  dropOut = false;

  horzwing.set_value(false);
  vertwing1.set_value(false);
  vertwing2.set_value(false);
  // lift.set_value(false);
}

void toggleHorzWings() {
  horzWingsOut = !horzWingsOut;
  horzwing.set_value(horzWingsOut);
}

void toggleRatchet() {
  isRatchetOut = !isRatchetOut;
  ratchet.set_value(isRatchetOut);
}

void toggleSlapHang() {
  isSlap = !isSlap;
  
}

void setSlapHang(int speed) {
  slapHang1 = speed;
  slapHang2 = speed;
}

void toggleVertWings() {
  vertWingsOut = !vertWingsOut;
  vertwing1.set_value(vertWingsOut);
  vertwing2.set_value(vertWingsOut);
}


// void toggleLift() {
//     liftUp = !liftUp;
//     lift.set_value(liftUp);
//     pros::delay(300);
// }