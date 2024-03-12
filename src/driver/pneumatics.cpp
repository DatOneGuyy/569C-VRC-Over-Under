#include "main.h"

void run_descorer(void*) {
    while (driving) {
        if (UP.changedToReleased()) {
            toggle_descorer();
        }

        pros::delay(20);
    }
}
void toggle_descorer() {
    descorer.set_value(!descorer.get_value());
}
void lower_descorer() {
    descorer.set_value(true);
}
void raise_descorer() {
    descorer.set_value(false);
}

void run_wings(void*) {
    retract_wings();

    while (driving) {
        if (L1.changedToReleased()) {
            toggle_wings();
        }

        pros::delay(20);
    }
}
void toggle_wings() {
    wings.set_value(!wings.get_value());
}
void deploy_wings() {
    wings.set_value(true); 
}
void retract_wings() {
    wings.set_value(false);
}

void run_elevation(void*) {
    while (driving){
        if (R2.changedToReleased()) {
            toggle_elevation();
        }

        pros::delay(20);
    }
}
void toggle_elevation(){
    elevation.set_value(!elevation.get_value());
}
void raise_elevation() {
    elevation.set_value(true);
}
void lower_elevation() {
    elevation.set_value(false);
}