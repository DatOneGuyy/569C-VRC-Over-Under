#include "main.h"

using namespace okapi;

void puncher_task(void*) {
    Motor puncher(9);
    ControllerButton L2(ControllerDigital::L2);

    bool puncher_active = false;
    bool puncher_active_prev = false;

    puncher.tarePosition();

    while (true) {
        if (L2.changedToReleased()) {
            puncher_active = !puncher_active;
        }

        if (puncher_active) {
            puncher.moveVoltage(ptv(85));
        } else if (puncher_active_prev) {
            while (fmod(puncher.getPosition(), 360) < 120 || fmod(puncher.getPosition(), 360) > 150) {
                puncher.moveVoltage(ptv(100));
                pros::delay(10);
            }
            puncher.moveVoltage(0);
        }

        puncher_active_prev = puncher_active;
        
        pros::delay(10);
    }
}