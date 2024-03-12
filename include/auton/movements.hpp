#pragma once

/**
 * @brief Drive forward/backwards with PID/gyro
 * 
 * @param distance Motor target in degrees
 * @param slew_rate Increase in percent voltage/11ms
 * @param kp Proportional constant between 0.1 to 1
 * @param kd Derivative constant between 0.2 and 2
 * @param timeout Time before exit in ms
 */
void drive(
    double distance, 
    double slew_rate = 4, 
    double kp = 0.3, 
    double kd = 1, 
    double timeout = 3000
);

/**
 * @brief Point/swing turn with PID
 * 
 * @param angle Target angle to turn to
 * @param swing Turning mode: 0 = left swing, 1 = right swing, 2 = point turn
 * @param slew_rate Increase in percent voltage/11ms
 * @param kp Proportional constant between 2 and 15
 * @param kd Derivative constant between 10 and 35
 * @param timeout Time before exit in ms
 */
void turn(
    double angle, 
    int swing = 2, 
    double slew_rate = 4, 
    double kp = 6, 
    double kd = 24, 
    double timeout = 2000
);

/**
 * @brief Pushes forward/backward with voltage
 * 
 * @param time Time to push
 * @param mult Multiplier for voltage - multiplied by 12000mV
 */
void push(int time, double mult = 1);

/**
 * @brief Reverses until target angle is reached
 * 
 * @param angle Target angle in degrees
 * @param power Power to move at in percent
 * @param timeout Milliseconds before exit
 */
void push_to_angle(double angle, double power = -40, int timeout = 2000);