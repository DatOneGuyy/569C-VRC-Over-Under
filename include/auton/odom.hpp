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
    int timeout = 3000
);
void turn_to_angle(
    double angle,
    int swing = 0,
    double kp = 0.9,
    double slew_rate = 1.4,
    double threshold = 1,
    int timeout = 3000
);
double get_angle();
void drive_to_point(
    double x,
    double y,
    double slew_rate = 0.9, 
    double threshold = 1,
    int timeout = 3000
);
void push(double time, double time2 = 0, double reverse = 400, double reverse2 = 0);
void drive_for(
    double distance,
    double slew_rate = 0.8,
    double kp = 0.7,
    double threshold = 1,
    int timeout = 3000
);
void report_angle(void*);