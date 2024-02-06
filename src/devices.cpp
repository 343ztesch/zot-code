#include "lemlib/api.hpp"
#include "main.h"
#include "devices.hpp"
#include "drivercontrol.hpp"

bool horzWingsOut = false;
bool vertWingsOut = false;
bool isSlap = false;
bool dropOut = false;
bool isRatchetOut = false;
pros::ADIDigitalOut vertwing1('A');
pros::ADIDigitalOut vertwing2('B');
pros::ADIDigitalOut horzwing('C');
pros::ADIDigitalOut ratchet('D');
// pros::ADIDigitalIn limitswitch ('E');


pros::Motor intake (-15, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor slapHang1 (-16, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor slapHang2 (17, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor leftFront(11, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor leftBack(12, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor leftTop(-13, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor rightFront(20, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor rightBack(19, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor rightTop(-10, pros::E_MOTOR_GEARSET_06, true); 

pros::MotorGroup left_side_motors({leftFront, leftBack, leftTop});
pros::MotorGroup right_side_motors({rightFront, rightFront, rightTop});

pros::Imu inertial_sensor(14); 

pros::Controller master(pros::E_CONTROLLER_MASTER);

Drive EzTempChassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-11, -12, 13}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{20, 19, -10}

  // IMU Port
  ,14

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.25


  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);


lemlib::Drivetrain drivetrain (
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    8, // track width
    2.75, // wheel diameter
    450, // wheel rpm
    2 // chase power
);

lemlib::OdomSensors sensors (
    nullptr, 
    nullptr, 
    nullptr, 
    nullptr,
    &inertial_sensor // inertial sensor
);

// forward/backward PID
lemlib::ControllerSettings lateralController (
    0.45, // kP
    5, // kD
    1, // smallErrorRange
    80, // smallErrorTimeout
    3, // largeErrorRange
    300, // largeErrorTimeout
    7 // slew rate
);
 
// turning PID
lemlib::ControllerSettings angularController (
    5, // kP
    35, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
);

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

void checkDTMotorsAndReturnTemperature() {
    std::vector<pros::Motor> motors = {
        leftFront, leftBack, leftTop, rightFront, rightBack, rightTop
    };

    while (true) {
        double totalTemp = 0.0;
        int count = 0;

        for (auto& motor : motors) {
            double temp = motor.get_temperature();
            if (temp == PROS_ERR_F) { // PROS_ERR_F is returned when the motor is unplugged
                master.set_text(0, 0, "Motor " + std::to_string(motor.get_port()) + " unplugged.");
                pros::delay(250);
                master.rumble("---");
            }

            if (count < 6) {
                totalTemp += temp;
            }
            ++count;
        }

        if (count == 0) master.set_text(0, 0, "No motors found.");

        double averageTempCelsius = totalTemp / count;
        double averageTempFahrenheit = averageTempCelsius * 9.0 / 5.0 + 32.0;
        master.set_text(0, 0, "Avg DT Temp: " + std::to_string(averageTempFahrenheit));

        pros::delay(1000);
    }
}

void checkOtherMotorsAndReturnTemperature() {
    std::vector<pros::Motor> motors = {
        intake, slapHang1, slapHang2
    };

    while (true) {
        double totalTemp = 0.0;
        int count = 0;

        for (auto& motor : motors) {
            double temp = motor.get_temperature();
            if (temp == PROS_ERR_F) { // PROS_ERR_F is returned when the motor is unplugged
                master.set_text(0, 0, "Motor " + std::to_string(motor.get_port()) + " unplugged.");
                pros::delay(250);
                master.rumble("---");
            }

            if (count < 6) {
                totalTemp += temp;
            }
            ++count;
        }

        if (count == 0) master.set_text(0, 0, "No motors found.");

        double averageTempCelsius = totalTemp / count;
        double averageTempFahrenheit = averageTempCelsius * 9.0 / 5.0 + 32.0;
        master.set_text(0, 0, "Avg Other Temp: " + std::to_string(averageTempFahrenheit));

        pros::delay(1000);
    }
}


// inits (what are the constants)
void default_constants() {
  EzTempChassis.set_slew_min_power(80, 80);
  EzTempChassis.set_slew_distance(7, 7);
  EzTempChassis.set_pid_constants(&EzTempChassis.headingPID, 11, 0, 20, 0);
  EzTempChassis.set_pid_constants(&EzTempChassis.forward_drivePID, 0.45, 0, 5, 0);
  EzTempChassis.set_pid_constants(&EzTempChassis.backward_drivePID, 0.45, 0, 5, 0);
  EzTempChassis.set_pid_constants(&EzTempChassis.turnPID, 5, 0.003, 35, 15);
  EzTempChassis.set_pid_constants(&EzTempChassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  EzTempChassis.set_slew_min_power(80, 80);
  EzTempChassis.set_slew_distance(7, 7);
  EzTempChassis.set_pid_constants(&EzTempChassis.headingPID, 11, 0, 20, 0);
  EzTempChassis.set_pid_constants(&EzTempChassis.forward_drivePID, 0.45, 0, 5, 0);
  EzTempChassis.set_pid_constants(&EzTempChassis.backward_drivePID, 0.45, 0, 5, 0);
  EzTempChassis.set_pid_constants(&EzTempChassis.turnPID, 5, 0.003, 35, 15);
  EzTempChassis.set_pid_constants(&EzTempChassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  EzTempChassis.set_slew_min_power(80, 80);
  EzTempChassis.set_slew_distance(7, 7);
  EzTempChassis.set_pid_constants(&EzTempChassis.headingPID, 11, 0, 20, 0);
  EzTempChassis.set_pid_constants(&EzTempChassis.forward_drivePID, 0.45, 0, 5, 0);
  EzTempChassis.set_pid_constants(&EzTempChassis.backward_drivePID, 0.45, 0, 5, 0);
  EzTempChassis.set_pid_constants(&EzTempChassis.turnPID, 5, 0.003, 35, 15);
  EzTempChassis.set_pid_constants(&EzTempChassis.swingPID, 7, 0, 45, 0);
}


void modified_exit_condition() {
  EzTempChassis.set_exit_condition(EzTempChassis.turn_exit, 50, 3, 50, 7, 50, 300);
  EzTempChassis.set_exit_condition(EzTempChassis.swing_exit, 50, 3, 50, 7, 50, 300);
  EzTempChassis.set_exit_condition(EzTempChassis.drive_exit, 50, 50, 50, 150, 50, 300);
}

void calibrateBothChassis(bool isLemLib /* defaulted to false in the .h file */) {
    // calibrate the chassis with imu
    if (isLemLib) { chassis.calibrate(); } else { EzTempChassis.initialize(); }
}

void ezTempChassisInits() {
    // EZ temp inits
    EzTempChassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
    EzTempChassis.set_active_brake(0.00625); // Sets the active brake kP. We recommend 0.1.
    EzTempChassis.set_curve_default(6, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
    default_constants(); // Set the drive to your own constants from autons.cpp!
    modified_exit_condition();
}