#include "main.h"
#include "autoSelect/selection.h"
#include "robotBase.h"

using namespace pros;


#define middleRed 1
#define middleBlue -1
#define fakerRed 2
#define fakerBlue -2
#define naRed 3
#define naBlue -3
#define skills 0


void autonomous()
{
	Imu imu(16);
	
	Motor backRight(20, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor midRight(19, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor frontRight(18, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor backLeft(11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
	Motor midLeft(12, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor frontLeft(13, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

	RobotBase base(&backRight, &midRight, &frontRight, &backLeft, &midLeft, &frontLeft);

	Motor armMove(9);
	Motor armMove2(2);
	Motor backArmMove(1);
	Motor backArmMove2(10);
	armMove.set_brake_mode(MOTOR_BRAKE_HOLD);
	armMove2.set_brake_mode(MOTOR_BRAKE_HOLD);
	backArmMove.set_brake_mode(MOTOR_BRAKE_HOLD);
	backArmMove2.set_brake_mode(MOTOR_BRAKE_HOLD);

	ADIDigitalOut actuator(1, 1);

	// Double check that the imu is calibrated
	while (imu.get_status() & c::E_IMU_STATUS_CALIBRATING)
	{  delay(10);  }





	if (selector::auton == skills)
	{
		
	}





	if (selector::auton == middleRed || selector::auton == middleBlue)
	{
		base.moveGyro(-57 _INCHES, &imu, true);

		actuator.set_value(0);

		base.moveGyro(41 _INCHES, &imu, true);

		actuator.set_value(1);
		armMove.move(127);
		armMove2.move(-127);
		delay(200);
		armMove.move(0);
		armMove2.move(0);

		base.moveGyro(18 _INCHES, &imu);
		base.turnGyro(31, &imu, true);
		base.moveGyro(-45 _INCHES, &imu);

		actuator.set_value(0);

		base.moveGyro(35 _INCHES, &imu);	// !!!!!! 35

		actuator.set_value(1);
		armMove.move(127);
		armMove2.move(-127);
		delay(200);
		armMove.move(0);
		armMove2.move(0);

		base.moveGyro(16 _INCHES, &imu);
		base.turnGyro(-134, &imu, true);

		backArmMove.move(127);
		backArmMove2.move(-127);
		delay(1200);
		backArmMove.move(0);
		backArmMove2.move(0);

		base.moveGyro(22 _INCHES, &imu);

		backArmMove.move(-127);
		backArmMove2.move(127);
		delay(600);
		backArmMove.move(0);
		backArmMove2.move(0);

		base.moveGyro(-27 _INCHES, &imu);
	}
}
