#include "main.h"

using namespace okapi;

double intake_speed = 0;

void intake_task(void*) {
    Motor intake(5);
    ControllerButton R1(ControllerDigital::R1);
    ControllerButton R2(ControllerDigital::R2);

    bool triball = false;

    while (true) {
        if (!R2.isPressed()) {
            if (R1.changedToPressed()) {
                if (triball) {
                    triball = false;
                    intake_speed = -12000;
                    pros::delay(300);
                    intake_speed = 8000;
                    pros::delay(300);
                    intake_speed = 12000;
                } else if (intake_speed == 12000) {
                    intake_speed = 0;
                } else {
                    intake_speed = 12000;
                }
            } 

            if (intake_speed > 0 && intake.getActualVelocity() < 10) {
                triball = true;
                intake_speed = 1000;
            }
        } else {
            intake_speed = -12000;
        }

        pros::delay(10);
    }
}