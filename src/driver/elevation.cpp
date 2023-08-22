#include "main.h"
#include "okapi/api.hpp"
#include "driver/elevation.hpp"

using namespace okapi;

void elevation_task(void *) {
    pros::ADIPort front_elevation({1, 'A'}, pros::E_ADI_DIGITAL_OUT);
    
    while (true) {
        
        pros::delay(10);
    }
}