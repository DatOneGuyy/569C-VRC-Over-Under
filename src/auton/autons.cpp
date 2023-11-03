#include "main.h"

using namespace okapi;

void left_auton(void) {

	start_odom(0, 0, 135);
	
	//intake ball and drive forward
	drive_for(350, 0.8, 0.3);
	pros::delay(200);
	turn_to_angle(90, 1);

	drive_for(300);

	//turn around
	drive_for(-80, 0.4, 0.4);
	turn_to_angle(-60, 0);
	
	pros::delay(200);

	//remove match load ball
	
	open_wings();
	drive_for(350, 0.4, 0.4);
	turn_to_angle(-10, 0, 1, 4);
	turn_to_angle(0, 2, 2, 2);
	

	//push ball to offensive zone
	pros::delay(200);
	
	close_wings();
	drive_for(1000, 0.4);
}

void right_auton(void) {	
	start_odom(0, 0, -135);
	
	drive_for(350, 0.8, 0.3);
	pros::delay(200);
	turn_to_angle(-90, 2, 1.5);

	drive_for(300, 3);

	drive_for(-200);
	pros::delay(200);
	lower_latch();
	set_intake(100);
	turn_to_angle(-20, 0, 1, 2);
	pros::delay(400);
	drive_for(1000);
	
	pros::delay(500);
	drive_for(-200);
	pros::delay(200);
	turn_to_angle(-140);
	set_intake(-100);
	pros::delay(500);
	
	turn_to_angle(-55);
	pros::delay(200);
	set_intake(100);
	drive_for(400, 0.8, 0.3);
	pros::delay(200);

	drive_for(-100);
	pros::delay(200);
	turn_to_angle(-170);
	open_wings();
	pros::delay(200);
	set_intake(-100);
	pros::delay(300);
	set_intake(0);
	drive_for(800, 4);

	set_intake(0);
	pros::delay(500);
	drive_for(-200);
	close_wings();
}

void skills(void) {
	/*
	start_odom(0, 0, 90);

	turn_to_angle(135, 2, 1.5, 2);
	
	drive_for(1100);
	
	turn_to_angle(90, 1, 2, 2);
	push(500);
	
	drive_for(-50);
	turn_to_angle(120, 1, 2, 2);
	turn_to_angle(30, 2);
	turn_to_angle(27, 0, 4, 3);

	start_puncher();
	pros::delay(000);
	stop_puncher();
	
	turn_to_angle(-45, 1);
	drive_for(750, 0.8, 0.4);

	pros::delay(200);
	turn_to_angle(0);

	lower_latch();
	pros::delay(200);
	drive_for(2500, 0.8, 0.4);
	raise_latch();

	turn_to_angle(35, 0, 1.5);

	drive_for(1100, 3, 1.5);
	turn_to_angle(70, 0, 3, 3);
	pros::delay(200);
	
	drive_for(400);
	push(600, 1000, 300);
	drive_for(-250);

	
	turn_to_angle(165, 0);
	
	pros::delay(200);
	drive_for(1500);
	
	turn_to_angle(90, 0);
	pros::delay(200);
	
	open_wings();
	drive_for(500);
	pros::delay(200);
	turn_to_angle(10, 0, 0.5);
	pros::delay(200);
	
	push(600, 600, 200);

	close_wings();
	drive_for(-900);
	
	pros::delay(200);
	turn_to_angle(90, 0, 0.6);
	
	set_intake(100);
	drive_for(700);
	open_wings();
	turn_to_angle(-15, 1, 2, 2);
	open_wings();
	set_intake(-100);
	push(600, 800, 500);
	drive_for(-200);
	set_intake(0);
	*/
	
	start_odom(0, 0, 0);
	chassis_l.moveTo(-12, 14, 10, 3000, false, true, 0.6, 0.1, 200);
	push(400);
	
	chassis_l.moveTo(-4, 9, -40, 3000, false, false, 0.6, 0.1, 200);
	pros::delay(200);
	chassis_l.turnTo(75, 40, 1000, false, false, 200);
	lower_latch();
	drive_for(-100, 0.4, 0.2);
	start_puncher();
	pros::delay(2000);
	stop_puncher();
	raise_latch();
	chassis_l.moveTo(0, 0, 85, 3000, false, true, 0.6, 0.1, 200);
	
	chassis_l.moveTo(30, 3, 90, 5000, false,true, 1, 0.1, 200);
	//open_wings();
	chassis_l.moveTo(35, 7, 0, 4000, false, true, 0.6, 0.1, 200);
	chassis_l.moveTo(25, 10, -80, 4000, false, true, 0.6, 0.1, 200);
	open_wings();
	chassis_l.moveTo(18, 21, 10, 3000, false, true, 1, 0.1, 200);
	chassis_l.turnTo(2000000, 21, 1500, false, false, 100);
	push(800, 500, 400, 500);
	chassis_l.turnTo(18, 700000000, 800, false, false, 200);
	
	open_wings();
	drive_for(500);
	turn_to_angle(-140, 1);
	drive_for(300);
	turn_to_angle(-90, 2);
	push(800, 800, 400, 800);
	turn_to_angle(-25, 2);
	
	drive_for(800);
	open_wings();
	turn_to_angle(-160, 1);
	close_wings();
	push(800, 500, 200, 400);
	//chassis_l.moveTo(15, 60, 0, 3000, false, true, 0.6, 0.1, 200);
	//chassis_l.turnTo(50, 35, 3000, false, false, 200);
	//push(800, 500, 400, 500);
	//lower_latch();
	//chassis_l.moveTo(40, 45, -90, 2000, false, false, 0.6, 0.1, 200);
	//chassis_l.moveTo(40, 90, 0, 2000, false, true, 0.6, 0.1, 200);
	//push(800, 500);
	
}