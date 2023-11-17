#include "main.h"

using namespace okapi;

int program;
double intake_speed;
bool driving = false;
  
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize(void) {
	chassis_l.calibrate();
	inertial1_o.calibrate();
	inertial2_o.calibrate();
	inertial3_o.calibrate();
	pros::Task report_angle_task(report_angle);
	auton_selector.setLedPWM(50);
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
	driving = false;

	if (auton_selector.getHue() > 200 && auton_selector.getHue() < 260) {
		program = 0;
	} else {
		if (auton_selector.getSaturation() > 0.4) {
			program = 1;
		} else {
			program = 2;
		}
	}

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
	pros::Task run_drive(drive_task);
	pros::Task run_elevation(elevation_task);
	pros::Task run_wings(wings_task);
	pros::Task run_latch(latch_task);
	pros::Task run_intake(intake_task);
	pros::Task run_puncher(puncher_task);
	pros::Task run_blocker(blocker_task);

	auton_selector.setLedPWM(0);

	if (program == 2) {
		raise_blocker();
		pros::delay(300);
		lower_latch();
		pros::delay(500);
		raise_latch();
		lower_blocker();
	} else if (program == 0) {
		pros::delay(300);
		raise_blocker();
		pros::delay(300);
		lower_latch();
		pros::delay(500);
		raise_latch();
		lower_blocker();
	}

	while (true) {
		pros::screen::print(TEXT_MEDIUM, 0, "Position: %f, %f", chassis_l.getPose(true).y, chassis_l.getPose(true).x);
		pros::screen::print(TEXT_MEDIUM, 1, "Angle: %f deg", chassis_l.getPose(false).theta);
		pros::screen::print(TEXT_MEDIUM, 2, "Encoder: L: %d", left_tracker.get_value());
		pros::screen::print(TEXT_MEDIUM, 3, "Center: %d", back_tracker.get_value());
		pros::screen::print(TEXT_MEDIUM, 4, "Saturation: %f", auton_selector.getSaturation());
		pros::screen::print(TEXT_MEDIUM, 5, "Hue: %f", auton_selector.getHue());
		pros::delay(100);
	}
}
