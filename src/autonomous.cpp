#include "main.h"

pros::Motor backLeft(11);		 //PORT 11 GOES TO BACK LEFT MOTOR
pros::Motor frontLeft(12, true); //PORT 12 GOES TO FRONT LEFT MOTOR
pros::Motor frontmostLeft(13);
pros::Motor frontmostRight(18);
pros::Motor frontRight(19, true); //PORT 19 GOES TO FRONT RIGHT MOTOR
pros::Motor backRight(20);		  //PORT 20 GOES TO BACK RIGHT MOTOR

//arm
pros::Motor armMove(9);
pros::Motor armMove2(2);
pros::Motor backArmMove(1);
pros::Motor backArmMove2(10);

void autonomous()
{
}

void translate(int units, int voltage)
{
	//reset motor encoders
	//resetDriveEncoders();
	//drive forwards
	while (frontLeft.get_position() < units)
	{
		//setDrive(voltage, voltage);
		pros::delay(10);
	}
	//brief brake
	//setDrive(-10,-10);
	pros::delay(50);
	//set the drive back to neutral

}

void resetDriveEncoders()
{
	backLeft.tare_position();
	frontLeft.tare_position();
	frontmostLeft.tare_position();
	backRight.tare_position();
	frontRight.tare_position();
	frontmostRight.tare_position();
}
