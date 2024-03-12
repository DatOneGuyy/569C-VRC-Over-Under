#pragma once

void chained_drive(
    double distance, 
    double slew_rate = 3, 
    double final_pct = 45,
    double kp = 0.3, 
    double kd = 1, 
    double timeout = 3000
);
void chained_turn(
    double angle, 
    int swing = 2, 
    double final_pct = 45,
    double slew_rate = 3, 
    double kp = 6, 
    double kd = 24, 
    double timeout = 2000
);