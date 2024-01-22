#include "main.h"

using namespace okapi;

ASSET(swerve_txt);

void close_auton() {
    deploy_wings();
    turn(-120, 1);
    retract_wings();
    pros::delay(1000);
    turn(-270);
    turn(-180, 0);
    turn(-260);
    pros::delay(4000);
    push(20000, 0.6);
}

void far_auton() {
    lower_latch();
    deploy_wings();
    pros::delay(200);
    retract_wings();
    start_intake(100);
    drive(850);
    pros::delay(300);
    start_intake(0);
    turn(90);
    start_intake(-100);
    pros::delay(500);
    turn(25);
    start_intake(100);
    drive(370);
    turn(130);
    start_intake(-100);
    deploy_wings();
    drive(600);
    retract_wings();
    drive(-200);
    turn(220);
    drive(650);
    deploy_wings();
    turn(60, 1);
    stop_intake();
    retract_wings();
    push(500);
}

void skills() {
    lower_latch();
    turn(-45, 1);
    drive(350);
    turn(0, 0);
    push(300);
    turn(-30, 0);
    turn(70);
    push(400, -0.4);

    puncher.moveVoltage(12000);
    puncher_skills.moveVoltage(12000);
    pros::delay(32000);
    puncher.moveVoltage(0);
    puncher_skills.moveVoltage(0);

    drive(700);
    turn(90);
    deploy_wings();
    deploy_wings();
    push(3500);
    
    retract_wings();
    push(1000, -0.6);
    turn(10);
    deploy_wings();

    drive(200);
    turn(120, 0);
    start_intake(-100);
    push(1000);
    retract_wings();

    stop_intake();
    push(1000, -0.6);
    turn(35, 1);
    deploy_wings();
    drive(800);
    turn(135, 0);
    retract_wings();
    
    turn(180, 0);
    push(1000);

    drive(-200);
    push(1000);
    drive(-200);
}

void test() {
    drive(600, 3, 1, 1.5);
}