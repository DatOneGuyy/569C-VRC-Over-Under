#include "main.h"

using namespace okapi;

void curve(double distance, double mult, double slew_rate, double kp, double kd, int timeout) {
    left_drive_o.tarePosition();
    right_drive_o.tarePosition();
    left_drive_o.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    right_drive_o.setEncoderUnits(AbstractMotor::encoderUnits::degrees);

    double base_power = 0;
    double error = distance;
    double past_error = error;

    double left_power = 0;
    double right_power = 0;

    int slew_count = 0;
    int step = 11;
    int threshold_count = 0;
    int speed_count = 0;

    while (slew_count * step < timeout && threshold_count < 12 && speed_count < 10) {
        error = distance - right_drive_o.getPosition();
        base_power = kp * error;
        base_power = slew(slew_rate, slew_count, base_power, initial_speed);
        base_power = c(-100, 100, base_power + kd * (error - past_error));

        left_power = base_power / mult;
        right_power = base_power * mult;

        left_drive_o.moveVoltage(ptv(c(-100, 100, left_power)));
        right_drive_o.moveVoltage(ptv(c(-100, 100, right_power)));

        if (fabs(left_drive_o.getActualVelocity()) < 3 && fabs(right_drive_o.getActualVelocity()) < 3) {
            speed_count++;
        } else {
            speed_count = 0;
        }

        if (fabs(error) < 10) {
            threshold_count++;
        }

        slew_count++;
        past_error = error;
        pros::delay(step);
    }

    initial_speed = 45;

    left_drive_o.moveVelocity(0);
    right_drive_o.moveVelocity(0);
}

void chained_curve(double distance, double mult, double slew_rate, double final_pct, double kp, double kd, int timeout) {
    left_drive_o.tarePosition();
    right_drive_o.tarePosition();
    left_drive_o.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    right_drive_o.setEncoderUnits(AbstractMotor::encoderUnits::degrees);
    
    double base_power = 0;
    double error = distance;
    double past_error = error;

    double left_power = 0;
    double right_power = 0;

    int slew_count = 0;
    int step = 11;
    int threshold_count = 0;

    double scale = 0.01 * (100 - fabs(final_pct));

    while (slew_count * step < timeout && threshold_count < 12) {
        error = distance - right_drive_o.getPosition();
        base_power = kp * error;
        base_power = slew(slew_rate, slew_count, base_power, initial_speed);
        base_power = c(-100, 100, base_power + kd * (error - past_error));

        left_power = base_power / mult;
        right_power = base_power * mult;

        left_drive_o.moveVoltage(c(-12000, 12000, ptv(c(-100, 100, left_power * scale)) + ptv(final_pct) * sign(distance)));
        right_drive_o.moveVoltage(c(-12000, 12000, ptv(c(-100, 100, right_power * scale)) + ptv(final_pct) * sign(distance)));

        if (sign(error) != sign(past_error)) {
            break;
        }

        if (fabs(error) < 10) {
            threshold_count++;
        }

        slew_count++;
        past_error = error;

        pros::screen::print(TEXT_MEDIUM, 0, "Error: %f", error);
        pros::screen::print(TEXT_MEDIUM, 1, "Power: %f, %f", left_power, right_power);
        pros::screen::print(TEXT_MEDIUM, 2, "Base Power: %f", base_power);
        pros::screen::print(TEXT_MEDIUM, 3, "Final powers: %f, %f", c(-12000, 12000, ptv(c(-100, 100, left_power * scale)) + ptv(final_pct) * sign(distance)), c(-12000, 12000, ptv(c(-100, 100, right_power * scale)) + ptv(final_pct) * sign(distance)));
        pros::delay(step);
    }

    initial_speed = 45;

    left_drive_o.moveVoltage(ptv(final_pct));
    right_drive_o.moveVoltage(ptv(final_pct));
}