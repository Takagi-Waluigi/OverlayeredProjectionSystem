#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxSimpleGrid.h"
#include "ofxAssimpModelLoader.h"

#include "DrawPatterns.h"
#include "OscManager.h"


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


		ofCamera cam;
		ofEasyCam ecam;

		ofxPanel gui;

		ofParameterGroup communicationSettings;
		ofParameterGroup cameraSettings;
		ofParameterGroup drawingSettings;

		ofParameter<bool> cameraMode;
		ofParameter<vec3> objectPosition;
		ofParameter<float> radius;
		ofParameter<float> rotationY;
		ofParameter<float> roll;
		ofParameter<float> screenWidth;
		ofParameter<float> roomScale;
		ofParameter<bool> enableRecieving;
		ofParameter<float> fov;
		ofParameter<bool> userMode;
		ofParameter<bool> markerVisible;
		ofParameter<bool> gridVisible;
		ofParameter<bool> roomVisible;

		ofParameter<int> channel;
		bool guiVisible;

		ofVec3f cameraPosition;	
		
		float addedRoll;
		ofxSimpleGrid grid;

		ofxAssimpModelLoader model;

		ofFbo fbo;

		ofVec4f TrackerTransformInfo;
		ofVec4f MarkerTransformInfo;

		float hostTime = 0;

		DrawPatterns drawPatterns;

		OscManager om;
};
