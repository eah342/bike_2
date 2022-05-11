#include <stdio.h>
#include <unistd.h>
#include "pubSysCls.h"
#include "servo.h"
#include "linearActuator.h"
#include "digitalSensor.h"

using namespace sFnd;

void servoTest(void);
void linearActuatorTest(void);
void sensorTest(void);
/*
int main(void)
{
	printf("Running linear actuator test\n");
	linearActuatorTest();
	printf("Linear actuator test finished\n");
	
	printf("Running servo motor test\n");
	//servoTest();
	printf("Servo motor test finished\n");

	printf("Running sensor test\n");
	sensorTest();
	printf("Sensor test finished\n");
	
	return 0;
}
*/

void servoTest(void)
{
	int servoInit, servoTurn;

	Servo servo;
	servoInit = servo.init();

	if (servoInit != 0)
		exit(1);

	printf("Successfully initialized the servo motor.\n");

	servoTurn = servo.turn(45.0);

	if (servoTurn != 0)
		exit(1);

	servoTurn = servo.turn(-45.0);

	if (servoTurn != 0)
		exit(1);

	printf("Successfully turned the servo motor.\n");
}

void linearActuatorTest(void)
{
	LinearActuator la(67, 68, 44);

	la.down();
	usleep(1000);
	la.up();
}

void sensorTest(void)
{
	DigitalSensor hall1(27), hall2(46), hall3(47);

	for (int i =  0; i < 10; i++) {
		printf("Iteration %d\n", i);
		printf("Hall 1 value: %d\n", hall1.read());
		printf("Hall 2 value: %d\n", hall2.read());
		printf("Hall 3 value: %d\n\n", hall3.read());
		usleep(1000);
	}
}

