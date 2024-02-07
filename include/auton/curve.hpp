#pragma once

void curve(
    double distance, 
    double mult = 0.9,
    double slew_rate = 4,
    double kp = 0.3,
    double kd = 0.1, 
    int timeout = 4000
);

void chained_curve(
    double distance, 
    double mult = 0.9,
    double slew_rate = 4,
    double final_pct = 45,
    double kp = 0.3, 
    double kd = 0.1, 
    int timeout = 4000
);