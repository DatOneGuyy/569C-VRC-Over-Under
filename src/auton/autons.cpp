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

	push(400);

	//turn around
	drive_for(-150, 0.4, 0.4);
	turn_to_angle(-60, 0);
	
	pros::delay(200);

	//remove match load ball
	
	open_wings();
	drive_for(700);
	turn_to_angle(-20, 0, 2, 4);
	

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
	turn_to_angle(-20);
	
	lower_latch();
	pros::delay(400);
	drive_for(1600, 0.8, 0.3);
	raise_latch();
	
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
	/*
	start_odom(0, 0, -135);
	
	drive_for(350, 0.8, 0.3);
	pros::delay(200);
	turn_to_angle(-100, 2, 1.5);

	drive_for(300, 3);

	drive_for(-200);
	pros::delay(200);
	lower_latch();
	set_intake(100);
	turn_to_angle(-20, 0, 1, 2);
	pros::delay(400);
	drive_for(900);
	
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
	close_wings();/**/
}

void skills(void) {	
	start_odom(-36, -60, 0);
	chassis_l.follow(preloads_txt, 3000, 7, false, true, 100);
	
	start_odom(0, 0, 90);
	turn_to_angle(135, 2, 1.5);
	
	//intake ball and drive forward
	drive_for(750, 0.4, 0.3);
	pros::delay(200);
	turn_to_angle(95, 1);

	push(600);

	//turn around
	drive_for(-100, 0.4, 0.4);

	turn_to_angle(120, 1, 2, 2);
	turn_to_angle(30, 2);
	turn_to_angle(23, 0, 4, 3);

	start_puncher();
	pros::delay(35000);
	stop_puncher();

	turn_to_angle(-45, 1);
	drive_for(500);
	turn_to_angle(0, 2);
	lower_latch();
	drive_for(2500, 0.4);
	
	raise_latch();
	turn_to_angle(90, 2);
	drive_for(400);
	turn_to_angle(180, 2);
	drive_for(300);
	turn_to_angle(90, 1, 1.5);
	
	open_wings();
	drive_for(400);
	turn_to_angle(0, 1, 1.5);
	push(700, 700);

	close_wings();
	drive_for(-1200);
	pros::delay(200);
	turn_to_angle(80);
	pros::delay(200);
	drive_for(1400, 0.2);
	turn_to_angle(-60, 0, 0.5);
	
	open_wings();
	drive_for(1000, 0.2);
	turn_to_angle(0);
	push(500, 700, 500, 1500);
	start_odom(0, 0, 0);
	
	turn_to_angle(45, 2);
	drive_for(1600, 0.2);
	open_wings();
	turn_to_angle(-160, 1);
	close_wings();
	push(800, 500, 200, 400);
	/*
	start_odom(0, 0, 0);
	chassis_l.moveTo(-13, 9, 0, 3000, false, true, 0.6, 0.1, 127);
	push(400);
	
	chassis_l.moveTo(-4, 7, -40, 3000, false, false, 1, 0.1, 200);
	
	chassis_l.turnTo(75, 40, 1000, false, false, 200);
	drive_for(-150, 0.4, 0.1);
	
	start_puncher();
	pros::delay(2000);
	stop_puncher();
	
	lower_latch();
	chassis_l.moveTo(0, 0, 90, 3000, false, true, 0.3, 0.6, 200);
	
	
	chassis_l.moveTo(22, 0, 85, 5000, false,true, 0.6, 0.1, 200);
	raise_latch();
	//open_wings();
	chassis_l.moveTo(25, 8, 0, 4000, false, true, 0.3, 0.1, 150);
	chassis_l.moveTo(18, 9, -80, 4000, false, true, 0.3, 0.1, 150);
	
	open_wings();
	pros::delay(200);
	chassis_l.moveTo(10, 13, 10, 3000, false, true, 1, 0.1, 150);
	
	pros::delay(200);
	chassis_l.turnTo(2000000, 13, 1500, false, false, 100);
	
	push(800, 800, 300, 800);
	pros::delay(200);
	
	chassis_l.turnTo(10, 700000000, 800, false, false, 30);
	pros::delay(200);
	
	open_wings();
	drive_for(500);
	turn_to_angle(-140, 1);
	drive_for(300);
	turn_to_angle(-90, 2);
	push(800, 800, 400, 800);
	turn_to_angle(-35, 2);
	
	drive_for(800);
	open_wings();
	turn_to_angle(-160, 1);
	close_wings();
	push(800, 500, 200, 400);
	
	/**/
}