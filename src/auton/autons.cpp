#include "chained.hpp"
#include "driver/intake.hpp"
#include "driver/pneumatics.hpp"
#include "driver/puncher.hpp"
#include "main.h"
#include "auton/curve.hpp"
#include "pros/rtos.hpp"

using namespace okapi;

void auto_retract(void*) {
    pros::delay(300);
    retract_wings();
}

void close_auton() {
    pros::Task intake_deploy_task(run_intake_deploy);
    inertial1.set_rotation(45);
    pros::delay(500);
    drive(-500);
    deploy_wings();
    turn(-40);
    retract_wings();
    pros::delay(1000);
    turn(45);
    drive(600);
    turn(0, 1);
    start_intake(-100);
    drive(1600);
    deploy_wings();
    turn(25);
}

void disruption_wp() {
    pros::Task intake_deploy_task(run_intake_deploy_rapid);
    deploy_wings();
    drive(2400);
    retract_wings();
    drive(-1500);
    turn(-143);
    drive(1450);
    deploy_wings();
    turn(-300);
    pros::delay(500);
    retract_wings();
    turn(-225);
    drive(400);
    turn(-270, 1);
    start_intake(-100);
    drive(1300);
    deploy_wings();
    turn(-245);
}

void delay_deploy(void*) {
    pros::delay(500);
    deploy_wings();
}

void disruption() {
    lower_descorer();
    start_intake(100);
    chained_curve(1800, 0.7);
    drive(-200);
    stop_intake();

    pros::Task delay_deploy_task2(delay_deploy);
    turn(90, 0);
    start_intake(-100);
    push(600);
    retract_wings();
    drive(-300);
    pros::delay(500);
    
    turn(30, 0);
    drive(-2900);
    turn(100);

    start_intake(-100);
    drive(1800);
}

void far_auton() {
    intake_deploy();
    pros::delay(300);
    drive(300, 6, 0.6);

    drive(-1500);
    turn(-35, 0);
    lower_descorer();
    drive(-1000, 6);
    turn(-90, 2, 6);
    raise_descorer();
    turn(110, 2, 6);
    start_intake(-100);
    push(500);

    drive(-700, 6, 0.6);
    turn(28, 2, 6);
    start_intake(100);
    drive(2400, 6, 0.6);
    drive(-500, 6, 0.6);
    
    turn(140, 2, 6);
    start_intake(-100);
    pros::delay(300);

    turn(60, 2, 6);
    start_intake(100);
    drive(1300, 6, 0.6);
    turn(180, 2, 6);

    deploy_wings();
    start_intake(-100);
    push(800);
    drive(-200);
}

void skills() {
    push(700);

    curve(-1000, 0.3);
    turn(75);
    push_to_angle(70, -30, 3500);
    
    pros::Task intake_deploy_task(run_intake_deploy);
    start_puncher();
    right_drive_o.moveVoltage(-700);
    //push(500, -0.1);
    pros::delay(24000); //28
    stop_puncher();

    turn(115);
    drive(1500);
    turn(90);
    start_intake();
    chained_drive(4500, 4, 45, 0.4);
    
    turn(70, 1);
    drive(2000);
    turn(15);

    start_intake(-100);
    push(1000);
    push(400, -0.7);
    push(700);
    drive(-900);
    start_intake();

    turn(-70);
    pros::Task delay_deploy_task(delay_deploy);
    chained_drive(3000);
    turn(50, 2, 6);
    start_intake(-100);
    push(1100);
    retract_wings();
    pros::delay(300);

    drive(-1700);
    turn(-25 + 360);
    start_intake();
    drive(2400);
    pros::Task delay_deploy_task2(delay_deploy);
    turn(120 + 360, 2, 6);
    start_intake(-100);
    push(1200, 0.8);
    retract_wings();

    drive(-1800);
    start_intake();
    turn(28 + 360);
    drive(3400);
    turn(140 + 360, 2, 6, 8);
    start_intake(-100);
    push(1200);
    push(300, -0.7);
    push(1000);

    curve(-1100, 0.8);
    stop_intake();
    turn(315 + 360);
    drive(1200);
    turn(265 + 360);
    raise_elevation();
    push(1300);
    lower_elevation(); 
}

void safe_far_wp() {
    pros::Task intake_deploy_task(run_intake_deploy);
    push(800);
    drive(-300);
}

void test() {
    initial_speed = 45;
    drive(600, 3, 1, 1.5);
}