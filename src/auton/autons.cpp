#include "main.h"

using namespace okapi;

void right_auton(void) {
	pros::Task run_intake_auton(intake_auton_task);

	start_odom(0, 0, 135);
	
	//intake ball and drive forward
	lower_latch();
	intake_speed = 80;
	drive_for(550);
	turn_to_angle(90);

	//score preload
	intake_speed = -100;
	raise_latch();
	drive_for(520);

	//turn around
	drive_for(-150);
	turn_to_angle(-70);
	
	pros::delay(200);

	//remove match load ball
	drive_for(130);
	turn_to_angle(-50, 2);
	open_wings();
	pros::delay(200);
	drive_for(220);

	//push ball to offensive zone
	pros::delay(200);
	turn_to_angle(-15, 0, 1.5, 1.5);
	close_wings();
	turn_to_angle(-50);
	intake_speed = 80;
	drive_for(250);
	pros::delay(200);
	turn_to_angle(0, 0, 1.5, 1.5);
	pros::delay(200);
	intake_speed = -100;
	lower_latch();
	drive_for(950);
	
}

void left_auton(void) {
	start_odom(0, 0, -135);
	drive_for(-500);
}

void skills(void) { 
	
}