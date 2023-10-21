#include "main.h"

using namespace okapi;

void intake_task(void*) {
    ControllerButton R1(ControllerDigital::R1);
    ControllerButton R2(ControllerDigital::R2);
    ControllerButton RIGHT(ControllerDigital::right);

    bool triball = false;
    int counter = 0;
    int presses = 0;

    while (true) {
        if (R1.changedToPressed()) {
            presses++;
            if (triball) {
                triball = false;
                set_intake(-100);
                pros::delay(300);
                set_intake(0);
                pros::delay(300);
                set_intake(100);
                pros::delay(300);
            } else if (intake_speed == 100) {
                set_intake(0);
                pros::delay(300);
            } else {
                set_intake(100);
                pros::delay(300);
            }
        }

        if (intake_speed > 0 && intake.getActualVelocity() < 10 && !triball && counter > 50) {
            triball = true;
            counter = 0;
            set_intake(0);
        }

        if (RIGHT.changedToPressed()) {
            set_intake(-100);
        }

        counter++;

        pros::screen::print(TEXT_MEDIUM, 7, "intake speed: %f", intake_speed);
        pros::screen::print(TEXT_MEDIUM, 6, "presses: %d", presses);
    
        pros::delay(10);
    }
}