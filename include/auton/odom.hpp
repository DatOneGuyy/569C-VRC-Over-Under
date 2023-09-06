#pragma once

void update_positions_encoders(void*);
void start_odom(
    double initial_x = 0,
    double initial_y = 0,
    double initial_angle = 135 * 3.141592653589 / 180
);
void drive_to(
    double target_x, 
    double target_y, 
    double target_speed = 0,  
    bool backwards = false,
    double threshold = 0.02,
    double kp_angle = 0.8,
    double angle_threshold = 70);
void turn_to(
    double x, 
    double y,
    double slew_rate = 0.8,
    double threshold = 0.03,
    double timeout = 3000
);
void turn_to_angle(
    double angle,
    double slew_rate = 0.8,
    double threshold = 1,
    double timeout = 3000
);
void drive_for(
    double distance,
    double slew_rate = 0.8,
    double threshold = 1,
    int timeout = 3000
);