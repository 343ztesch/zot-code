#pragma once

#include "main.h"
#include "lemlib/api.hpp"

extern pros::Controller master;

extern pros::Motor intake;
extern pros::Motor slapHang1;
extern pros::Motor slapHang2;

extern pros::Motor rightFront;
extern pros::Motor rightBack;
extern pros::Motor rightTop;

extern pros::Motor leftFront;
extern pros::Motor leftBack;
extern pros::Motor leftTop;

extern pros::ADIDigitalOut vertwing1;
extern pros::ADIDigitalOut vertwing2;
extern pros::ADIDigitalOut horzwing;
extern pros::ADIDigitalOut ratchet;
// extern pros::ADIDigitalIn limitswitch;

extern bool horzWingsOut;
extern bool vertWingsOut;
extern bool dropOut;
extern bool isSlap;
extern bool isRatchetOut;

extern lemlib::Chassis chassis;

extern Drive EzTempChassis;

void checkDTMotorsAndReturnTemperature();
void checkOtherMotorsAndReturnTemperature();
void calibrateBothChassis(bool isLemLib = false);
void ezTempChassisInits();

// Change Pneumatic, Motor Names, Motor Temp name
