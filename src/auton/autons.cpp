#include "main.h"
#include "auton/odom.hpp"
#include "okapi/api.hpp"
#include "auton/autons.hpp"

using namespace okapi;

void clear_screen(void) {
	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::fill_rect(0, 0, 480, 240);
}

void right_auton(void) {
	pros::Task intake_auton_task(intake_auton);

	start_odom(0, 0, 3 * pi / 4);
	intake_speed = 8000;
	drive_for(400);
	turn_to_angle(90);
	intake_speed = -12000;
	drive_for(500);
	pros::screen::print(pros::E_TEXT_MEDIUM, 10, "Completed");
	
}

void left_auton(void) {
	
}

void skills(void) { 
	
}