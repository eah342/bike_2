#include "analogSensor.h"
#include "GPIO.h"
#include <unistd.h>
#include <sstream>

#define LDR_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"

using namespace exploringBB;
using namespace std;

/*
 *  Constructor for an analog sensor
*/
AnalogSensor::AnalogSensor(int pinNumber) {
	this->pinNumber = pinNumber;
}

/*
 * function for reading an analog sensor
 * this function is derived from code in the beaglebone textbook
*/
int AnalogSensor::read() {
	int value;
	stringstream ss;
	fstream fs;

	// create string stream to read from analog file
	ss << LDR_PATH << this->pinNumber << "_raw";

	// open the file where the analog value is stored and read it
	fs.open(ss.str().c_str(), fstream::in);
	fs >> value;
	fs.close();

	return value;
}

