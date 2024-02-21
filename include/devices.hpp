#include "okapi/api.hpp"
#include "lemlib/api.hpp"

#pragma once

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