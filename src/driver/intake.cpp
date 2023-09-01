#include "main.h"
#include "okapi/api.hpp"
#include "driver/intake.hpp"

using namespace okapi;

void intake_task(void*) {
    Motor intake(5);
    ControllerButton R1(ControllerDigital::R1);
    ControllerButton R2(ControllerDigital::R2);

    bool intake_active = false;
    bool triball = false;

    while (true) {
        if (R1.changedToPressed()) {
            if (triball) {
                intake_active = true;
                triball = false;
                intake.moveVoltage(-12000);
                pros::delay(300);
                intake.moveVoltage(12000);
            } else {
                if (intake_active) {
                    intake_active = false;
                    intake.moveVoltage(0);
                } else {
                    intake_active = true;
                    intake.moveVoltage(12000);
                    pros::delay(300);
                }
            }
        }
        intake.moveVoltage(12000 * intake_active);

        if (intake_active && intake.getActualVelocity() == 0) {
            intake_active = false;
            triball = true;
        }

        pros::delay(10);
    }
}