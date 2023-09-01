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
	pros::Task run_intake_auton(intake_auton_task);

	start_odom(0, 0, 3 * pi / 4);
	lower_latch();
	intake_speed = 80;
	drive_for(400);
	turn_to_angle(90);
	intake_speed = -100;
	raise_latch();
	drive_for(500);
	drive_for(-300);
	turn_to_angle(-80);
	pros::delay(200);
	drive_for(100);
	turn_to_angle(-60);
	open_wings();
	pros::delay(200);
	drive_for(500);
	close_wings();
	turn_to_angle(0);
	lower_latch();
	drive_for(800);
	
}

void left_auton(void) {
	
}

void skills(void) { 
	
}