#include "main.h" // IWYU pragma: keep

using namespace okapi;

pros::Motor left1(4, MOTOR_GEARSET_06, false);
pros::Motor left2(18, MOTOR_GEARSET_06, false);
pros::Motor left3(19, MOTOR_GEARSET_06, false);
pros::Motor right1(3, MOTOR_GEARSET_06, true);
pros::Motor right2(11, MOTOR_GEARSET_06, true);
pros::Motor right3(12, MOTOR_GEARSET_06, true);

pros::MotorGroup left_drive({left1, left2, left3});
pros::MotorGroup right_drive({right1, right2, right3});

MotorGroup left_drive_o({-4, -20, -19});
MotorGroup right_drive_o({-3, -11, -12});

Motor puncher(10);
Motor puncher_skills(-14);

Motor intake(-16);

pros::IMU inertial1(7);
IMU inertial1_o(7);

pros::ADIPort wings('E', ADI_DIGITAL_OUT);
pros::ADIPort elevation('D', ADI_DIGITAL_OUT);
Potentiometer auton_selector('C');
pros::ADIPort latch('F', ADI_DIGITAL_OUT);

lemlib::Drivetrain drivetrain(
	&left_drive,
	&right_drive,
	15.25,
	lemlib::Omniwheel::NEW_275,
	450,
    8
);

lemlib::OdomSensors sensors(
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	&inertial1
);

lemlib::ControllerSettings linearController(32, 0, 1, 3, 1, 100, 3, 500, 20);
lemlib::ControllerSettings angularController(2, 0, 16, 3, 1, 100, 3, 500, 20);

lemlib::Chassis chassis_l(drivetrain, linearController, angularController, sensors);