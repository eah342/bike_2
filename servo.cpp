#include <stdio.h>		
#include "servo.h"

using namespace sFnd;

Servo::Servo() {
	this->manager = SysManager::Instance();
};

int Servo::init() {
	try {
		size_t numPorts = 0;
		std::vector<std::string> comHubPorts;

		SysManager::FindComHubPorts(comHubPorts);
		for (numPorts = 0; numPorts < comHubPorts.size() && numPorts < NET_CONTROLLER_MAX; numPorts++)
			this->manager->ComHubPort(numPorts, comHubPorts[numPorts].c_str());

		if (numPorts != 1) {
			printf("Servo Motor failed to initialize. Invalid number of ports\n");
			return -1;
		}
	} catch (mnErr &theErr) {
		printf("Servo Motor failed to initialize.\n");
		printf("Caught error: address = %d, err = 0x%08x\nmsg = %s\n", theErr.TheAddr, theErr.ErrorCode, theErr.ErrorMsg);
		return -1;
	}

	return 0;
}


