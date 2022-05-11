#include "servo.h"
#include <stdio.h>

using namespace sFnd;

//*********************************************************************************
//This program will load configuration files onto each node connected to the port, then executes
//sequential repeated moves on each axis.
//*********************************************************************************

#define ACC_LIM_RPM_PER_SEC	15
#define VEL_LIM_RPM			15
#define NUM_MOVES			1
#define TIME_TILL_TIMEOUT	10000	//The timeout used for homing(ms)

Servo::Servo()
{
	this->manager = SysManager::Instance();
}

int Servo::init()
{
	size_t portCount = 0;
	std::vector<std::string> comHubPorts;

	//This will try to open the port. If there is an error/exception during the port opening,
	//the code will jump to the catch loop where detailed information regarding the error will be displayed;
	//otherwise the catch loop is skipped over
	try
	{ 
		
		SysManager::FindComHubPorts(comHubPorts);
		printf("Found %d SC Hubs\n", comHubPorts.size());

		for (portCount = 0; portCount < comHubPorts.size() && portCount < NET_CONTROLLER_MAX; portCount++) {
			
			this->manager->ComHubPort(portCount, comHubPorts[portCount].c_str()); 	//define the first SC Hub port (port 0) to be associated 
											// with COM portnum (as seen in device manager)
		}

		if (portCount < 0) {
			
			printf("Unable to locate SC hub port\n");

			return -1;  //This terminates the main program
		}
		//printf("\n I will now open port \t%i \n \n", portnum);
		this->manager->PortsOpen(portCount);				//Open the port

		for (size_t i = 0; i < portCount; i++) {
			IPort &myPort = this->manager->Ports(i);

			printf(" Port[%d]: state=%d, nodes=%d\n",
				myPort.NetNumber(), myPort.OpenState(), myPort.NodeCount());

			//Once the code gets past this point, it can be assumed that the Port has been opened without issue
			//Now we can get a reference to our port object which we will use to access the node objects

			for (size_t iNode = 0; iNode < myPort.NodeCount(); iNode++) {
				// Create a shortcut reference for a node
				INode &theNode = myPort.Nodes(iNode);

				theNode.EnableReq(false);				//Ensure Node is disabled before loading config file

				this->manager->Delay(200);

				//theNode.Setup.ConfigLoad("Config File path");

				printf("   Node[%d]: type=%d\n", int(iNode), theNode.Info.NodeType());
				printf("            userID: %s\n", theNode.Info.UserID.Value());
				printf("        FW version: %s\n", theNode.Info.FirmwareVersion.Value());
				printf("          Serial #: %d\n", theNode.Info.SerialNumber.Value());
				printf("             Model: %s\n", theNode.Info.Model.Value());

				//The following statements will attempt to enable the node.  First,
				// any shutdowns or NodeStops are cleared, finally the node is enabled
				theNode.Status.AlertsClear();					//Clear Alerts on node 
				theNode.Motion.NodeStopClear();	//Clear Nodestops on Node  				
				theNode.EnableReq(true);					//Enable node 
				
				//At this point the node is enabled
				printf("Node \t%zi enabled\n", iNode);
				double timeout = this->manager->TimeStampMsec() + TIME_TILL_TIMEOUT;	//define a timeout in case the node is unable to enable
																			//This will loop checking on the Real time values of the node's Ready status
				while (!theNode.Motion.IsReady()) {
					if (this->manager->TimeStampMsec() > timeout) {
						printf("Error: Timed out waiting for Node %d to enable\n", iNode);
						return -2;
					}
				}/*
				//At this point the Node is enabled, and we will now check to see if the Node has been homed
				//Check the Node to see if it has already been homed, 
				if (theNode.Motion.Homing.HomingValid())
				{
					if (theNode.Motion.Homing.WasHomed())
					{
						printf("Node %d has already been homed, current position is: \t%8.0f \n", iNode, theNode.Motion.PosnMeasured.Value());
						printf("Rehoming Node... \n");
					}
					else
					{
						printf("Node [%d] has not been homed.  Homing Node now...\n", iNode);
					}
					//Now we will home the Node
					theNode.Motion.Homing.Initiate();

					timeout = this->manager->TimeStampMsec() + TIME_TILL_TIMEOUT;	//define a timeout in case the node is unable to enable
																			// Basic mode - Poll until disabled
					while (!theNode.Motion.Homing.WasHomed()) {
						if (this->manager->TimeStampMsec() > timeout) {
							printf("Node did not complete homing:  \n\t -Ensure Homing settings have been defined through ClearView. \n\t -Check for alerts/Shutdowns \n\t -Ensure timeout is longer than the longest possible homing move.\n");
							return -2;
						}
					}
					printf("Node completed homing\n");
				}
				else {
					printf("Node[%d] has not had homing setup through ClearView.  The node will not be homed.\n", iNode);
				}
			*/	
			}

			printf("Disabling nodes, and closing port\n");
			//Disable Nodes

			for (size_t iNode = 0; iNode < myPort.NodeCount(); iNode++) {
				// Create a shortcut reference for a node
				myPort.Nodes(iNode).EnableReq(false);
			}
		}
	}
	catch (mnErr& theErr)
	{
		printf("Failed to disable Nodes n\n");
		//This statement will print the address of the error, the error code (defined by the mnErr class), 
		//as well as the corresponding error message.
		printf("Caught error: addr=%d, err=0x%08x\nmsg=%s\n", theErr.TheAddr, theErr.ErrorCode, theErr.ErrorMsg);

		return 0;  //This terminates the main program
	}

	// Close down the ports
	this->manager->PortsClose();

	return 0;			//End program
}

