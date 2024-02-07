#include "main.h"

using namespace okapi;

void drive(double distance, double slew_rate, double kp, double kd, double timeout) {
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
    int speed_count = 0;

    bool flag = false;

    while (slew_count * step < timeout && threshold_count < 12 && speed_count < 10) {
        position = left_drive_o.getPosition() / 2 + right_drive_o.getPosition() / 2;
        error = distance - position;
        angle_error = inertial1.get_rotation() - angle_initial;

        power = kp * error;
        power = slew(slew_rate, slew_count, power, initial_speed);
        power = c(-100, 100, power + kd * (error - past_error));

        //left_drive_o.moveVoltage(c(-12000, 12000, ptv(100 * profile(sign(distance) * (1 - error / distance), sign(distance)) - kg * angle_error)));
        //right_drive_o.moveVoltage(c(-12000, 12000, ptv(100 * profile(sign(distance) * (1 - error / distance), sign(distance)) + kg * angle_error)));

        left_drive_o.moveVoltage(c(-12000, 12000, ptv(power - kg * angle_error * error / distance)));
        right_drive_o.moveVoltage(c(-12000, 12000, ptv(power + kg * angle_error * error / distance)));

        if (fabs(error) < 10) {
            threshold_count++;
        } else {
            threshold_count = 0;
        }

        if (fabs(left_drive_o.getActualVelocity()) < 3 && fabs(right_drive_o.getActualVelocity()) < 3) {
            speed_count++;
        } else {
            speed_count = 0;
        }

        past_error = error;
        slew_count++;

        pros::screen::print(TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(TEXT_MEDIUM, 2, "Angle error: %f", angle_error);
		pros::screen::print(TEXT_MEDIUM, 3, "Power: %f", power);
        pros::screen::print(TEXT_MEDIUM, 4, "Target: %f", distance);
        pros::screen::print(TEXT_MEDIUM, 5, "Angle: %f", inertial1.get_rotation());
        pros::screen::print(TEXT_MEDIUM, 6, "Velocities: %f, %f", left_drive_o.getActualVelocity(), right_drive_o.getActualVelocity());
        pros::screen::print(TEXT_MEDIUM, 7, "Past error: %f", past_error);
        pros::screen::print(TEXT_MEDIUM, 8, "Slew count: %d", slew_count);
        pros::screen::print(TEXT_MEDIUM, 9, "Threshold count: %d", threshold_count);

        if (error < 0 && !flag) {
            flag = true;
            controller.setText(0, 0, "Angle error: " + std::to_string(angle_error));
        }

        pros::delay(step);
    }

    pros::screen::print(TEXT_MEDIUM, 10, "Loop exited for distance %f", distance);

    left_drive_o.moveVelocity(0);
    right_drive_o.moveVelocity(0);
    initial_speed = 45;
}

void turn(double angle, int swing, double slew_rate, double kp, double kd, double timeout) {    
    double position = inertial1.get_rotation();
    double error = angle;
    double past_error = angle;
    double power = 0;
    
    int slew_count = 0;
    int step = 11;
    int threshold_count = 0;
    int speed_count = 0;

    while (slew_count * step < timeout && threshold_count < 12 && speed_count < 10) {
        position = inertial1.get_rotation();
        error = angle - position;

        power = kp * error;
        power = slew(slew_rate, slew_count, power, initial_speed);
        power = power + kd * (error - past_error);

        if (swing == 0) {
            left_drive_o.moveVoltage(c(-12000, 12000, ptv(power)));
            right_drive_o.moveVoltage(0);
        } else if (swing == 1) {
            right_drive_o.moveVoltage(c(-12000, 12000, ptv(-power)));
            left_drive_o.moveVoltage(0);
        } else {
            left_drive_o.moveVoltage(c(-12000, 12000, ptv(power)));
            right_drive_o.moveVoltage(c(-12000, 12000, ptv(-power)));
        }

        if (fabs(error) < 10) {
            threshold_count++;
        } else {
            threshold_count = 0;
        }

        if (fabs(left_drive_o.getActualVelocity()) < 3 && fabs(right_drive_o.getActualVelocity()) < 3) {
            speed_count++;
        } else {
            speed_count = 0;
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

        pros::delay(step);
    }

    left_drive_o.moveVelocity(0);
    right_drive_o.moveVelocity(0);
    initial_speed = 45;
}

void push(int time, double mult) {
    left_drive_o.moveVoltage(12000 * mult);
    right_drive_o.moveVoltage(12000 * mult);

    pros::delay(time);

    left_drive_o.moveVelocity(0);
    right_drive_o.moveVelocity(0);
}