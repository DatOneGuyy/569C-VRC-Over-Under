#include "main.h"

using namespace okapi;

void puncher_task(void*) {
    ControllerButton L2(ControllerDigital::L2);

    bool puncher_active = false;

    puncher.tarePosition();
    puncher.setEncoderUnits(AbstractMotor::encoderUnits::degrees);

    while (true) {
        if (L2.changedToReleased()) {
            puncher_active = !puncher_active;
        }

        if (puncher_active) {
            puncher.moveVoltage(ptv(85));
        } else {
            puncher.moveVoltage(ptv(0));
        }

        pros::screen::print(TEXT_MEDIUM, 8, "puncher: %f", fmod(puncher.getPosition(), 750));
        
        pros::delay(10);
    }
}