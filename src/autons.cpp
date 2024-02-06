#include "devices.hpp"
#include "autons.hpp"
#include "drivercontrol.hpp"

//Responisble for all of the autons
void doNothing() {}

ASSET(leftsidequalsv3_txt)
ASSET(elimsLeftPath1_txt)
ASSET(elimsLeftPath2_txt)
ASSET(elimsLeftPath3_txt)
ASSET(elimsLeftPath4_txt)
ASSET(elimsLeftPath5_txt)
ASSET(elimsLeftPath6_txt)
ASSET(rightQualsPath1_txt)
ASSET(rightQualsPath2_txt)
ASSET(rightQualsPath3_txt)
ASSET(rightQualsPath4_txt)
ASSET(rightQualsPath5_txt)
ASSET(rightQualsPath6_txt)
ASSET(rightQualsPath7_txt)
ASSET(rightQualsPath8_txt)
ASSET(rightQualsPath9_txt)

ASSET(skillsPath1_txt)
ASSET(skillsPath2_txt)
ASSET(skillsPath3_txt)

// function definitions

//       chassis.setPose(x, y, theta); 
//       chassis.turnTo(x, y, timeout);    
//       chassis.follow(path file, timeout, lookahead distance, isAsynchronous, forwards (false makes the robot run the path backwards));
//
//       chassis.waitUntil(inches); use this to have your bot wait until the path is finished
//       a really big number means just wait until the path has finished


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;


// Left side auton qualification, gets win point
void leftSideQual() {
    //Start parallel to matchload bar
    EzTempChassis.set_drive_pid(-13, 80);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(RIGHT_SWING, 45, 80);
    pros::delay(100);
    EzTempChassis.wait_drive();
    
    //Score into goal
    EzTempChassis.set_drive_pid(-15, 80); //Pushes ball into goal 
    pros::delay(100);
    EzTempChassis.wait_drive();
    EzTempChassis.set_drive_pid(7, 80); //Comes back to where it was
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_turn_pid(-135, DRIVE_SPEED);
    EzTempChassis.wait_drive();

    pros::delay(200);

    EzTempChassis.set_swing_pid(LEFT_SWING, -190, 80);
    pros::delay(200);
    EzTempChassis.wait_drive();

    
    EzTempChassis.set_drive_pid(-14, 30);
    pros::delay(100);
    EzTempChassis.wait_until(-8);
    vertwing2.set_value(true);
    EzTempChassis.wait_drive();


    //Sweep matchload ball
    EzTempChassis.set_swing_pid(ez::LEFT_SWING, -230, 40); //Turns and pushes the ball out
    EzTempChassis.wait_until(-30);
    vertwing2.set_value(false);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-42, 80);
    pros::delay(100);
    EzTempChassis.wait_drive();
    EzTempChassis.set_drive_pid(8, DRIVE_SPEED);
    EzTempChassis.wait_drive();
    EzTempChassis.set_turn_pid(-45,DRIVE_SPEED);
    EzTempChassis.wait_drive();
    pros::delay(400);

    EzTempChassis.set_drive_pid(11,DRIVE_SPEED);
    EzTempChassis.wait_drive();
    intake = 127;
    pros::delay(5000);
    intake = 0;


    // EzTempChassis.set_drive_pid(-1, DRIVE_SPEED);
    // pros::delay(100);
    // EzTempChassis.wait_drive();
}

