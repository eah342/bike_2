#ifndef DIGITALSENSOR_H_
#define DIGITALSENSOR_H_
#include "GPIO.h"

using namespace exploringBB;

class DigitalSensor {
private:
	int pinNumber;

public:
	DigitalSensor(int pinNumber);

	int read();
};

#endif
