#include "main.h"

using namespace okapi;

void elevation_task(void*) {
    pros::ADIPort elevation('G', ADI_DIGITAL_OUT);
    ControllerButton R2(ControllerDigital::R2);

    elevation.set_value(false);

    while (true) {
        if (R2.changedToReleased()) {
            elevation.set_value(!elevation.get_value());
        }

        pros::delay(10);
    }
}

void wings_task(void*) {
    ControllerButton L1(ControllerDigital::L1);

    wings.set_value(false);

    while (true) {
        if (L1.changedToReleased()) {
            wings.set_value(!wings.get_value());
        }
        pros::delay(10);
    }
}

void latch_task(void*) {
    ControllerButton UP(ControllerDigital::up);
    if (program == 2) {
        latch.set_value(true);
    }

    while (true) {
        if (UP.changedToPressed()) {
            latch.set_value(!latch.get_value());
        }

        pros::delay(10);
    }
}