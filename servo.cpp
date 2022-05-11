#include <stdio.h>		
#include "servo.h"

using namespace sFnd;

#define TIMEOUT 10000
#define CHANGE_NUMBER_SPACE 2000

Servo::Servo()
{
	this->manager = SysManager::Instance();
	this->node = NULL;
};

Servo::~Servo()
{
	time_t timeout;
	timeout = time(NULL) + 3;

	this->node->EnableReq(false);
	this->node->Status.RT.Refresh();
	while (this->node->Status.RT.Value().cpm.Enabled) {
		if (time(NULL) > timeout) {
			printf("Error: Timed out trying to disable the node\n");
			return;
		}
		this->node->Status.RT.Refresh();
	};

	printf("Successfully disabled the node\n");

	this->manager->PortsClose();

	printf("Successfully closed the ports\n");
}

int Servo::init()
{
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

		IPort &port0 = this->manager->Ports(0);

		INode &tmpNode = port0.Nodes(0);

		this->node = &tmpNode;
		this->node->Status.AlertsClear();
		this->node->Motion.NodeStopClear();
		this->node->EnableReq(true);
		
		double timeout = this->manager->TimeStampMsec() + TIMEOUT;
		while (!this->node->Motion.IsReady()) {
			if (this->manager->TimeStampMsec() > timeout) {
				printf("Error: Timed out waiting for the node to enable\n");
				return -2;
			}
		}
	} catch (mnErr &theErr) {
		printf("Servo Motor failed to initialize.\n");
		printf("Caught error: address = %d, err = 0x%08x\nmsg = %s\n", theErr.TheAddr, theErr.ErrorCode, theErr.ErrorMsg);
		return -1;
	}

	return 0;
}

int Servo::home()
{
	// motor homing
	if (this->node->Motion.Homing.HomingValid()) {
		double timeout = this->manager->TimeStampMsec() + TIMEOUT;
		
		printf("Homing now...\n");
		
		this->node->Motion.Homing.Initiate();
		while (!this->node->Motion.Homing.WasHomed()) {
			if (this->manager->TimeStampMsec() > timeout) {
				printf("Node did not complete homing.\n");
				return -2;
			}
		}

		this->node->Motion.PosnMeasured.Refresh();

		printf("Node completed homing, current position: \t%8.0f \n", this->node->Motion.PosnMeasured.Value());
		printf("Soft limits now active\n");
		printf("Adjusting Numberspace by %d\n", CHANGE_NUMBER_SPACE);
		this->node->Motion.AddToPosition(CHANGE_NUMBER_SPACE);			//Now the node is no longer considered "homed, and soft limits are turned off
		this->node->Motion.Homing.SignalComplete();		//reset the Node's "sense of home" soft limits (unchanged) are now active again
		this->node->Motion.PosnMeasured.Refresh();		//Refresh our current measured position
		printf("Numberspace changed, current position: \t%8.0f \n", this->node->Motion.PosnMeasured.Value());
	} else {
		printf("The node does not have homing enabled. This should never happen, but if it does re-enable it using clearview..\n");
		return -2;
	}

	return 0;
}		

