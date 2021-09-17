#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button()
{
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

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
	pros::Motor backLeft(11); 		//PORT 11 GOES TO BACK LEFT MOTOR
	pros::Motor frontLeft(12); 		//PORT 12 GOES TO FRONT LEFT MOTOR
	pros::Motor frontRight(19);		//PORT 19 GOES TO FRONT RIGHT MOTOR
	pros::Motor backRight(20);		//PORT 20 GOES TO BACK RIGHT MOTOR

	pros::Motor armMove(1);			//TODO: placeholder port, change to real one

	while (true)
	{
		//get controller inputs and store them to variables
		int leftInput = master.get_analog(ANALOG_LEFT_Y) * -1; 	//yes, its inefficient to invert twice like this
		int rightInput = master.get_analog(ANALOG_RIGHT_Y); 	//do i care? no and neither will the compiler

		//driving controls
		backLeft.move(leftInput);
		frontLeft.move(leftInput * -1);		//the movement of the front motors is inverted to make all wheels go
		frontRight.move(rightInput * -1); 	//the same direction instead of just rotating inwards
		backRight.move(rightInput);

		//arm movement controls
		if(master.get_digital(DIGITAL_L1))
		{
			armMove.move(10);
		}
		else if(master.get_digital(DIGITAL_R1))
		{
			armMove.move(-10);
		}

		pros::delay(5);
	}
}
