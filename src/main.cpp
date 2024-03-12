#include "main.h"

using namespace okapi;

int program = 0;
double intake_speed = 0;
double initial_speed = 45;
bool driving = false;
bool shooting = false;

const double scale = 2.75 / 3.25;

void initialize() {
    inertial1.reset(true);
    controller.rumble(".");
}

void disabled() {
    lower_elevation();
}

void competition_initialize() {
    while (!driving) {
        pros::screen::print(TEXT_MEDIUM, 0, "Angle: %f", inertial1.get_rotation());

        if (auton_selector.get() < 100) {
            pros::screen::print(TEXT_MEDIUM, 1, "Safe AWP\t\t\t\t\t");
        } else if (auton_selector.get() < 1000) {
            pros::screen::print(TEXT_MEDIUM, 1, "Disruption AWP\t\t\t\t\t");
        } else if (auton_selector.get() < 2000) {
            pros::screen::print(TEXT_MEDIUM, 1, "Disruption\t\t\t\t\t");
        } else if (auton_selector.get() < 3000) {
            pros::screen::print(TEXT_MEDIUM, 1, "Safe far WP\t\t\t\t\t");
        } else if (auton_selector.get() < 4000) {
            pros::screen::print(TEXT_MEDIUM, 1, "Safe 6 ball\t\t\t\t\t");
        } else {
            pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Skills\t\t\t\t\t");
        }
        pros::delay(20);
    }
}

void autonomous() {
    driving = false;

    left_drive_o.setBrakeMode(AbstractMotor::brakeMode::hold);
    right_drive_o.setBrakeMode(AbstractMotor::brakeMode::hold);
    left_drive_o.setGearing(AbstractMotor::gearset::blue);
    right_drive_o.setGearing(AbstractMotor::gearset::blue);

    if (auton_selector.get() < 100) {
        program = 0;
    } else if (auton_selector.get() < 1000) {
        program = 4;
    } else if (auton_selector.get() < 2000) {
        program = 3;
    } else if (auton_selector.get() < 3000) {
        program = 5;
    } else if (auton_selector.get() < 4000) {
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
        case 3:
            disruption();
            break;
        case 4:
            disruption_wp();
            break;
        case 5:
            safe_far_wp();
            break;
    }
}

void opcontrol() {
    bool elevation_timer = false;
    bool warning_timer = false;
    bool skills_autohang = false;
    int start = pros::millis();
    driving = true;

    pros::Task puncher_task(run_puncher);
    pros::Task descorer_task(run_descorer);
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

        if (DOWN.changedToReleased()) {
            pros::Task intake_deploy_task(run_intake_deploy);
        }

		pros::delay(20);
	}
}
