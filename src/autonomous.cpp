#include "main.h"
#include "okapi/api/chassis/controller/chassisControllerIntegrated.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
using namespace okapi;
using okapi::ChassisControllerIntegrated;

pros::Motor backLeft(11);	//PORT 11 GOES TO BACK LEFT MOTOR
pros::Motor frontLeft(12);	//PORT 12 GOES TO FRONT LEFT MOTOR
pros::Motor frontRight(19); //PORT 19 GOES TO FRONT RIGHT MOTOR
pros::Motor backRight(20);	//PORT 20 GOES TO BACK RIGHT MOTOR

void autonomous() //-12 -19
{
	std::shared_ptr<ChassisController> chassis =
		ChassisControllerBuilder()
			.withMotors(
				{12,13,-11},
				{-19,18,20}
			)
			.withMaxVelocity(100.0)
			.withDimensions({AbstractMotor::gearset::green, (3.0/5.0)}, {{3.25_in, 10_in}, imev5GreenTPR})
			.build();
	chassis->moveDistance(1_m);
	chassis->turnAngle(90_deg);
	chassis->moveDistance(1_m);
}

// void translate(int units, int voltage)
// {
// 	int direction = abs(units) / units;
// 	//TODO:resetDriveEncoders();
// 	//TODO:gyro.reset();

// 	while (avgDriveEncoderValue() < abs(units))
// 	{
// 		/* code */
// 	}
// 	//brief brake
// 	driveMotor(-10 * direction, -10 * direction);
// 	pros::delay(50);
// 	//set drive back to neutral
// 	driveMotor(0, 0);
// }

// void driveMotor(int left, int right)
// {
// 	backLeft.move(left);
// 	frontLeft.move(left * -1);
// 	backRight.move(right * -1);
// 	backRight.move(right);
// }

// double avgDriveEncoderValue()
// {
// 	return 0;
// }