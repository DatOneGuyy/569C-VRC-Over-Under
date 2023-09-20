#include "main.h"

using namespace okapi;

void start_puncher() {
    puncher.moveVoltage(ptv(85));
}

void stop_puncher() {
    puncher.moveVoltage(0);
}