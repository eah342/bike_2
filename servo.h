#ifndef __SERVO_H_
#define __SERVO_H_
#include "pubSysCls.h"

using namespace sFnd;
using namespace std;

class Servo
{
private:
	SysManager *manager;
public:
	Servo();
	int init();
};

#endif
