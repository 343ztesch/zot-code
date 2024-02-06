#include "main.h"
#include "lemlib/api.hpp"
#include "drivercontrol.hpp"
#include "devices.hpp"
#include "autons.hpp"
#include "gif-pros/gifclass.hpp"
#include "screen.hpp"
#include "display/lvgl.h" 

// Enter your autons here!
AutonFunction autonFunctions[] = {
    {"Skills Prog", skills},
    {"Left Elims", leftSideElims},
    {"Left Quals", leftSideQual},

    /*
    {"Right Far Rush", rightSideFarRush},
    {"Right 5 Ball", rightSideQuals},
    {"Right 3 Bar", rightSideQualsTouchBar},
    {"Right 6 Ball", rightSide6Ball},
    {"Skills", skills}
    */
};

// this is needed for LVGL displaying! Do not touch!
size_t autonCount = sizeof(autonFunctions) / sizeof(autonFunctions[0]);

// these are the gifs that will display randomly for the calibration screen
std::string calibrationGifs[] = {
                "/usd/jq-griddy.gif", 
                "/usd/dog-angry.gif", 
                "/usd/did-you-pray-today.gif", 
                "/usd/beast-boy.gif", 
            };

// these are the gifs that will display randomly during the match
std::string matchGifs[] = {
                "/usd/getreal.gif", 
                "/usd/minecraft-sky-parkour.gif", 
            };

void initialize() {
    ez::print_ez_template();

    pros::delay(500); // Stop the user from doing anything while legacy ports configure.
 
	// screen init
    calibrationScreenInit();

    // calibrate the lem lib x ez temp chassis
    calibrateBothChassis();

    // auton selector
    autonSelectorScreenInit(
        // your auton funcitons
        autonFunctions, 
        // auton count needed for LVGL displaying
        autonCount, 
        // customizable color scheme, play around with it!
        LV_COLOR_MAKE(0xFF, 0x00, 0x00)

    );

    // pid and curve inits
    ezTempChassisInits();
    
    // MY INITS
    // resets all pistons to false
    resetPistons();
    ratchet.set_value(true);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {} 

/**
 * Runs after initialize(), and before autonomous when connected to the Field

 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 */
void autonomous() {
    EzTempChassis.reset_pid_targets(); // Resets PID targets to 0
    EzTempChassis.reset_gyro(); // Reset gyro position to 0
    EzTempChassis.reset_drive_sensor(); // Reset drive sensors to 0
    EzTempChassis.set_drive_brake(pros::E_MOTOR_BRAKE_HOLD); // Set motors to hold.

    runSelectedAuton(autonFunctions, autonCount);
}

/**
 * Runs the operator control code. This function will be started in its own task
 */


// Debounce Code
bool wasR1PressedLast = false;
bool wasR2PressedLast = false;

void opcontrol() {
    // reset all pistons to false
    resetPistons();

    // task to make sure all motors are plugged in and check the temperature of the drivetrain
    pros::Task motorCheckDT(checkDTMotorsAndReturnTemperature);
    pros::Task motorCheckOther(checkOtherMotorsAndReturnTemperature);
    


    // Driver Skills Code (COMMENT OUT when not doing skills)
    // EzTempChassis.set_drive_brake(pros::E_MOTOR_BRAKE_HOLD);
    // pros::Task skillsTask([]() {
    //     skills();
    // });

    // leftFront.move_velocity(0);
    // leftBack.move_velocity(0);
    // leftTop.move_velocity(0);
    // rightFront.move_velocity(0);
    // rightBack.move_velocity(0);
    // rightTop.move_velocity(0);
    // Wait for any button press to interrupt skills
    // bool interrupted = false;
    // while (!interrupted) {
    //     for (int button = pros::E_CONTROLLER_DIGITAL_L1; button <= pros::E_CONTROLLER_DIGITAL_Y; button++) {
    //         if (master.get_digital_new_press(static_cast<pros::controller_digital_e_t>(button))) {
    //             interrupted = true;
    //             skillsTask.remove(); // Stop the skills task
                
    //             break;
    //         }
    //     }
    //     pros::delay(20); // Small delay to prevent hogging CPU
    // }
    // END OF SKILLS AUTO CODE

    EzTempChassis.set_drive_brake(pros::E_MOTOR_BRAKE_COAST);
	while (true) {
        tank_drive(
            // OPTIONAL:
            // adjust curve (DEFAULT IS 4.0):
            // <curve_value_here>
        );
        
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) { 
            toggleSlapHang();
            pros::delay(250);
        } 

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { 
            toggleRatchet();
            pros::delay(250);
        }

        bool isR1Pressed = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
        bool isR2Pressed = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
        if (isR1Pressed && !wasR1PressedLast) {
            toggleVertWings();
        }
        wasR1PressedLast = isR1Pressed;

        // Toggle Horz Wings on rising edge of DOWN button press
        if (isR2Pressed && !wasR2PressedLast) {
            toggleHorzWings();
        }
        wasR2PressedLast = isR2Pressed;   

        

        if (!isSlap) {
            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) { 
                setSlapHang(127); 
            } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) { 
                setSlapHang(-127); 
            } else { 
                setSlapHang(0);
            }
        } else {
            setSlapHang(-85);
        }      

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { 
            intake = 127; 
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { 
            intake = -127; 
        } else { 
            intake = 0; 
        }   

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) { 
            motorCheckDT.suspend(); 
            motorCheckOther.suspend(); 
        }

		pros::delay(ez::util::DELAY_TIME);
	}
}

int matchGifsSize = sizeof(matchGifs) / sizeof(matchGifs[0]);
int calibrationGifsSize = sizeof(calibrationGifs) / sizeof(calibrationGifs[0]);