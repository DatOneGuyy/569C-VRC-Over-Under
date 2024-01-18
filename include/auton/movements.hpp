#pragma once

void drive(double distance, double slew_rate = 3, double kp = 1, double kd = 1.5, double timeout = 5000);
void turn(double angle, double slew_rate = 3, double kp = 6, double kd = 24, double timeout = 3000);