#include "main.h"
#include "okapi/api.hpp"
#include "driver/pneumatics.hpp"
#include "pros/adi.h"

using namespace okapi;

void elevation_task(void*) {
    pros::ADIPort front_elevation('G', pros::E_ADI_DIGITAL_OUT);
    pros::ADIPort back_elevation('H', pros::E_ADI_DIGITAL_OUT);
    ControllerButton LEFT(ControllerDigital::left);

    front_elevation.set_value(false);
    back_elevation.set_value(false);

    while (true) {
        if (LEFT.changedToReleased()) {
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

    latch.set_value(false);

    while (true) {
        if (UP.changedToPressed()) {
            latch.set_value(!latch.get_value());
        }

        pros::delay(10);
    }
}