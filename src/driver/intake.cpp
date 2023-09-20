#include "main.h"

using namespace okapi;

void intake_task(void*) {
    ControllerButton R1(ControllerDigital::R1);
    ControllerButton R2(ControllerDigital::R2);

    bool triball = false;
    int counter = 0;

    while (true) {
        if (R1.changedToPressed()) {
            if (triball) {
                triball = false;
                intake_speed = -100;
                pros::delay(300);
                intake_speed = 0;
                pros::delay(500);
                intake_speed = 100;
            } else if (intake_speed == 100) {
                intake_speed = 0;
                pros::delay(300);
            } else {
                intake_speed = 100;
                pros::delay(300);
            }
        }

        if (intake_speed > 0 && intake.getActualVelocity() < 5 && !triball && counter > 250) {
            triball = true;
            counter = 0;
            intake_speed = 0;
        }

        counter++;
    
        pros::delay(10);
    }
}