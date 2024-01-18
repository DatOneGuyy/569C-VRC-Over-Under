#include "main.h"

using namespace okapi;

int program = 0;
double intake_speed = 0;
bool driving = false;
bool shooting = false;

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    driving = false;

    left_drive_o.setBrakeMode(AbstractMotor::brakeMode::coast);
    right_drive_o.setBrakeMode(AbstractMotor::brakeMode::coast);

    //test();

    if (auton_selector.get() < 30) {
        program = 0;
    } else if (auton_selector.get() < 500) {
        program = 1;
    } else {
        program = 2;
    }
    
    switch (program) {
        case 0:
            close_auton();
            break;
        case 1:
            far_auton();
            break;
        case 2:
            skills();
            break;
    }
}

void opcontrol() {
    bool elevation_timer = false;
    bool warning_timer = false;
    int start = pros::millis();
    driving = true;

    pros::Task puncher_task(run_puncher);
    pros::Task latch_task(run_latch);
    pros::Task wings_task(run_wings);
    pros::Task elevation_task(run_elevation);
    pros::Task drive_task(run_drive);
    pros::Task intake_task(run_intake);

	while (true) {
        if (A.changedToReleased()) {
            test();
        }

        if (pros::millis() - start > 90000 && !elevation_timer) {
            controller.rumble("---");
            elevation_timer = true;
        }

        if (pros::millis() - start > 45000 && !warning_timer) {
            controller.rumble("...");
            warning_timer = true;
        }

		pros::delay(20);
	}
}
