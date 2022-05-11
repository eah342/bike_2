#ifndef __SERVO_H_
#define __SERVO_H_
#include <math.h>
#include "pubSysCls.h"

using namespace sFnd;
using namespace std;

class Servo
{
private:
	SysManager *manager;
	INode *node;
	int convertDegreesToCounts(float degrees);
	float convertCountsToDegrees(int count);
public:
	Servo();
	int init();
	int turn(float angle);
	float getAngle();
};

#endif
