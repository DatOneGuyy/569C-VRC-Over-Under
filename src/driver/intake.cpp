#include "main.h"

void run_intake(void*) {
    bool triball = false;
    int counter = 0;

    while (driving) {
        if (!RIGHT.isPressed()) {
            if (R1.changedToPressed()) {
                if (triball) {
                    triball = false;
                    start_intake(-100);
                    pros::delay(300);
                    start_intake(0);
                    pros::delay(300);
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

            if (intake_speed > 0 && intake.getActualVelocity() < 10 && !triball && counter > 100) {
                triball = true;
                counter = 0;
                start_intake(50);
            }

            counter++;
        
            pros::delay(10);
        } else {
            start_intake(-100);
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