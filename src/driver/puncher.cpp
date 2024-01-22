#include "main.h"

using namespace okapi;

void run_puncher(void*) {
    while (true) {
        if (L2.changedToReleased()) {
            toggle_puncher();
        }

        puncher.moveVoltage(shooting * 12000);
        puncher_skills.moveVoltage(shooting * 12000);

        pros::delay(20);
    }
}

void start_puncher() {
    shooting = true;
}

void stop_puncher() {
    shooting = false;
}

void toggle_puncher() {
    shooting = !shooting;
}