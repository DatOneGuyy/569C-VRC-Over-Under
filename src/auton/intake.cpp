#include "main.h"

using namespace okapi;

void intake_auton_task(void*) {
    Motor intake(5);

    while (true) {
        intake.moveVoltage(ptv(intake_speed));
        pros::delay(20);
    }
}