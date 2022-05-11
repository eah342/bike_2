#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "pubSysCls.h"
#include "servo.h"
#include "linearActuator.h"
#include "digitalSensor.h"

using namespace sFnd;
using namespace std;

static Servo servo;
static LinearActuator linearActuator(67, 68, 44);
static DigitalSensor hall1(27), hall2(46), hall3(47);

void printMainMenu();
void servoMenu();
void linearActuatorMenu();
void sensorMenu();

int main(void)
{
	//servo.init();

	int choice;
	while (1) {
		printMainMenu();
		cout << "Choose an option: ";
		cin >> choice;
		if (choice == 1) {
			servoMenu();
		}
		else if (choice == 2) {
			cout << "Hub motor code is not testable yet" << endl;
		}
		else if (choice == 3) {
			linearActuatorMenu();
		}
		else if (choice == 4) {
			sensorMenu();
		}
		else if (choice == 5) {
			cout << "Goodbye!" << endl;
			break;
		}
		else {
			cout << "Invalid choice" << endl;
		}
	}
	return 0;
}

void printMainMenu()
{
	cout << "1. Servo Motor" << endl;
	cout << "2. Hub Motor" << endl;
	cout << "3. Linear Actuator" << endl;
	cout << "4. Sensors" << endl;
	cout << "5. Exit" << endl;
}

void servoMenu()
{
	float angle;

	cout << "Enter the angle you would like to turn the servo: ";
	cin >> angle;

	servo.turn(angle);
}

void linearActuatorMenu()
{
	int up;
	
	cout << "Enter 1 for up, or 2 for down: ";
	cin >> up;

	if (up == 1)
		linearActuator.up();
	else if (up == 2)
		linearActuator.down();
}

void sensorMenu()
{
	cout << "Displaying sensor values for 5 seconds:" << endl;

	for (int i =  0; i < 5; i++) {
		printf("Iteration %d\n", i);
		printf("Hall 1 value: %d\n", hall1.read());
		printf("Hall 2 value: %d\n", hall2.read());
		printf("Hall 3 value: %d\n\n", hall3.read());
		usleep(1000);
	}
}

