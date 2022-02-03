#ifndef robotBase
#define robotBase

#include "main.h"
using namespace pros;

#define wheelDiameter 3.25
#define PI 3.1416
#define ratio 0.6

#define wheelCircumference (PI*wheelDiameter
#define _INCHES *21.1554

class RobotBase
{
private:
  void resetPos();
  int minRightMeasure();
  int minLeftMeasure();
  int rightMaxError(int target);
  int leftMaxError(int target);

public:
  Motor* right1;
  Motor* right2;
  Motor* right3;
  Motor* left1;
  Motor* left2;
  Motor* left3;

  RobotBase(Motor* _r1, Motor* _r2, Motor* _r3, Motor* _l1, Motor* _l2, Motor* _l3);

  void move(int rightPower, int leftPower);

  void movePID(int target, int maxDist = 2);
  void moveGyro(int target, Imu* imu, bool console = false, int precision = 5);
  void turnGyro(double target, Imu* imu, bool console = false, double precision = 0.1);
};

#endif
