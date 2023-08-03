#pragma once

void update_positions_encoders(void*);
void start_odom(void);
void drive_to(
    double target_x, 
    double target_y, 
    double target_speed = 0,  
    bool backwards = false,
    double threshold = 0.02,
    double kp_angle = 2.0,
    double angle_threshold = 70);
void turn_to(
    double target_angle,
    double slew_rate = 0.6,
    double threshold = 2,
    double timeout = 3000,
    int threshold_time = 200
);