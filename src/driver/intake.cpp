#include "main.h"
#include "okapi/api.hpp"
#include "driver/intake.hpp"

using namespace okapi;

void intake_task(void*) {
    Motor intake(-15);
    ControllerButton R1(ControllerDigital::R1);
    ControllerButton R2(ControllerDigital::R2);

    while (true) {
        intake.moveVoltage(12000 * (R1.isPressed() - R2.isPressed()));
        pros::delay(10);
    }
}