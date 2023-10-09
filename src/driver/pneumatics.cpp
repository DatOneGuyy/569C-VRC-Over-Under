#include "main.h"

using namespace okapi;

void elevation_task(void*) {
    pros::ADIPort front_elevation('G', ADI_DIGITAL_OUT);
    pros::ADIPort back_elevation('H', ADI_DIGITAL_OUT);
    ControllerButton R2(ControllerDigital::R2);

    front_elevation.set_value(false);
    back_elevation.set_value(false);

    while (true) {
        if (R2.changedToReleased()) {
            front_elevation.set_value(!front_elevation.get_value());
            back_elevation.set_value(!back_elevation.get_value());
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