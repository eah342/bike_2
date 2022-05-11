#ifndef LINEARACTUATOR_H_
#define LINEARACTUATOR_H_
#include "GPIO.h"

using namespace exploringBB;

class LinearActuator {
private:
	int downPin, upPin, enablePin;

public:
	LinearActuator(int upPin, int downPin, int enablePin);

	void up();
	void down();
};

#endif
