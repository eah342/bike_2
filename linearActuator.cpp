#include "linearActuator.h"
#include "GPIO.h"
#include <unistd.h>

using namespace exploringBB;
using namespace std;

LinearActuator::LinearActuator(int upPin, int downPin, int enablePin) {
	this->upPin = upPin;
	this->downPin = downPin;
	this->enablePin = enablePin;
}

void LinearActuator::up() {
	GPIO upGPIO(this->upPin);
	GPIO downGPIO(this->downPin);
	GPIO enableGPIO(this->enablePin);

	upGPIO.setDirection(OUTPUT);
	downGPIO.setDirection(OUTPUT);
	enableGPIO.setDirection(OUTPUT);

	upGPIO.setValue(HIGH);
	downGPIO.setValue(LOW);
	enableGPIO.setValue(HIGH);

	usleep(5000000);

	upGPIO.setValue(LOW);
	enableGPIO.setValue(LOW);
}

void LinearActuator::down() {
	GPIO upGPIO(this->upPin);
	GPIO downGPIO(this->downPin);
	GPIO enableGPIO(this->enablePin);

	upGPIO.setDirection(OUTPUT);
	downGPIO.setDirection(OUTPUT);
	enableGPIO.setDirection(OUTPUT);

	upGPIO.setValue(LOW);
	downGPIO.setValue(HIGH);
	enableGPIO.setValue(HIGH);

	usleep(5000000);

	downGPIO.setValue(LOW);
	enableGPIO.setValue(LOW);
}

