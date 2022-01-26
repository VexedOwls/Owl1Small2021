#include "main.h"

pros::Motor backLeft(11);	//PORT 11 GOES TO BACK LEFT MOTOR
pros::Motor frontLeft(12);	//PORT 12 GOES TO FRONT LEFT MOTOR
pros::Motor frontRight(19); //PORT 19 GOES TO FRONT RIGHT MOTOR
pros::Motor backRight(20);	//PORT 20 GOES TO BACK RIGHT MOTOR

void autonomous()
{

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
