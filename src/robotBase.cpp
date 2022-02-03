#include "robotBase.h"

RobotBase::RobotBase(Motor* _r1, Motor* _r2, Motor* _r3, Motor* _l1, Motor* _l2, Motor* _l3)
{
  right1 = _r1;
  right2 = _r2;
  right3 = _r3;
  left1 = _l1;
  left2 = _l2;
  left3 = _l3;
};

void RobotBase::move(int rightPower, int leftPower)
{
  right1->move(rightPower);
  right2->move(rightPower);
  right3->move(rightPower);

  left1->move(leftPower);
  left2->move(leftPower);
  left3->move(leftPower);
};

void RobotBase::resetPos()
{
  right1->tare_position();
  right2->tare_position();
  right3->tare_position();
  left1->tare_position();
  left2->tare_position();
  left3->tare_position();
};



int max(int a, int b, int c)
{  return std::max(std::max(a, b), c);  }

int min(int a, int b, int c)
{  return std::min(std::min(a, b), c);  }

int RobotBase::minRightMeasure()
{
  if(max(right1->get_position(), right2->get_position(), right3->get_position()) < 0)
  { return min(right1->get_position(), right2->get_position(), right3->get_position()); }
  return max(right1->get_position(), right2->get_position(), right3->get_position());
};

int RobotBase::minLeftMeasure()
{
  if(max(left1->get_position(), left2->get_position(), left3->get_position()) < 0)
  { return min(left1->get_position(), left2->get_position(), left3->get_position()); }
  return max(left1->get_position(), left2->get_position(), left3->get_position());
};

int RobotBase::rightMaxError(int target)
{
  if ((target/std::abs(target)) == -1)
  {  return min(target - right1->get_position(), target - right2->get_position(), target - right3->get_position());  }
  return max(target - right1->get_position(), target - right2->get_position(), target - right3->get_position());

};

int RobotBase::leftMaxError(int target)
{
  if ((target/std::abs(target)) == -1)
  {  return min(target - left1->get_position(), target - left2->get_position(), target - left3->get_position());  }
  return max(target - left1->get_position(), target - left2->get_position(), target - left3->get_position());
};



int mean(int val1, int val2)
{
  return ((val1 + val2)/2);
}

int clamp(int val, int max, int min)
{
  return (   std::max( std::min(val, max), min)   );
}









void RobotBase::movePID(int distance, int maxDist)
{
  double kP = 0.6; // 0.5
  double kI = 0.05; // 0.1
  double kD = 0.25; // 0.5
  int integral = 0;
  int previous_error = distance;
  int error = distance;
  int averageSpeed = 0;

  resetPos();

  while(   abs(error)>maxDist   )  //  ||   abs(averageSpeed)>stopSpeed
  {
    error = distance - mean( minRightMeasure(), minLeftMeasure() );
    integral = integral + error;

    if (abs(error) < 2) { integral = 0; }
    if (abs(error) > 20) { integral = 0; }

    int derivative = error - previous_error;
    previous_error = error;

    int rightSpeed = clamp(kP*error, 127, -127) + kI*integral + kD*derivative;
    int leftSpeed  = clamp(kP*error, 127, -127) + kI*integral + kD*derivative;

    move(rightSpeed, leftSpeed);
    std::cout <<    error<<" | "<<clamp(error*kP, 127, -127)<<" "<<integral*kI<<" "<<derivative*kD<<" | "<<rightSpeed<<" "<<leftSpeed    << std::endl;

    delay(10);
  }

  move(0, 0);
};









void RobotBase::moveGyro(int distance, Imu* imu, bool console, int precision)
{
  double kP = 0.4;    // 0.3
  double kPi = 0.05;   // 0.1
  double kD = 0.15;
  double kG = 4;      // 4
  double kGi = 0.3;   // 0.3

  imu->set_heading(180);
  resetPos();

  int error = distance;
  int previousError = distance;
  int errorIntegral = 0;
  int derivative = error - previousError;
  double angleError = 0;
  double angleErrorIntegral = 0;

  while ( abs(error) > precision )
  {
    error = mean( rightMaxError(distance), leftMaxError(distance) );
    errorIntegral = errorIntegral + error;
    angleError = 180 - imu->get_heading(); // ++R == -aE
    angleErrorIntegral = angleErrorIntegral + angleError;

    if (abs(error) < 2) { errorIntegral = 0; }
    if (abs(error) > 40) { errorIntegral = 0; }
    if (std::abs(angleError) < 0.05) { angleErrorIntegral = 0; }
    if (std::abs(angleError) > 5) { angleErrorIntegral = 0; }

    derivative = error - previousError;
    previousError = error;

    int rightSpeed = clamp(kP*error, 127, -127) + kPi*errorIntegral + kG*angleError + kGi*angleErrorIntegral + kD*derivative;
    int leftSpeed  = clamp(kP*error, 127, -127) + kPi*errorIntegral - kG*angleError - kGi*angleErrorIntegral + kD*derivative;

    move(rightSpeed, leftSpeed);

    if (console) {
      // std::cout<< rightMaxError(distance)<<" "<<right1->get_position()<<" "<<right2->get_position()<<" "<<right3->get_position() <<std::endl;
      std::cout<< error<<" "<<angleError<<" | "<<clamp(kP*error, 127, -127)<<" "<<kPi*errorIntegral<<" "<<kG*angleError<<" "<<kGi*angleErrorIntegral<<" "<<kD*derivative<<" | "<<rightSpeed<<" "<<leftSpeed <<std::endl;
      // std::cout<< right1->get_position()<<" "<<right2->get_position()<<" "<<right3->get_position()<<" "<<left1->get_position()<<" "<<left2->get_position()<<" "<<left3->get_position() <<std::endl;
    }

    delay(10);
  }
  move(0, 0);
  if (console) { std::cout << "PIGI Complete...\n\n\n\n" << std::endl; }
};




void RobotBase::turnGyro(double target, Imu* imu, bool console, double precision)
{ // 28.25
  double kP = 2;      // 3
  double kPi = 0.17;   // 0.1
  double kD = 0.2;

  imu->set_heading(180);
  target = target+180;
  double error = target-180;
  double errorIntegral = 0;
  double previousError = error;
  double derivative = error - previousError;

  while( std::abs(error) > precision )
  {
    error = target - imu->get_heading();
    errorIntegral = errorIntegral + error;

    if (std::abs(error) < 0.02) { errorIntegral = 0; }
    if (std::abs(error) > 10) { errorIntegral = 0; }

    derivative = error - previousError;
    previousError = error;

    int rightSpeed =  (clamp(kP*error, 50, -50) + kPi*errorIntegral + kD*derivative);
    int leftSpeed  = -(clamp(kP*error, 50, -50) + kPi*errorIntegral + kD*derivative);
    move(rightSpeed, leftSpeed);

    if (console) { std::cout<<error<<" | "<<clamp(kP*error, 50, -50)<<" "<<kPi*errorIntegral<<" "<<kD*derivative<<" | "<<rightSpeed<<std::endl; }

    delay(10);
  }
  move(0, 0);
  if (console) { std::cout<<"Rotation done...\n\n\n\n"<<std::endl; }
};
