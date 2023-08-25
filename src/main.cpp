#include "main.h"
#include "okapi/api.hpp"
#include "pros/screen.h"

using namespace okapi;

bool driving;

bool r = true;
bool l = false;

int program;

double final_speed = 0;

pros::Motor left1(4);
pros::Motor left2(20);
pros::Motor left3(18);
pros::Motor right1(3);
pros::Motor right2(13);
pros::Motor right3(16);

pros::MotorGroup left_drive({left1, left2, left3});
pros::MotorGroup right_drive({right1, right2, right3});


lemlib::Drivetrain_t drivetrain { 
	&left_drive,
	&right_drive,
	15.25,
	2.75,
	600
};

pros::ADIEncoder left_tracker('C', 'D', true);
pros::ADIEncoder right_tracker('A', 'B', true);
pros::ADIEncoder back_tracker('E', 'F', false);
pros::IMU inertial_p(16);

lemlib::TrackingWheel left_tracking_wheel(&left_tracker, 2.75, -5.0 * 184 / 180);
lemlib::TrackingWheel right_tracking_wheel(&right_tracker, 2.75, 5.0 * 184 / 180);
lemlib::TrackingWheel back_tracking_wheel(&back_tracker, 2.75, 5.125);

lemlib::OdomSensors_t sensors {
	&left_tracking_wheel,
	&right_tracking_wheel,
	&back_tracking_wheel,
	nullptr,
	&inertial_p
};

lemlib::ChassisController_t lateralController {8, 30, 1, 100, 3, 500, 5};
lemlib::ChassisController_t angularController {4, 40, 1, 100, 3, 500, 40};

lemlib::Chassis chassis_l(drivetrain, lateralController, angularController, sensors);

//std::shared_ptr<okapi::ChassisController> chassis = ChassisControllerBuilder().withMotors({4, 20, 18}, {-3, -11, -16}).build();
    
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize(void) {/*
	IMU inertial(16, IMUAxes::z);
	IMU inertial2(12, IMUAxes::z);
	IMU inertial3(19, IMUAxes::z);

	inertial.calibrate();
	inertial2.calibrate();
	inertial3.calibrate();

	while (inertial.isCalibrating() || inertial2.isCalibrating() || inertial3.isCalibrating()) {
		pros::delay(200);
	}*/
	chassis_l.calibrate();
	pros::delay(3000);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled(void) {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize(void) {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous(void) {
	program = 0;

	bool driving = false;

	switch (program) {
		case 0:
			left_auton();
			break;
		case 1:
			right_auton();
			break;
		case 2:
			skills();
			break;
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol(void) {
	driving = true;
	pros::Task run_drive(drive_task);
	pros::Task run_pneumatics(elevation_task);
	pros::Task run_wings(wings_task);
	pros::Task run_scraper(scraper_task);
	pros::Task run_intake(intake_task);
	pros::Task run_puncher(puncher_task);

	while (true) {
		pros::screen::print(pros::E_TEXT_MEDIUM, 0, "Position: %f, %f", chassis_l.getPose(true).x, chassis_l.getPose(true).y);
		pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Angle: %f deg", chassis_l.getPose(false).theta);
		pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Encoders: L - %d, R - %d", left_tracker.get_value(), right_tracker.get_value());
		pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Center: %d", back_tracker.get_value());
		pros::delay(100);
	}
}
