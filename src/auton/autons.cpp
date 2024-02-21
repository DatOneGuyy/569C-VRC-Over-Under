#include "chained.hpp"
#include "driver/intake.hpp"
#include "driver/pneumatics.hpp"
#include "driver/puncher.hpp"
#include "main.h"
#include "auton/curve.hpp"
#include "pros/rtos.hpp"

void auto_retract(void*) {
    pros::delay(300);
    retract_wings();
}

void close_auton() {
    inertial1.set_rotation(45);
    lower_latch();
    start_intake(100);
    pros::delay(500);
    drive(-500);
    deploy_wings();
    turn(-40);
    retract_wings();
    pros::delay(1000);
    turn(45);
    drive(400);
    turn(0, 1);
    start_intake(-100);
    drive(1600);
    deploy_wings();
    turn(25);
}

void delay_deploy(void*) {
    pros::delay(300);
    deploy_wings();
}

void disruption() {
    lower_latch();
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
    deploy_wings();
    lower_latch();
    pros::delay(400);
    pros::Task auto_retract_task(auto_retract);
    start_intake();
    curve(3800, 1.55);

    turn(90);
    deploy_wings();
    start_intake(-100);
    push(800);

    retract_wings();
    drive(-300);
    turn(240);
    start_intake();

    drive(1500);
    turn(130);
    drive(2600);

    deploy_wings();
    turn(30);
    retract_wings();
    start_intake(-100);
    pros::delay(400);
    push(700);

    drive(-400);
    turn(-80);
    start_intake(100);
    curve(2700, 1.2);
    deploy_wings();
    turn(-60);
    /*
    lower_latch();
    push(1000);
    drive(-500);*/
}

void skills() {
    lower_latch();
    push(700);
    raise_latch();

    curve(-1200, 0.7);
    turn(80);
    push_to_angle(73, -60);
    
    start_puncher();
    pros::delay(26000); //28
    stop_puncher();

    turn(115);
    drive(1300);
    turn(95);
    start_intake();
    chained_drive(3800);
    
    deploy_wings();
    turn(50, 1);
    drive(1100);
    turn(30);
    retract_wings();

    start_intake(-100);
    push(1000);
    push(400, -0.7);
    push(700);
    drive(-900);
    start_intake();

    turn(-60);
    pros::Task delay_deploy_task(delay_deploy);
    chained_drive(1900);
    turn(55);
    start_intake(-100);
    push(1100);
    retract_wings();
    pros::delay(300);

    drive(-1600);
    turn(-20);
    start_intake();
    drive(2300);
    turn(120);
    deploy_wings();
    start_intake(-100);
    pros::delay(400);
    push(1200);
    retract_wings();

    drive(-1900);
    start_intake();
    turn(36);
    chained_drive(3400);
    deploy_wings();
    turn(150);
    start_intake(-100);
    retract_wings();
    push(1500);
    push(400, -0.7);
    push(1000);

    curve(-1100, 0.8);
    stop_intake();
    turn(315);
    drive(1000);
    turn(265);
    raise_elevation();
    push(1300);
    lower_elevation(); 
}

void test() {
    initial_speed = 45;
    drive(600, 3, 1, 1.5);
}