#include "main.h"

using namespace okapi;

double intake_speed = 0;

void left_auton(void) {
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
	drive_for(520, 1.5);

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
	drive_for(1150, 0.5);
	intake_speed = 0;
	raise_latch();
	
}

void right_auton(void) {
	pros::Task run_intake_auton(intake_auton_task);
	start_odom(0, 0, -135);

	lower_latch();
	intake_speed = 100;
	pros::delay(200);
	drive_for(750, 0.2, 1, 5000);
	turn_to_angle(-90);

	intake_speed = -100;
	raise_latch();
	drive_for(500, 1.5);
	pros::delay(500);

	drive_for(-350);
	intake_speed = 100;
	pros::delay(200);
	turn_to_angle(-20);
	pros::delay(400);
	drive_for(1500);
	
	pros::delay(500);
	drive_for(-300);
	turn_to_angle(-135);
	intake_speed = -100;
	pros::delay(500);
	
	turn_to_angle(-60);
	pros::delay(200);
	intake_speed = 100;
	drive_for(850);
	pros::delay(200);

	drive_for(-100);
	pros::delay(200);
	turn_to_angle(-170);
	open_wings();
	pros::delay(200);
	intake_speed = -100;
	pros::delay(300);
	intake_speed = 0;
	drive_for(900, 1.5);

	intake_speed = 0;
	pros::delay(500);
	drive_for(-200);
	close_wings();
}

void skills(void) { 
	pros::Task run_intake_auton(intake_auton_task);
	start_odom(0, 0, 90);

	open_wings();
	turn_to_angle(135, 2);
	close_wings();
	pros::delay(200);
	drive_for(700, 1.0);
	turn_to_angle(90, 1);
	drive_for(400, 2.5);

	drive_for(-50);
	pros::delay(300);
	turn_to_angle(135, 1, 0.9, 1.5);
	pros::delay(200);
	drive_for(-500);
	pros::delay(200);
	turn_to_angle(45);
	drive_for(-300);
	turn_to_angle(30, 1, 0.9, 1.5);

	start_puncher();
	pros::delay(3000);
	stop_puncher();

	turn_to_angle(-30, 1, 0.9, 1.5);
	drive_for(300);
	turn_to_angle(0, 2, 3.0, 1.5);

}