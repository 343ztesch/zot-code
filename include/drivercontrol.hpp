#pragma once

#include "pros/rtos.hpp"
#include "lemlib/api.hpp"

// . . .
// 
//  DRIVER CONTROL: What are the functions
//
// . . .
void resetPistons();
void toggleHorzWings();
void toggleVertWings();
// void toggleLift();
bool getShiftKey();
// void drop();
void setSlapHang(int speed);
void toggleRatchet();
void toggleSlapHang();
void tank_drive(double curve = 6.0);
void set_drive_to_coast();
void set_drive_to_hold();