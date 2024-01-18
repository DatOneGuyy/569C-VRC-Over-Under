#include "okapi/api.hpp"
#include "lemlib/api.hpp"

#pragma once

extern pros::Motor left1;
extern pros::Motor left2;
extern pros::Motor left3;
extern pros::Motor right1;
extern pros::Motor right2;
extern pros::Motor righ3;

extern pros::MotorGroup left_drive;
extern pros::MotorGroup right_drive;

extern okapi::MotorGroup left_drive_o;
extern okapi::MotorGroup right_drive_o;

extern okapi::Motor puncher_skills;
extern okapi::Motor puncher;

extern okapi::Motor intake;

extern pros::IMU inertial1;
extern okapi::IMU inertial1_o;

extern pros::ADIPort wings;
extern pros::ADIPort elevation;
extern pros::ADIEncoder tracker;
extern okapi::Potentiometer auton_selector;
extern pros::ADIPort latch;

extern lemlib::Drivetrain drivetrain;

extern lemlib::TrackingWheel tracking_wheel;

extern lemlib::OdomSensors sensors;

extern lemlib::ControllerSettings lateralController;
extern lemlib::ControllerSettings angularController;

extern lemlib::Chassis chassis_l;