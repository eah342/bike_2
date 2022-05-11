#include <stdio.h>
#include <unistd.h>
#include "pubSysCls.h"
#include "servo.h"
#include "linearActuator.h"

using namespace sFnd;

void servoTest();
void linearActuatorTest();

int main(void)
{
	printf("Running servo motor test\n");
	servoTest();
	printf("Servo motor test finished\n");

	printf("Running linear actuator test\n");
	linearActuatorTest();
	printf("Linear actuator test finished\n");

	return 0;
}

void servoTest()
{
	int servoInit;

	Servo servo;
	servoInit = servo.init();

	if (servoInit != 0)
		exit(1);

	printf("Successfully initialized the servo motor.\n");
}

void linearActuatorTest()
{
	LinearActuator la(67, 68, 44);

	la.down();
	usleep(1000);
	la.up();
}

