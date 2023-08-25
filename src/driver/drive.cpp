#include "main.h"
#include "okapi/api.hpp"
#include "driver/drive.hpp"

using namespace okapi;

void drive_task(void*) {
	Controller controller;
	double left, right;

	std::shared_ptr<ChassisController> drive =
		ChassisControllerBuilder()
			.withMotors({4, 20, 18}, {-3, -13, -16})
			.withDimensions({AbstractMotor::gearset::blue, 1}, {{2.75_in, 15.25_in}, imev5BlueTPR})
			.build();
	drive->getModel()->setBrakeMode(AbstractMotor::brakeMode::coast);

	while (true) {
		left = controller.getAnalog(ControllerAnalog::leftY);
		right = controller.getAnalog(ControllerAnalog::rightY);

		drive->getModel()->tank(controller_map(left), controller_map(right));
	
		pros::delay(10); 
	}
}