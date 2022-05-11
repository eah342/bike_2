#include "linearActuator.h"
#include "GPIO.h"
#include <unistd.h>

#define SLEEP_DURATION 5000000

using namespace exploringBB;
using namespace std;

/*
 * constructor for the linear actuator class
*/
LinearActuator::LinearActuator(int upPin, int downPin, int enablePin) {
	this->upPin = upPin;
	this->downPin = downPin;
	this->enablePin = enablePin;
}

/*
 * function to lift up the linear actuator
*/
void LinearActuator::up() {
	// initialize the GPIO objects
	GPIO upGPIO(this->upPin);
	GPIO downGPIO(this->downPin);
	GPIO enableGPIO(this->enablePin);

	// set the GPIO objects to output
	upGPIO.setDirection(OUTPUT);
	downGPIO.setDirection(OUTPUT);
	enableGPIO.setDirection(OUTPUT);

	// set the values appropriately for moving up
	upGPIO.setValue(HIGH);
	downGPIO.setValue(LOW);
	enableGPIO.setValue(HIGH);

	// sleep for as long as it takes for the wheels to move up
	usleep(SLEEP_DURATION);

	// stop moving the linear actuator and disable it
	upGPIO.setValue(LOW);
	enableGPIO.setValue(LOW);
}

/*
 * function to lower the linear actuator
*/
void LinearActuator::down() {
	// initialize the GPIO objects
	GPIO upGPIO(this->upPin);
	GPIO downGPIO(this->downPin);
	GPIO enableGPIO(this->enablePin);

	// set the GPIO objects to output
	upGPIO.setDirection(OUTPUT);
	downGPIO.setDirection(OUTPUT);
	enableGPIO.setDirection(OUTPUT);

	// set the values appropriately for moving down
	upGPIO.setValue(LOW);
	downGPIO.setValue(HIGH);
	enableGPIO.setValue(HIGH);

	// sleep for as long as it takes for the wheels to move down
	usleep(SLEEP_DURATION);

	// stop moving the linear actuator and disable it
	downGPIO.setValue(LOW);
	enableGPIO.setValue(LOW);
}

