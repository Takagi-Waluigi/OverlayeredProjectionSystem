#include "OscManager.h"

void OscManager::setup()
{
	reciever.setup(PORT);
	trackerA = ofVec4f(0, 0, 0, 0);
	trackerB = ofVec4f(0, 0, 0, 0);
	marker = ofVec4f(0, 0, 0, 0);
}

void OscManager::update()
{
	isRecieving = false;

	while (reciever.hasWaitingMessages())
	{
		isRecieving = true;

		ofxOscMessage msg;
		reciever.getNextMessage(msg);

		if (msg.getAddress() == "/tracker")
		{
			trackerA.x = msg.getArgAsFloat(0) * 1000;
			trackerA.y = msg.getArgAsFloat(1) * 1000;
			trackerA.z = msg.getArgAsFloat(2) * -1000;
			trackerA.w = -msg.getArgAsFloat(3);
		}

		if (msg.getAddress() == "/trackerB")
		{
			trackerB.x = msg.getArgAsFloat(0) * 1000;
			trackerB.y = msg.getArgAsFloat(1) * 1000;
			trackerB.z = msg.getArgAsFloat(2) * -1000;
			trackerB.w = -msg.getArgAsFloat(3);
		}

		if (msg.getAddress() == "/marker")
		{
			marker.x = msg.getArgAsFloat(0) * 1000;
			marker.y = msg.getArgAsFloat(1) * 1000;
			marker.z = msg.getArgAsFloat(2) * -1000;
			marker.w = -msg.getArgAsFloat(3);
		}
	}
}

ofVec4f OscManager::getTransformInfo(int id)
{
	ofVec4f transform = ofVec4f(0, 0, 0, 0);

	if (id == 0)
	{
		transform = trackerA;
	}
	else if (id == 1)
	{
		transform = trackerB;
	}
	else if (id == 2)
	{
		transform = marker;
	}

	return transform;

}