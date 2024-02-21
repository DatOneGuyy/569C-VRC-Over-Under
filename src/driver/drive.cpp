#include "main.h"

using namespace okapi;

void run_drive(void*) {
    left_drive_o.setBrakeMode(AbstractMotor::brakeMode::brake);
    right_drive_o.setBrakeMode(AbstractMotor::brakeMode::brake);
    left_drive_o.setGearing(AbstractMotor::gearset::blue);
    right_drive_o.setGearing(AbstractMotor::gearset::blue);
    left_drive_o.moveVoltage(0);
    right_drive_o.moveVoltage(0);

    double peak_left = 0, peak_right = 0;
    double current_left, current_right;

    int update_counter = 0;

    while (driving) {
        left_drive_o.moveVoltage(ptv(100 * (controller.getAnalog(ControllerAnalog::leftY))));
        right_drive_o.moveVoltage(ptv(100 * (controller.getAnalog(ControllerAnalog::rightY))));

        current_left = left_drive_o.getActualVelocity();
        current_right = right_drive_o.getActualVelocity();

        if (fabs(current_left) > fabs(peak_left)) {
            peak_left = current_left;
        }

        if (fabs(current_right) > fabs(peak_right)) {
            peak_right = current_right;
        }

        if (update_counter % 20 == 0) {
            //controller.setText(1, 0, std::to_string(static_cast<int>(round(current_left))) + " " + std::to_string(static_cast<int>(round(current_right))) + "          ");
            controller.setText(0, 0, std::to_string(static_cast<int>(round(peak_left))) + " " + std::to_string(static_cast<int>(round(peak_right))) + "          ");
        }

        update_counter++;

        pros::delay(10);    
    }
}