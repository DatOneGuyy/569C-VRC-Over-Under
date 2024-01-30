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
    deploy_wings();
    turn(21);
    retract_wings();
    start_intake(100);
    drive(3200, 3, 1, 1.5, 5000);
    turn(135);
    deploy_wings();
    start_intake(-100);
    push(600);
    retract_wings();
    stop_intake();
    drive(-300);
    turn(275);
    start_intake(100);
    drive(1400);
    turn(180);
    start_intake(-50);
    drive(1800);
    deploy_wings();
    turn(45, 1);
}

void skills() {
    chained_turn(45, 0);
    chained_drive(500);
    chained_turn(0, 1);
    chained_turn(-180);
    chained_drive(500);
    turn(-270, 1);
}

void test() {
    drive(600, 3, 1, 1.5);
}