#include "main.h"

using namespace okapi;

void run_drive(void*) {
    left_drive_o.setBrakeMode(AbstractMotor::brakeMode::brake);
    right_drive_o.setBrakeMode(AbstractMotor::brakeMode::brake);
    
    while (driving) {
        left_drive_o.moveVoltage(ptv(100 * (controller.getAnalog(ControllerAnalog::leftY))));
        right_drive_o.moveVoltage(ptv(100 * (controller.getAnalog(ControllerAnalog::rightY))));
    }
}