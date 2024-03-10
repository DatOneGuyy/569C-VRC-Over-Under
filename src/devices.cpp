#include "main.h" // IWYU pragma: keep

using namespace okapi;

MotorGroup left_drive_o({-4, -18, -19});
MotorGroup right_drive_o({3, 11, 12});

Motor puncher(10);
Motor puncher_skills(-14);

Motor intake(-16);

pros::IMU inertial1(7);
IMU inertial1_o(7);

pros::ADIPort wings('E', ADI_DIGITAL_OUT);
pros::ADIPort elevation('D', ADI_DIGITAL_OUT);
Potentiometer auton_selector('C');
pros::ADIPort descorer('F', ADI_DIGITAL_OUT);