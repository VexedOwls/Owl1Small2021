#include "main.h"
#include "motors.h"

using namespace pros;





/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol()
{
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	//drive motors, REVERSE ALL FRONT MOTORS

	//arm
	pros::Motor armMove(9);
	pros::Motor armMove2(2);
	pros::Motor backArmMove(1);
	pros::Motor backArmMove2(10);

	armMove.set_brake_mode(MOTOR_BRAKE_HOLD);
	armMove2.set_brake_mode(MOTOR_BRAKE_HOLD);
	backArmMove.set_brake_mode(MOTOR_BRAKE_HOLD);
	backArmMove2.set_brake_mode(MOTOR_BRAKE_HOLD);

	bool state = 0;
	bool doClaw = false;
	bool latchA = false;
	pros::ADIDigitalOut actuator(1, state);


	while (true)
	{
		//get controller inputs and store them to variables
		int leftInput = master.get_analog(ANALOG_LEFT_Y) * -1; //yes, its inefficient to invert twice like this
		int rightInput = master.get_analog(ANALOG_RIGHT_Y) * -1;	   //do i care? no and neither will the compiler

		//driving controls
		backLeft->move(leftInput);
		frontLeft->move(leftInput);
		midLeft->move(leftInput);
		frontRight->move(rightInput);
		midRight->move(rightInput);
		backRight->move(rightInput);


		if (master.get_digital(DIGITAL_Y) && !competition::is_connected())
		{  autonomous();  }


		//claw control
		if (master.get_digital(DIGITAL_A)) {
			if(!latchA){ //flip the toggle one time and set the latch
			doClaw = !doClaw;
			latchA = true;
			}
			} else {
			//Once the BumperA is released then then release the latch too
			latchA = false;
		}

		if (doClaw)
		{
			state = 1;
			actuator.set_value(state);
		}
		else if (!doClaw)
		{
			state = 0;
			actuator.set_value(state);
		}

		//arm movement controls
		if (master.get_digital(DIGITAL_R1)) //if user is holding down L1,
		{
			armMove.move(-127); //move front arm motor forward
			armMove2.move(127);
		}
		else if (master.get_digital(DIGITAL_R2)) //if user is holding L2 and isnt holding L1,
		{
			armMove.move(127); //move front arm motor backward
			armMove2.move(-127);
		}
		else //otherwise,
		{
			armMove.move(0); //quit moving the arm
			armMove2.move(0);
		}

		if (master.get_digital(DIGITAL_L1)) //if user is holding down R1,
		{
			backArmMove.move(-127); //move back arm motor forward
			backArmMove2.move(127);
		}
		else if (master.get_digital(DIGITAL_L2)) //if user is holding R2 and isnt holding R1,
		{
			backArmMove.move(127); //move back arm motor backward
			backArmMove2.move(-127);
		}
		else //otherwise,
		{
			backArmMove.move(0); //quit moving the arm
			backArmMove2.move(0);
		}

		//button controls
		if(master.get_digital(DIGITAL_B))
		{
			autonomous();
		}

		pros::delay(2);
	}
}
