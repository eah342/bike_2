#ifndef __SERVO_H_
#define __SERVO_H_
#include "pubSysCls.h"

using namespace sFnd;
using namespace std;

class Servo
{
private:
	SysManager *manager;
	INode *node;
public:
	Servo();
	~Servo();
	int init();
	int home();
};

#endif
