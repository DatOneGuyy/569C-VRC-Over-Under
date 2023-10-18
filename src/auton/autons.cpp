#include "main.h"

using namespace okapi;

void left_auton(void) {

	start_odom(0, 0, 135);
	
	//intake ball and drive forward
	drive_for(580);
	turn_to_angle(90);

	//score preload
	drive_for(520, 2.5);

	//turn around
	drive_for(-200);
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
	set_intake(80);
	drive_for(350);
	pros::delay(200);
	turn_to_angle(0, 0, 1.5, 1.5);
	lower_latch();
	pros::delay(200);
	set_intake(-100);
	drive_for(1150, 0.5);
	set_intake(0);
	raise_latch();
}

void right_auton(void) {
	start_odom(0, 0, -135);
	
	set_intake(100);
	drive_for(550, 0.2, 1, 5000);
	set_intake(0);
	turn_to_angle(-90, 2);

	close_wings();
	set_intake(-100);
	drive_for(500, 1.5);
	pros::delay(500);

	drive_for(-350);
	pros::delay(200);
	lower_latch();
	set_intake(100);
	turn_to_angle(-20);
	pros::delay(400);
	raise_latch();
	drive_for(1500);
	
	pros::delay(500);
	drive_for(-300);
	turn_to_angle(-135);
	set_intake(-100);
	pros::delay(500);
	
	turn_to_angle(-60);
	pros::delay(200);
	set_intake(100);
	drive_for(850);
	pros::delay(200);

	drive_for(-100);
	pros::delay(200);
	turn_to_angle(-170);
	open_wings();
	pros::delay(200);
	set_intake(-100);
	pros::delay(300);
	set_intake(0);
	drive_for(900, 1.5);

	set_intake(0);
	pros::delay(500);
	drive_for(-200);
	close_wings();
}

void skills(void) {
	start_odom(0, 0, 90);

	turn_to_angle(135, 2, 1.5, 2);
	
	drive_for(850, 1.0);
	
	turn_to_angle(90, 1, 1.5, 2);
	push(500);
	
	drive_for(-50);
	turn_to_angle(120, 1, 2, 2);
	turn_to_angle(30, 2);
	turn_to_angle(20, 0, 4, 3);

	start_puncher();
	pros::delay(32000);
	stop_puncher();
	
	turn_to_angle(-45, 1);
	drive_for(750);
	turn_to_angle(0);

	lower_latch();
	pros::delay(200);
	drive_for(2400);
	raise_latch();

	turn_to_angle(35, 2, 3, 3);

	open_wings();
	drive_for(800, 1);
	close_wings();
	turn_to_angle(90, 2, 3, 3);
	push(700, 700);
	drive_for(-200);

	turn_to_angle(155, 0, 1, 1);
	pros::delay(200);
	drive_for(1500, 3);
	open_wings();

	turn_to_angle(90);
	drive_for(500);
	turn_to_angle(0, 1);
	push(1000, 800);

	close_wings();
	drive_for(-800);
	turn_to_angle(90, 0);
	drive_for(800);
	open_wings();
	turn_to_angle(-25, 1, 2, 2);
	open_wings();
	push(1000, 800);
	drive_for(-200);
	
	/*
	turn_to_angle(90);
	drive_for(-400, 2.5, 2);
	pros::delay(400);
	chassis_l.setPose(chassis_l.getPose().rotate(90 - chassis_l.getPose().theta));

	drive_for(500);
	turn_to_angle(180, 2, 2);
	drive_for(500);
	turn_to_angle(90, 1, 2);
	drive_for(400);

	open_wings();
	turn_to_angle(0, 1);
	drive_for(1100, 2.0);
	close_wings();

	drive_for(-300);
	turn_to_angle(-90, 2);
	drive_for(-400);
	turn_to_angle(0, 1);
	drive_for(-400, 4);
	chassis_l.setPose(chassis_l.getPose().rotate(90 - chassis_l.getPose().theta));
	open_wings();
	drive_for(1000, 2.0);
	drive_for(-300);
	*/
}