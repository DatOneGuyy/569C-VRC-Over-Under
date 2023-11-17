#include "main.h"

using namespace okapi;

ASSET(left_txt);
ASSET(preloads_txt);
ASSET(right_txt);
ASSET(side_txt);

void left_auton(void) {
	

	start_odom(0, 0, 135);
	
	//intake ball and drive forward
	drive_for(600, 0.4, 0.3);
	pros::delay(200);
	turn_to_angle(90, 1);

	drive_for(500, 4);

	//turn around
	drive_for(-150, 0.4, 0.4);
	turn_to_angle(-60, 0);
	
	pros::delay(200);

	//remove match load ball
	
	open_wings();
	drive_for(650);
	turn_to_angle(-20, 0, 3, 3);
	

	//push ball to offensive zone
	pros::delay(200);
	
	close_wings();
	drive_for(1700, 0.3);
	/**/
}

void right_auton(void) {
	start_odom(0, 0, -135);
	
	set_intake(100);
	drive_for(550, 0.4);
	turn_to_angle(-90, 2);

	push(500);
	pros::delay(500);

	drive_for(-350, 0.4, 0.3);
	pros::delay(200);
	set_intake(100);
	
	raise_blocker();
	turn_to_angle(-20);
	
	lower_latch();
	pros::delay(400);
	drive_for(1600, 0.8, 0.3);
	raise_latch();
	lower_blocker();
	
	pros::delay(500);
	drive_for(-100);
	pros::delay(200);
	turn_to_angle(-140);
	set_intake(-100);
	pros::delay(500);
	
	turn_to_angle(-60);
	pros::delay(200);
	set_intake(100);
	drive_for(750, 0.8, 1);
	pros::delay(500);
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
	
	/**/
}

void skills(void) {	
	chassis_l.setPose(-36, -60, 0);
	//chassis_l.follow(preloads_txt, 3000, 5, false, true, 80);
	chassis_l.moveTo(-64, -42, 0, 3000, false, true, 0.6, 0.1, 100);

	push(500);

	chassis_l.moveTo(-56, -48, -40, 3000, false, false, 0.6, 0.1, 100);
	raise_blocker();
	chassis_l.turnTo(50, -10, 1000, false, false, 127);
	drive_for(-100, 0.3, 0.3);
	lower_latch();
	
	chassis_l.moveTo(-50, -64, 90, 3000, false, true, 0.6, 0.1, 100);
	raise_latch();
	lower_blocker();
	chassis_l.moveTo(32, -63, 90, 3000, false, true, 0.6, 0.1);

	chassis_l.moveTo(35, -50, 0, 3000, false, true, 0.6, 0.1);
	chassis_l.moveTo(20, -43, -70, 3000, false, true, 0.6, 0.1);
	chassis_l.moveTo(12, -39, 0, 3000, false, true, 0.6, 0.1);

	chassis_l.moveTo(15, -30, 80, 3000, false, true, 0.6, 0.1);
	push(700);
	chassis_l.moveTo(12, -30, 90, 3000, false, false, 0.6, 0.1);
	chassis_l.turnTo(12, 90000, 3000, false, false);
	
	chassis_l.moveTo(12, 0, 0, 3000, false, true, 0.6, 0.1);
	chassis_l.turnTo(40, -20, 2000, false, false, 127);
	push(700);
	
	/**/
}