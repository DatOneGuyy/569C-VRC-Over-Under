#include "main.h"

using namespace okapi;

void intake_auton_task(void*) {
    while (true) {
        intake.moveVoltage(ptv(intake_speed));
        pros::delay(10);
    }
}