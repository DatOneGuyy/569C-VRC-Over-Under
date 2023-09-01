#include "main.h"
#include "okapi/api.hpp"
#include "auton/pneumatics.hpp"
#include "pros/adi.hpp"

using namespace okapi;

void open_wings() {
    pros::ADIPort wings('A', pros::E_ADI_DIGITAL_OUT);
    wings.set_value(true);
}

void close_wings() {
    pros::ADIPort wings('A', pros::E_ADI_DIGITAL_OUT);
    wings.set_value(false);
}

void lower_latch() {
    pros::ADIPort latch('B', pros::E_ADI_DIGITAL_OUT);
    latch.set_value(true);
}

void raise_latch() {
    pros::ADIPort latch('B', pros::E_ADI_DIGITAL_OUT);
    latch.set_value(false);
}