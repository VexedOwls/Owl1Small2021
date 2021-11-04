#include "main.h"
#include "okapi/api/chassis/controller/chassisControllerIntegrated.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
using namespace okapi;
using okapi::ChassisControllerIntegrated;

void autonomous()
{
	std::shared_ptr<ChassisController> chassis =
		ChassisControllerBuilder()
			.withMotors(-11, 12, -19, 20)
			// Green gearset, 4 in wheel diam, 11.5 in wheel track
			.withDimensions(AbstractMotor::gearset::green, {{3.25_in, 10_in}, imev5GreenTPR})
			.build();
	chassis->moveDistance(1_m);
}