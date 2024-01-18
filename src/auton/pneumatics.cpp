#include "main.h"

using namespace okapi;

void open_wings() {
    wings.set_value(true);
    pros::screen::print(TEXT_MEDIUM, 11, "Wings opened");
}

void close_wings() {
    wings.set_value(false);
}

void lower_latch() {
    latch.set_value(true);
}

void raise_latch() {
    latch.set_value(false);
}