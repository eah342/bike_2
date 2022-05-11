#ifndef ANALOGSENSOR_H_
#define ANALOGSENSOR_H_
#include "GPIO.h"

using namespace exploringBB;

class AnalogSensor {
private:
	int pinNumber;

public:
	AnalogSensor(int pinNumber);

	int read();
};

#endif
