#include "main.h"

using namespace okapi;

void clear_screen(void) {
	pros::screen::set_pen(COLOR_BLACK);
	pros::screen::fill_rect(0, 0, 480, 240);
}

void right_auton(void) {
	pros::Task run_intake_auton(intake_auton_task);

	start_odom(0, 0, 135);
	
	//intake ball and drive forward
	lower_latch();
	intake_speed = 80;
	drive_for(400);
	turn_to_angle(90);

	//score preload
	intake_speed = -100;
	drive_for(500);

	//turn around
	drive_for(-200);
	turn_to_angle(-70);
	pros::delay(200);

	//remove match load ball
	drive_for(200);
	open_wings();
	turn_to_angle(-60);
	pros::delay(200);
	open_wings();
	drive_for(700);

	//push ball to offensive zone
	turn_to_angle(0);
	pros::delay(200);
	drive_for(800);
	
}

void left_auton(void) {
	start_odom(0, 0, 135);
	open_wings();
	drive_for(400);
}

void skills(void) { 
	
}