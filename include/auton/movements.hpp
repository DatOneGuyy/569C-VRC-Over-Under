#pragma once

void drive(
    double distance, 
    double slew_rate = 3, 
    double kp = 1, 
    double kd = 1.5, 
    double timeout = 3000
);
void turn(
    double angle, 
    int swing = 2, 
    double slew_rate = 3, 
    double kp = 6, 
    double kd = 24, 
    double timeout = 2000
);
void push(int time, double mult = 1);