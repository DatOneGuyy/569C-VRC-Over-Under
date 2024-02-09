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
    deploy_wings();
    lower_latch();
    pros::Task auto_retract_task(auto_retract);
    start_intake();
    curve(2600, 0.67);
    
    drive(-500);
    turn(-170);
    curve(2000, 0.65);
    deploy_wings();
    turn(-330);
    retract_wings();
    pros::delay(500);

    turn(-265);

    start_intake(-100);
    drive(1900);
    deploy_wings();
    turn(-250);
}

void far_auton() {
    deploy_wings();
    lower_latch();
    pros::Task auto_retract_task(auto_retract);
    start_intake();
    curve(3700, 1.5);

    turn(90);
    deploy_wings();
    start_intake(-100);
    push(800);

    retract_wings();
    drive(-300);
    turn(235);
    start_intake();

    drive(1300);
    turn(135);
    drive(2500);

    deploy_wings();
    turn(30);
    start_intake(-100);
    retract_wings();
    push(700);

    drive(-400);
    turn(-80);
    start_intake(100);
    curve(2900, 1.15);
    deploy_wings();
    turn(-60);

}

void skills() {
    lower_latch();
    push(700);
    raise_latch();
    pros::delay(200);

    curve(-1100, 2.0);
    turn(72);
    push(500, -0.4);

    start_puncher();
    pros::delay(30000);
    stop_puncher();

    curve(2200, 1.1);
    turn(80, 2, 4);\
    start_intake(-100);
    push(3000);
    drive(-1000);
    deploy_wings();
    push(700);

    initial_speed = -45;
    chained_curve(-1500, 1.9, 4);
    chained_turn(170, 1);
    drive(-2200);

    turn(160);
    deploy_wings();
    chained_drive(1100);
    turn(110, 1);
    push(1000);
    retract_wings();
    drive(-1000);
    deploy_wings();
    push(700);
    retract_wings();

    pros::delay(500);
    drive(-1400);
    turn(33);
    deploy_wings();
    chained_drive(2600);
    retract_wings();
    turn(150);
    push(1000);
   
    curve(-1000, 2.0);
    turn(315);
    chained_drive(1100);
    turn(265, 1);

    toggle_elevation();
    push(1400, 0.8);
    toggle_elevation();
}

void test() {
    initial_speed = 45;
    drive(600, 3, 1, 1.5);
}