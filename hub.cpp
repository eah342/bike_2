#include "hub.h"
#include "GPIO.h"
#include <unistd.h>

// TODO: verify this speed
#define MAXSPEED 40

using namespace exploringBB;
using namespace std;

/*
 * Constructor for the Hub motor class
*/
Hub::Hub(int period)
{
	this->period = period;
}

/*
 * Deconstructor for the hub motor class
*/
Hub::~Hub()
{
	std::ofstream enableFile, dutyCycleFile;

	// open the file where the duty cycle is written
	dutyCycleFile.open("/sys/class/pwm/pwm-0\\:0/duty_cycle", std::ios::trunc);
	if (!dutyCycleFile)
		printf("Failed to set speed to zero\n");

	// set speed to zero
	dutyCycleFile << 0;

	// close file
	dutyCycleFile.close();

	// open the file where the enable is written
	enableFile.open("/sys/class/pwm/pwm-0\\:0/enable", std::ios::trunc);
	if (!enableFile)
		printf("Failed to disable pwm\n");

	// disable the pwm
	enableFile << 0;

	// close the file
	enableFile.close();
}

/*
 * Init function for the hub motor class
 * this is used instead of the constructor so that we can check if everything initialized correctly
*/
int Hub::init()
{
	std::ofstream enableFile, polarityFile, periodFile;

	// set the polarity
	polarityFile.open("/sys/class/pwm/pwm-0\\:0/polarity", std::ios::trunc);
	if (!polarityFile) {
		printf("Failed to set polarity\n");
		return -1;
	}

	polarityFile << "normal";

	polarityFile.close();
	
	// set the period
	periodFile.open("/sys/class/pwm/pwm-0\\:0/period", std::ios::trunc);
	if (!periodFile) {
		printf("Failed to set period\n");
		return -1;
	}

	periodFile << this->period;

	periodFile.close();
	
	// enable the pwm
	enableFile.open("/sys/class/pwm/pwm-0\\:0/enable", std::ios::trunc);
	if (!enableFile) {
		printf("Failed to enable pwm\n");
		return -1;
	}

	enableFile << 1;

	enableFile.close();

	return 0;
}

/*
 * function for changing the speed of the hub motor
*/
int Hub::changeSpeed(float speed)
{
	std::ofstream file;

	file.open("/sys/class/pwm/pwm-0\\:0/duty_cycle", std::ios::trunc);

	if (!file) {
		printf("Failed to change hub motor speed\n");
		return -1;
	}
	
	// calculate the pwm value from the desired speed
	int pwmVal = this->getPwmValueFromSpeed(speed);	

	// write the pwm value to the duty cycle file
	file << pwmVal;

	file.close();

	return 0;
}

/*
 * function for converting the desired speed of the bike to a pwm
*/
int Hub::getPwmValueFromSpeed(float speed)
{
	// max speed is 40 m/s
	// max pwm value is 4095
	return ceil(4095 * (speed / MAXSPEED));
}

