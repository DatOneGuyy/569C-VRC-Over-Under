#include "main.h"
#include "okapi/api.hpp"
#include "auton/intake.hpp"

using namespace okapi;

void intake_auton(void*) {
    Motor intake(5);

    while (true) {
        intake.moveVoltage(ptv(intake_speed));
        pros::delay(20);
    }
}