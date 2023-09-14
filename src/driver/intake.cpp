#include "main.h"

using namespace okapi;

void intake_task(void*) {
    ControllerButton R1(ControllerDigital::R1);
    ControllerButton R2(ControllerDigital::R2);

    bool triball = false;
    double speed = 0;
    int counter = 0;

    while (true) {
        if (R1.changedToPressed()) {
            if (triball) {
                triball = false;
                speed = -100;
                pros::delay(300);
                speed = 0;
                pros::delay(500);
                speed = 100;
            } else if (intake_speed == 100) {
                speed = 0;
                pros::delay(300);
            } else {
                speed = 100;
                pros::delay(300);
            }
        }

        if (intake_speed > 0 && intake.getActualVelocity() < 10 && !triball && counter > 200) {
            triball = true;
            counter = 0;
            speed = 10;
        }

        if (R2.isPressed()) {
            intake_speed = -100;
        } else {
            intake_speed = speed;
        }

        counter++;
    
        pros::delay(10);
    }
}