#ifndef __HUB_H_
#define __HUB_H_
#include <math.h>
#include "pubSysCls.h"

using namespace sFnd;
using namespace std;

class Hub
{
private:
	int period;
	int getPwmValueFromSpeed(float speed);

public:
	Hub(int period);
	~Hub();

	int init();
	int changeSpeed(float speed);
};

#endif
