#include "main.h"

using namespace okapi;

void elevation_task(void*) {
    pros::ADIPort elevation('G', ADI_DIGITAL_OUT);
    ControllerButton R2(ControllerDigital::R2);

    elevation.set_value(false);

    while (true) {
        if (R2.changedToReleased()) {
            if (!elevation.get_value()) {
                raise_blocker();
                lower_latch();
                pros::delay(300);
            }
            elevation.set_value(!elevation.get_value());
            pros::delay(200);
            if (!elevation.get_value()) {
                pros::delay(300);
                lower_blocker();
            }
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

void blocker_task(void*) {
    ControllerButton X(ControllerDigital::X);

    while (true) {
        pros::screen::print(TEXT_MEDIUM, 6, "blocker state: %d", blocker.get_value());
        if (X.changedToReleased()) {
            blocker.set_value(!blocker.get_value());
        }

        pros::delay(10);
    }
}