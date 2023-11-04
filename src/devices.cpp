#include "main.h"

using namespace okapi;

const double center_radius = 4.0803;

pros::Motor left1(4, MOTOR_GEARSET_06, false);
pros::Motor left2(20, MOTOR_GEARSET_06, false);
pros::Motor left3(18, MOTOR_GEARSET_06, false);
pros::Motor right1(-3, MOTOR_GEARSET_06, true);
pros::Motor right2(-13, MOTOR_GEARSET_06, true);
pros::Motor right3(-14, MOTOR_GEARSET_06, true);

Motor intake(5);
Motor puncher(9);

pros::MotorGroup left_drive({left1, left2, left3});
pros::MotorGroup right_drive({right1, right2, right3});

MotorGroup left_drive_o({4, 20, 18});
MotorGroup right_drive_o({-3, -13, -14});

pros::IMU inertial1(7);
pros::IMU inertial2(10);
pros::IMU inertial3(16);

IMU inertial1_o(7);
IMU inertial2_o(10);
IMU inertial3_o(16);

pros::ADIPort wings('A', ADI_DIGITAL_OUT);
pros::ADIPort latch('B', ADI_DIGITAL_OUT);
okapi::Potentiometer auton_selector('H');

pros::ADIEncoder left_tracker('C', 'D', false);
pros::ADIEncoder back_tracker('E', 'F', false);

lemlib::Drivetrain_t drivetrain { 
	&left_drive,
	&right_drive,
	15.25,
	2.75,
	600
};

lemlib::TrackingWheel left_tracking_wheel(&left_tracker, 2.75, center_radius);
lemlib::TrackingWheel back_tracking_wheel(&back_tracker, 2.75, 0);

lemlib::OdomSensors_t sensors {
	&left_tracking_wheel,
	nullptr,
	&back_tracking_wheel,
	nullptr,
	&inertial1
};

lemlib::ChassisController_t lateralController {27, 1, 1, 100, 3, 500, 5};
lemlib::ChassisController_t angularController {2, 16, 1, 100, 3, 500, 5};

lemlib::Chassis chassis_l(drivetrain, lateralController, angularController, sensors);
