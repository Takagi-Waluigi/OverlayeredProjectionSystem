#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 8005

class OscManager
{
public:
	void setup();
	void update();
	ofVec4f getTransformInfo(int id);

	ofxOscReceiver reciever;
	bool isRecieving;

private:
	ofVec4f trackerA, trackerB, marker;
};