int Servo::turn(float angle)
{
	size_t portCount = 0;
	std::vector<std::string> comHubPorts;

	//This will try to open the port. If there is an error/exception during the port opening,
	//the code will jump to the catch loop where detailed information regarding the error will be displayed;
	//otherwise the catch loop is skipped over
	try
	{ 
		
		SysManager::FindComHubPorts(comHubPorts);
		printf("Found %d SC Hubs\n", comHubPorts.size());

		for (portCount = 0; portCount < comHubPorts.size() && portCount < NET_CONTROLLER_MAX; portCount++) {
			
			this->manager->ComHubPort(portCount, comHubPorts[portCount].c_str()); 	//define the first SC Hub port (port 0) to be associated 
											// with COM portnum (as seen in device manager)
		}

		if (portCount < 0) {
			
			printf("Unable to locate SC hub port\n");

			return -1;  //This terminates the main program
		}
		//printf("\n I will now open port \t%i \n \n", portnum);
		this->manager->PortsOpen(portCount);				//Open the port

		for (size_t i = 0; i < portCount; i++) {
			IPort &myPort = this->manager->Ports(i);

			for (size_t iNode = 0; iNode < myPort.NodeCount(); iNode++) {
				// Create a shortcut reference for a node
				INode &theNode = myPort.Nodes(iNode);
				theNode.EnableReq(false);				//Ensure Node is disabled before loading config file

				this->manager->Delay(200);
				// any shutdowns or NodeStops are cleared, finally the node is enabled
				theNode.Status.AlertsClear();					//Clear Alerts on node 
				theNode.Motion.NodeStopClear();	//Clear Nodestops on Node  				
				theNode.EnableReq(true);	

				theNode.Motion.MoveWentDone();						//Clear the rising edge Move done register

				theNode.AccUnit(INode::RPM_PER_SEC);				//Set the units for Acceleration to RPM/SEC
				theNode.VelUnit(INode::RPM);						//Set the units for Velocity to RPM
				theNode.Motion.AccLimit = ACC_LIM_RPM_PER_SEC;		//Set Acceleration Limit (RPM/Sec)
				theNode.Motion.VelLimit = VEL_LIM_RPM;				//Set Velocity Limit (RPM)

				int counts = convertDegreesToCounts(angle);

				printf("Moving Node \t%zi \n", iNode);
				theNode.Motion.MovePosnStart(counts);			//Execute 10000 encoder count move 
				printf("%f estimated time.\n", theNode.Motion.MovePosnDurationMsec(counts));
				double timeout = this->manager->TimeStampMsec() + theNode.Motion.MovePosnDurationMsec(counts) + 1000000;			//define a timeout in case the node is unable to enable

				while (!theNode.Motion.MoveIsDone()) {
					if (this->manager->TimeStampMsec() > timeout) {
						printf("Error: Timed out waiting for move to complete\n");
						return -2;
					}
				}
				printf("Node \t%zi Move Done\n", iNode);
			} // for each node


			printf("Disabling nodes, and closing port\n");
			//Disable Nodes

			for (size_t iNode = 0; iNode < myPort.NodeCount(); iNode++) {
				// Create a shortcut reference for a node
				myPort.Nodes(iNode).EnableReq(false);
			}
		}
	}
	catch (mnErr& theErr)
	{
		printf("Failed to disable Nodes n\n");
		//This statement will print the address of the error, the error code (defined by the mnErr class), 
		//as well as the corresponding error message.
		printf("Caught error: addr=%d, err=0x%08x\nmsg=%s\n", theErr.TheAddr, theErr.ErrorCode, theErr.ErrorMsg);

		return 0;  //This terminates the main program
	}

	// Close down the ports
	this->manager->PortsClose();

	return 0;			//End program
}

