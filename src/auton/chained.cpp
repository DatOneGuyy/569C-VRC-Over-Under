#include "main.h"

using namespace okapi;

void chained_drive(double distance, double slew_rate, double final_pct, double kp, double kd, double timeout) {
    left_drive_o.tarePosition();
    right_drive_o.tarePosition();
    left_drive_o.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    right_drive_o.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    
    double position = 0;
    double error = distance;
    double past_error = distance;
    double power = 0;

    double kg = 4;
    double angle_initial = inertial1.get_rotation();
    double angle_error = 0;
    
    int slew_count = 0;
    int step = 11;
    int threshold_count = 0;

    double scale = 0.01 * (100 - fabs(final_pct));

    while (slew_count * step < timeout && threshold_count < 12) {
        position = left_drive_o.getPosition() / 2 + right_drive_o.getPosition() / 2;
        error = distance - position;
        angle_error = inertial1.get_rotation() - angle_initial;

        power = kp * error;
        power = slew(slew_rate, slew_count, power, initial_speed);
        power = c(-100, 100, power + kd * (error - past_error));

        left_drive_o.moveVoltage(c(-12000, 12000, scale * ptv(power - kg * angle_error * error / distance) + ptv(final_pct)));
        right_drive_o.moveVoltage(c(-12000, 12000, scale * ptv(power + kg * angle_error * error / distance) + ptv(final_pct)));

        if (sign(error) != sign(past_error)) {
            break;
        }

        if (power < 9) {
            threshold_count += 3;
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

    left_drive_o.moveVoltage(ptv(final_pct));
    right_drive_o.moveVoltage(ptv(final_pct));
    initial_speed = final_pct;
}

void chained_turn(double angle, int swing, double final_pct, double slew_rate, double kp, double kd, double timeout) {    
    double position = inertial1.get_rotation();
    double error = angle;
    double past_error = angle;
    double power = 0;
    
    int slew_count = 0;
    int step = 11;
    int threshold_count = 0;

    double scale = 0.01 * (100 - fabs(final_pct));

    while (fabs(error) > 1) {
        position = inertial1.get_rotation();
        error = angle - position;

        power = kp * error;
        power = slew(slew_rate, slew_count, power, initial_speed);
        power = power + kd * (error - past_error);

        if (swing == 0) {
            left_drive_o.moveVoltage(c(-12000, 12000, scale * ptv(power) + ptv(final_pct)));
            right_drive_o.moveVoltage(0);
        } else if (swing == 1) {
            right_drive_o.moveVoltage(c(-12000, 12000, scale * ptv(-power) - ptv(final_pct * sign(error))));
            left_drive_o.moveVoltage(0);
        } else {
            left_drive_o.moveVoltage(c(-12000, 12000, ptv(power)));
            right_drive_o.moveVoltage(c(-12000, 12000, ptv(-power)));
        }

        if (sign(error) != sign(past_error)) {
            break;
        }

        if (power < 5) {
            threshold_count += 3;
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
        pros::screen::print(TEXT_MEDIUM, 6, "Threshold count: %f", threshold_count);
        pros::screen::print(TEXT_MEDIUM, 7, "output: %f", c(-12000, 12000, scale * ptv(-power) - ptv(final_pct)));

        pros::delay(step);
    }
    
    if (swing == 2 || swing == 0) {
        left_drive_o.moveVoltage(ptv(final_pct));
    }
    
    if (swing == 2 || swing == 1) {
        right_drive_o.moveVoltage(ptv(final_pct));
    }
    initial_speed = final_pct;
}