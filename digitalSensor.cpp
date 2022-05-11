#include "digitalSensor.h"
#include "GPIO.h"
#include <unistd.h>

using namespace exploringBB;
using namespace std;

/*
 * Constructor for a digital sensor
*/
DigitalSensor::DigitalSensor(int pinNumber) {
	this->pinNumber = pinNumber;
}

/*
 * Function for reading data from a digitial sensor
*/
int DigitalSensor::read() {
	// init the GPIO object
	GPIO sens(this->pinNumber);

	// set the output direction of the GPIO object
	sens.setDirection(INPUT);

	return sens.getValue();
}

