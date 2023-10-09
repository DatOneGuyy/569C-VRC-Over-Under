#include "main.h"

using namespace okapi;

void set_intake(double percent) {
    intake_speed = percent;
    intake.moveVoltage(ptv(percent));
}