float Servo::getAngle()
{
	float angle;
	size_t portCount = 0;
	std::vector<std::string> comHubPorts;

	//This will try to open the port. If there is an error/exception during the port opening,
	//the code will jump to the catch loop where detailed information regarding the error will be displayed;
	//otherwise the catch loop is skipped over
	try
	{ 
		
		SysManager::FindComHubPorts(comHubPorts);
		printf("Found %d SC Hubs\n", comHubPorts.size());

		for (portCount = 0; portCount < comHubPorts.size() && portCount < NET_CONTROLLER_MAX; portCount++) {
			
			this->manager->ComHubPort(portCount, comHubPorts[portCount].c_str()); 	//define the first SC Hub port (port 0) to be associated 
											// with COM portnum (as seen in device manager)
		}

		if (portCount < 0) {
			
			printf("Unable to locate SC hub port\n");

			return -1;  //This terminates the main program
		}
		//printf("\n I will now open port \t%i \n \n", portnum);
		this->manager->PortsOpen(portCount);				//Open the port

		for (size_t i = 0; i < portCount; i++) {
			IPort &myPort = this->manager->Ports(i);

			for (size_t iNode = 0; iNode < myPort.NodeCount(); iNode++) {
				// Create a shortcut reference for a node
				INode &theNode = myPort.Nodes(iNode);
				theNode.EnableReq(false);				//Ensure Node is disabled before loading config file

				this->manager->Delay(200);
				// any shutdowns or NodeStops are cleared, finally the node is enabled
				theNode.Status.AlertsClear();					//Clear Alerts on node 
				theNode.Motion.NodeStopClear();	//Clear Nodestops on Node  				
				theNode.EnableReq(true);	

				theNode.Motion.MoveWentDone();						//Clear the rising edge Move done register
				
				// Create a variable to return and refresh the position
				theNode.Motion.PosnCommanded.Refresh();

				// If there have been no number wraps, just return the position
				int counts = theNode.Motion.PosnCommanded.Value();
				angle = convertCountsToDegrees(counts);
			} // for each node


			printf("Disabling nodes, and closing port\n");
			//Disable Nodes

			for (size_t iNode = 0; iNode < myPort.NodeCount(); iNode++) {
				// Create a shortcut reference for a node
				myPort.Nodes(iNode).EnableReq(false);
			}
		}
	}
	catch (mnErr& theErr)
	{
		printf("Failed to disable Nodes n\n");
		//This statement will print the address of the error, the error code (defined by the mnErr class), 
		//as well as the corresponding error message.
		printf("Caught error: addr=%d, err=0x%08x\nmsg=%s\n", theErr.TheAddr, theErr.ErrorCode, theErr.ErrorMsg);

		return 0;  //This terminates the main program
	}

	// Close down the ports
	this->manager->PortsClose();

	return 0;			//End program
}

int Servo::convertDegreesToCounts(float degrees)
{
	// 800 counts = 360 degrees
	// round up by default
	return ceil(degrees * (800.0 / 360.0));
}

float Servo::convertCountsToDegrees(int counts)
{
	return counts * (360.0 / 800.0);
}

