#include "main.h"

using namespace okapi;

int program = 0;
double intake_speed = 0;
double initial_speed = 45;
bool driving = false;
bool shooting = false;

void initialize() {
    inertial1.reset(true);
    controller.rumble(".");
}

void disabled() {}

void competition_initialize() {
    while (!driving) {
        pros::screen::print(TEXT_MEDIUM, 0, "Angle: %f", inertial1.get_rotation());
        pros::delay(20);
    }
}

void autonomous() {
    driving = false;

    left_drive_o.setBrakeMode(AbstractMotor::brakeMode::hold);
    right_drive_o.setBrakeMode(AbstractMotor::brakeMode::hold);
    left_drive_o.setGearing(AbstractMotor::gearset::blue);
    right_drive_o.setGearing(AbstractMotor::gearset::blue);

    //test();

    if (auton_selector.get() < 100) {
        program = 0;
    } else if (auton_selector.get() < 4000) {
        program = 1;
    } else {
        program = 2;
    }

    //program = 3;
    
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
        case 3:
            disruption();
            break;
    }
}

void opcontrol() {
    bool elevation_timer = false;
    bool warning_timer = false;
    bool skills_autohang = true;
    int start = pros::millis();
    driving = true;

    pros::Task puncher_task(run_puncher);
    pros::Task latch_task(run_latch);
    pros::Task wings_task(run_wings);
    pros::Task elevation_task(run_elevation);
    pros::Task drive_task(run_drive);
    pros::Task intake_task(run_intake);

	while (driving) {
        if (pros::millis() - start > 90000 && !elevation_timer) {
            controller.rumble("---");
            elevation_timer = true;
        }

        if (pros::millis() - start > 60000 && !warning_timer) {
            controller.rumble("...");
            warning_timer = true;
        }


        if (pros::millis() - start > 50000 && !skills_autohang && program == 2) {
            controller.rumble("--");
            toggle_elevation();
            skills_autohang = true;
        }

		pros::delay(20);
	}
}
