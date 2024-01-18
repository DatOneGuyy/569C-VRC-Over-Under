#include "main.h"

using namespace okapi;

void drive(double distance, double slew_rate, double kp, double kd, double timeout) {
    left_drive_o.tarePosition();
    right_drive_o.tarePosition();
    
    double position = 0;
    double error = distance;
    double past_error = distance;
    double power = 0;

    double kg = 1.5;
    double angle_initial = inertial1.get_rotation();
    double angle_error = 0;
    
    int slew_count = 0;
    int step = 11;
    int threshold_count = 0;

    while (slew_count * step < timeout && threshold_count < 12) {
        position = left_drive_o.getPosition() / 2 + right_drive_o.getPosition() / 2;
        error = distance - position;
        angle_error = inertial1.get_rotation() - angle_initial;

        power = kp * error;
        power = slew(slew_rate, slew_count, power, 45);
        power = power + kd * (error - past_error);

        left_drive_o.moveVoltage(c(-12000, 12000, ptv(power - kg * angle_error)));
        right_drive_o.moveVoltage(c(-12000, 12000, ptv(power + kg * angle_error)));

        if (error < 2) {
            threshold_count++;
        } else {
            threshold_count = 0;
        }

        if (error == past_error) {
            threshold_count++;
        } else {
            threshold_count = 0;
        }

        past_error = error;
        slew_count++;

        pros::screen::print(TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(TEXT_MEDIUM, 2, "Angle error: %f", angle_error);
		pros::screen::print(TEXT_MEDIUM, 3, "Power: %f", power);
        pros::screen::print(TEXT_MEDIUM, 4, "Target: %f", distance);
        pros::screen::print(TEXT_MEDIUM, 5, "Angle: %f", inertial1.get_rotation());
        pros::screen::print(TEXT_MEDIUM, 6, "Initial: %f", angle_initial);
        pros::screen::print(TEXT_MEDIUM, 7, "Past error: %f", past_error);
        pros::screen::print(TEXT_MEDIUM, 8, "Slew count: %d", slew_count);

        pros::delay(step);
    }

    left_drive_o.moveVelocity(0);
    right_drive_o.moveVelocity(0);
}

void turn(double angle, double slew_rate, double kp, double kd, double timeout) {    
    double position = inertial1.get_rotation();
    double error = angle;
    double past_error = angle;
    double power = 0;
    
    int slew_count = 0;
    int step = 11;
    int threshold_count = 0;

    while (slew_count * step < timeout && threshold_count < 12) {
        position = inertial1.get_rotation();
        error = angle - position;

        power = kp * error;
        power = slew(slew_rate, slew_count, power, 45);
        power = power + kd * (error - past_error);

        left_drive_o.moveVoltage(c(-12000, 12000, ptv(power)));
        right_drive_o.moveVoltage(c(-12000, 12000, ptv(-power)));

        if (error < 2) {
            threshold_count++;
        } else {
            threshold_count = 0;
        }

        if (error == past_error) {
            threshold_count += 2;
        } else {
            threshold_count = 0;
        }

        past_error = error;
        slew_count++;

        pros::screen::print(TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(TEXT_MEDIUM, 2, "Power: %f", power);
        pros::screen::print(TEXT_MEDIUM, 3, "Target: %f", angle);
        pros::screen::print(TEXT_MEDIUM, 4, "Past error: %f", past_error);
        pros::screen::print(TEXT_MEDIUM, 5, "Slew count: %d", slew_count);

        pros::delay(step);
    }

    left_drive_o.moveVelocity(0);
    right_drive_o.moveVelocity(0);
}