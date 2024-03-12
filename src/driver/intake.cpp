#include "intake.hpp"
#include "main.h"

void run_intake(void*) {
    bool triball = false;
    int counter = 0;

    if (program == 2) {
        intake.moveVoltage(-12000);
        pros::delay(800);
        intake.moveVoltage(12000);
        pros::delay(800);
        intake.moveVoltage(-12000);
    }

    while (driving) {
        if (!RIGHT.isPressed()) {
            if (R1.changedToPressed()) {
                if (triball) {
                    triball = false;
                    start_intake(-100);
                    pros::delay(900);
                    start_intake(100);
                    counter = 0;
                    pros::delay(300);
                } else if (intake_speed == 100) {
                    start_intake(0);
                    pros::delay(300);
                } else {
                    counter = 0;
                    start_intake(100);
                    pros::delay(300);
                }
            }

            if (intake_speed > 0 && intake.getActualVelocity() < 10 && !triball && counter > 70) {
                triball = true;
                counter = 0;
            }

            counter++;
        
            pros::delay(10);
        } else {
            start_intake(-100);
            pros::delay(10);
        }
    }
}

void start_intake(double pct) {
    intake_speed = pct;
    intake.moveVoltage(ptv(pct));
}

void stop_intake() {
    intake.moveVoltage(0);
}

void run_intake_deploy(void*) {
    intake.moveVoltage(-12000);
    pros::delay(800);
    intake.moveVoltage(12000);
    pros::delay(800);
    intake.moveVoltage(-12000);
    pros::delay(800);
    intake.moveVoltage(12000);
}

void run_intake_deploy_rapid(void*) {
    intake.moveVoltage(-12000);
    pros::delay(500);
    intake.moveVoltage(12000);
}

void intake_deploy() {
    intake.moveVoltage(-12000);
    pros::delay(500);
    intake.moveVoltage(12000);
}