#include "main.h"

using namespace okapi;

ASSET(swerve_txt);

void close_auton() {

}

void far_auton() {

}

void skills() {
    chassis_l.follow(swerve_txt, 5, 5000, true, false);
}

void test() {
    drive(600, 3, 1, 1.5);
}