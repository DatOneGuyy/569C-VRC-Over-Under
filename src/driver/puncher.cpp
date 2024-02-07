#include "devices.hpp"
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
    puncher.moveVoltage(12000);
    puncher_skills.moveVoltage(12000);
}

void stop_puncher() {
    puncher.moveVoltage(0);
    puncher_skills.moveVoltage(0);
}

void toggle_puncher() {
    shooting = !shooting;
}