void leftSideElims() {
    // Get mid ball 
    horzwing.set_value(true);
    pros::delay(100);
    EzTempChassis.set_drive_pid(57, 127);
    EzTempChassis.wait_until(10);
    intake = -127;
    horzwing.set_value(false);
    EzTempChassis.wait_until(42);
    EzTempChassis.set_drive_pid(15, 25);
    EzTempChassis.wait_drive();

    //Back
    EzTempChassis.set_drive_pid(-52, 127);
    pros::delay(100);
    EzTempChassis.wait_until(-50);

    EzTempChassis.set_turn_pid(77, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(75);

    intake = 127;
    pros::delay(500);

    EzTempChassis.set_drive_pid(-2, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();


//BAR
    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 115, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-18, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(-20);

    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 160, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();
    
    //score alliance triball
    EzTempChassis.set_drive_pid(-11.5, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();
    pros::delay(200);

    EzTempChassis.set_drive_pid(3, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-3, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();
    pros::delay(200);

    EzTempChassis.set_drive_pid(9.5, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 115, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(17, 70);
    pros::delay(100);
    EzTempChassis.wait_drive();
    intake = 127;

    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 75, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();
//Go down aisle
    EzTempChassis.set_drive_pid(40, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-40, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, -15, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(35, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(30);

    pros::delay(5000);
    intake = 0;

}

void rightSideQuals() {
    // lower intake
    intake = -127;

    EzTempChassis.set_drive_pid(-12, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(ez::LEFT_SWING, -45, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-17, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(30, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    /*EzTempChassis.set_swing_pid(ez::LEFT_SWING, 0, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(20, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(ez::LEFT_SWING, 45, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(40, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-30, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_turn_pid(225, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(8, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    wings.set_value(true);
    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 180, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(12, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_turn_pid(135, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();
    wings.set_value(false);

    EzTempChassis.set_drive_pid(-6, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_turn_pid(180, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    intake = -127;
    EzTempChassis.set_drive_pid(20, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 135, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(16, 127);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 180, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-22, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(-20);

    EzTempChassis.set_turn_pid(97, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(95);

    intake = 127;
    EzTempChassis.set_drive_pid(57, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(55);

    EzTempChassis.set_turn_pid(227, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(225);

    EzTempChassis.set_drive_pid(48, 127);
    pros::delay(100);
    EzTempChassis.wait_until(12);
    intake = -127;
    EzTempChassis.wait_drive();
}

void rightSideQualsTouchBar() {
    // lower intake
    intake = 127;

    EzTempChassis.set_drive_pid(-12, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(ez::LEFT_SWING, -45, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-17, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(13, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(ez::LEFT_SWING, 0, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(20, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(ez::LEFT_SWING, 45, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(40, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-30, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_turn_pid(225, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(8, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    wings.set_value(true);
    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 180, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(12, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_turn_pid(135, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();
    wings.set_value(false);

    EzTempChassis.set_drive_pid(-6, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_turn_pid(180, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    intake = -127;
    EzTempChassis.set_drive_pid(20, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 137, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(135);

    EzTempChassis.set_drive_pid(16, 127);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-12, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(-10);


    EzTempChassis.set_turn_pid(47, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(45);

    intake = 0;
    EzTempChassis.set_drive_pid(52, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(50);

    wings.set_value(true);
    EzTempChassis.set_turn_pid(92, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(90); */
}

void rightSideFarRush() {
    horzwing.set_value(true);
    intake = 127;
    EzTempChassis.set_drive_pid(66, 127);
    pros::delay(100);
    EzTempChassis.wait_until(10);
    horzwing.set_value(false);
    EzTempChassis.wait_until(64);

    EzTempChassis.set_drive_pid(-14, 127);
    pros::delay(100);
    EzTempChassis.wait_until(-12);

    EzTempChassis.set_turn_pid(122, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(120);

    intake = -127;
    pros::delay(500);

    EzTempChassis.set_turn_pid(267, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(265);

    intake = 127;

    EzTempChassis.set_drive_pid(10, 127);
    pros::delay(100);
    EzTempChassis.wait_until(8);

    EzTempChassis.set_drive_pid(-18, 127);
    pros::delay(100);
    EzTempChassis.wait_until(-16);

    EzTempChassis.set_turn_pid(122, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(120);

    horzwing.set_value(true);
    EzTempChassis.set_drive_pid(24, 127);
    pros::delay(100);
    EzTempChassis.wait_until(4);
    intake = -127;
    EzTempChassis.wait_drive();
    horzwing.set_value(false);

    EzTempChassis.set_drive_pid(-7, 127);
    pros::delay(100);
    EzTempChassis.wait_until(-5);

    EzTempChassis.set_turn_pid(32, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(30);

    EzTempChassis.set_drive_pid(-45, 127);
    pros::delay(100);
    EzTempChassis.wait_until(-41);

    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 32, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(30);

    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 122, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(120);

    EzTempChassis.set_drive_pid(-15, 127);
    pros::delay(100);
    EzTempChassis.wait_until(-6);
    intake = -127;
    EzTempChassis.wait_until(-13);

    EzTempChassis.set_turn_pid(-62, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(-60);

    intake = 127;

    EzTempChassis.set_drive_pid(13, 127);
    pros::delay(100);
    EzTempChassis.wait_until(10.5);

    EzTempChassis.set_drive_pid(-32, 127);
    pros::delay(100);
    EzTempChassis.wait_until(-30);

    EzTempChassis.set_turn_pid(122, 127);
    pros::delay(100);
    EzTempChassis.wait_until(120);

    horzwing.set_value(true);
    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 75, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(14, 127);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_turn_pid(32, 127);
    pros::delay(100);
    EzTempChassis.wait_until(26);
    horzwing.set_value(false);
    EzTempChassis.wait_until(30);

    intake = -127;
    EzTempChassis.set_turn_pid(55, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(51.5);

    EzTempChassis.set_drive_pid(48, 127);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-12, 127);
    pros::delay(100);
    EzTempChassis.wait_drive();
}

void rightSide6Ball() {
    horzwing.set_value(true);
    intake = 127;
    EzTempChassis.set_drive_pid(66, 127);
    pros::delay(100);
    EzTempChassis.wait_until(10);
    horzwing.set_value(false);
    EzTempChassis.wait_until(64);

    EzTempChassis.set_turn_pid(122, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(120);

    horzwing.set_value(true);
    EzTempChassis.set_drive_pid(40, 127);
    pros::delay(100);
    EzTempChassis.wait_until(4);
    intake = -127;
    EzTempChassis.wait_drive();
    horzwing.set_value(false);

    EzTempChassis.set_swing_pid(ez::LEFT_SWING, 72, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(70);

    EzTempChassis.set_drive_pid(-26, 127);
    pros::delay(100);
    EzTempChassis.wait_until(-24);

    intake = 127;
    EzTempChassis.set_turn_pid(-62, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(-60);

    EzTempChassis.set_drive_pid(11, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(9);

    EzTempChassis.set_turn_pid(-22, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(-20);

    EzTempChassis.set_drive_pid(-28, 127);
    pros::delay(100);
    EzTempChassis.wait_until(-26);

    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 122, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(120);

    EzTempChassis.set_drive_pid(-22, 127);
    pros::delay(100);
    EzTempChassis.wait_until(2);
    intake = -127;
    EzTempChassis.wait_until(20);

    EzTempChassis.set_turn_pid(-62, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(-60);

    intake = 127;

    EzTempChassis.set_drive_pid(12, 127);
    pros::delay(100);
    EzTempChassis.wait_until(10);

    EzTempChassis.set_drive_pid(-32, 127);
    pros::delay(100);
    EzTempChassis.wait_until(-30);

    EzTempChassis.set_turn_pid(122, 127);
    pros::delay(100);
    EzTempChassis.wait_until(120);

    EzTempChassis.set_drive_pid(8, 127);
    pros::delay(100);
    EzTempChassis.wait_until(6);

    horzwing.set_value(true);
    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, 75, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(10, 127);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_turn_pid(32, 127);
    pros::delay(100);
    EzTempChassis.wait_until(26);
    horzwing.set_value(false);
    EzTempChassis.wait_until(30);

    intake = -127;
    EzTempChassis.set_turn_pid(57, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.wait_until(54.5);

    EzTempChassis.set_drive_pid(48, 127);
    pros::delay(100);
    EzTempChassis.wait_drive();

    EzTempChassis.set_drive_pid(-12, 127);
    pros::delay(100);
    EzTempChassis.wait_drive();
}

void skills() {
    //Start with 45 degree bearing NE, back left wheel as close as possible to corner of tile
    //swerve to face the goal
    EzTempChassis.set_swing_pid(ez::LEFT_SWING, -60, DRIVE_SPEED);
    EzTempChassis.wait_drive();
    //deploy vert on right
    vertwing2.set_value(true);
    //shoot matchloads
    //do: shoot: while 11w motor IMU reads less than 23.5 * 360 degrees
    //retract vert wing
    vertwing2.set_value(false);
    //navigate to get under bar
    EzTempChassis.set_swing_pid(ez::LEFT_SWING, 0, DRIVE_SPEED);
    EzTempChassis.wait_drive();
    EzTempChassis.set_drive_pid(6, DRIVE_SPEED);
    EzTempChassis.wait_drive();
    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, -45, DRIVE_SPEED);
    EzTempChassis.wait_drive();
    //drive under bar
    EzTempChassis.set_drive_pid(56, DRIVE_SPEED);
    EzTempChassis.wait_drive();
    //get in front of goal
    EzTempChassis.set_swing_pid(ez::RIGHT_SWING, -(98 + 15), DRIVE_SPEED);
    EzTempChassis.wait_drive();
    EzTempChassis.set_drive_pid(33, DRIVE_SPEED);
    EzTempChassis.wait_drive();
    EzTempChassis.set_swing_pid(ez::LEFT_SWING, -98, DRIVE_SPEED);
    EzTempChassis.wait_drive();
    //turn so back wings face goal
    EzTempChassis.set_turn_pid(-225, TURN_SPEED);
    EzTempChassis.wait_drive();

    //push twice
    vertwing1.set_value(true);
    vertwing2.set_value(true);
    EzTempChassis.set_drive_pid(-27, 127);
    EzTempChassis.wait_drive();
    EzTempChassis.set_drive_pid(27, DRIVE_SPEED);
    EzTempChassis.wait_drive();
    EzTempChassis.set_drive_pid(-27, 127);
    EzTempChassis.wait_drive();



    
}

