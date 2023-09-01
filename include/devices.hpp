#include "okapi/api.hpp"
#include "lemlib/api.hpp"

#pragma once

extern lemlib::Chassis chassis_l;
extern pros::IMU inertial1;

extern pros::MotorGroup left_drive;
extern pros::MotorGroup right_drive;
extern okapi::MotorGroup left_drive_o;
extern okapi::MotorGroup right_drive_o;