#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSimpleGrid.h"
#include "ofxAssimpModelLoader.h"
#include "ofxOsc.h"

#define PORT 8005

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void oscReciever();
		void oscDump(ofxOscMessage m);

		ofCamera cam;
		ofEasyCam ecam;

		ofxPanel gui;
		ofParameter<bool> cameraMode;
		ofParameter<vec3> objectPosition;
		ofParameter<float> radius;
		ofParameter<float> rotationY;
		ofParameter<float> roll;
		ofParameter<float> screenWidth;
		ofParameter<float> roomScale;
		ofParameter<bool> enableRecieving;
		ofParameter<float> fov;
		ofVec3f cameraPosition;
		
		
		float addedRoll;
		ofxSimpleGrid grid;

		ofxAssimpModelLoader model;

		ofxOscReceiver reciever;

		ofVec4f TrackerTransformInfo;
		
};
