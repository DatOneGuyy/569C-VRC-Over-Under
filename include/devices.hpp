#include "okapi/api.hpp"
#include "lemlib/api.hpp"

#pragma once

extern pros::Motor left1;
extern pros::Motor left2;
extern pros::Motor left3;
extern pros::Motor right1;
extern pros::Motor right2;
extern pros::Motor righ3;

extern okapi::Motor intake;
extern okapi::Motor puncher;

extern pros::MotorGroup left_drive;
extern pros::MotorGroup right_drive;

extern okapi::MotorGroup left_drive_o;
extern okapi::MotorGroup right_drive_o;

extern pros::IMU inertial1;

extern pros::ADIPort wings;
extern pros::ADIPort latch;

extern pros::ADIEncoder left_tracker;
extern pros::ADIEncoder back_tracker;

extern lemlib::Drivetrain_t drivetrain;

extern lemlib::TrackingWheel left_tracking_wheel;
extern lemlib::TrackingWheel back_tracking_wheel;

extern lemlib::OdomSensors_t sensors;

extern lemlib::ChassisController_t lateralController;
extern lemlib::ChassisController_t angularController;

extern lemlib::Chassis chassis_l;