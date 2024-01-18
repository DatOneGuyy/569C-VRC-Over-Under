#include "main.h"

using namespace okapi;

Controller controller(ControllerId::master);

ControllerButton R1(ControllerDigital::R1);
ControllerButton R2(ControllerDigital::R2);
ControllerButton L1(ControllerDigital::L1);
ControllerButton L2(ControllerDigital::L2);

ControllerButton DOWN(ControllerDigital::down);
ControllerButton UP(ControllerDigital::up);
ControllerButton LEFT(ControllerDigital::left);
ControllerButton RIGHT(ControllerDigital::right);

ControllerButton A(ControllerDigital::A);
ControllerButton B(ControllerDigital::B);
ControllerButton X(ControllerDigital::X);
ControllerButton Y(ControllerDigital::Y);