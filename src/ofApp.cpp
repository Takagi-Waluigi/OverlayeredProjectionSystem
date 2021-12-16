#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//GUI init
	{
		gui.setup();

		cameraMode.set("camera mode", true);
		screenWidth.set("screen width", 1000, 0, 3000);
		objectPosition.set("camera position", vec3(0, 500, 0), vec3(-10000, 0, -10000), vec3(10000, 2000, 10000));
		roll.set("camera roll", 0, -180, 180);
		radius.set("radius", 10, -1000, 1000);
		rotationY.set("rot Y", 0, 0, 360);
		roomScale.set("room scale", 12, 0, 30);
		enableRecieving.set("enable recieving", false);
		fov.set("fov", 60, 0, 180);

		gui.add(cameraMode);
		gui.add(screenWidth);
		gui.add(objectPosition);
		gui.add(radius);
		gui.add(rotationY);
		gui.add(roll);
		gui.add(roomScale);
		gui.add(enableRecieving);
		gui.add(fov);
	}
	
	//Load Room
	model.loadModel("/scaniverse-20210909-113953.obj");

	//Osc setup
	reciever.setup(PORT);


}

//--------------------------------------------------------------
void ofApp::update(){
	//osc recieving
	{
		if (enableRecieving) oscReciever();
	}

	//camera settings
	{
		cam.setFarClip(100000);
		ecam.setFarClip(100000);

		if (enableRecieving)
		{
			cameraPosition.x = TrackerTransformInfo.x + radius * sin(ofDegToRad(TrackerTransformInfo.w));
			cameraPosition.y = objectPosition->y;
			cameraPosition.z = TrackerTransformInfo.z + radius * cos(ofDegToRad(TrackerTransformInfo.w));

		}
		else
		{
			cameraPosition.x = objectPosition->x + radius * sin(ofDegToRad(rotationY));
			cameraPosition.y = objectPosition->y;
			cameraPosition.z = objectPosition->z + radius * cos(ofDegToRad(rotationY));
		}

		cam.setPosition(cameraPosition);
		cam.lookAt(vec3(cameraPosition.x, 0, cameraPosition.z));

		float addedRot = (enableRecieving) ? TrackerTransformInfo.w + roll : rotationY + roll;

		if(enableRecieving) cam.roll(TrackerTransformInfo.w + roll); else cam.roll(rotationY + roll);

		//fov = ofRadToDeg(PI - atan2(objectPosition->y, objectPosition->x + screenWidth / 2 * cos(-ofDegToRad(addedRoll)) + objectPosition->x) * 2);

		cam.setFov(fov);
	}
	
	//cam.setAspectRatio(0.5625);
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	if (cameraMode) cam.begin(); else ecam.begin();

	
	//’PˆÊ‚Í‡o 10001‚
	grid.draw(16, 500);

	ofNoFill();
	if (!cameraMode)
	{
		ofPushMatrix();
		ofTranslate(0, -1, 0);
		ofRotateX(180);
		ofRotateY(57 - 90);
		//ofSetColor(200, 128);
		//model.disableTextures();
		model.setScale(roomScale, roomScale, roomScale);
		//model.drawWireframe();
		model.drawFaces();
		ofPopMatrix();

		ofPushMatrix();

		ofVec3f op = (enableRecieving) ? ofVec3f(TrackerTransformInfo.x, objectPosition->y, TrackerTransformInfo.z) : ofVec3f(objectPosition);
		float rotY = (enableRecieving) ? TrackerTransformInfo.w : rotationY;

		ofTranslate(op);
		ofRotateY(rotY);
		ofSetColor(255, 0, 0);
		ofDrawBox(0, -op.y / 2, 0, 150, op.y, 150);

		ofPopMatrix();

		ofPushMatrix();
		ofSetColor(0, 255, 0);
		ofTranslate(cameraPosition);
		ofRotateYDeg(rotY);
		ofDrawBox(10);
		ofPopMatrix();

		ofSetColor(255);

		float aspectRatio = ofGetHeight() / ofGetWidth();
		float screenHeight = screenWidth * aspectRatio;

		ofDrawLine(cameraPosition, 
				   vec3(cameraPosition.x - (screenWidth / 2) * cos(-ofDegToRad(rotY)), 
					    0, 
					    cameraPosition.z - (screenWidth / 2) * sin(-ofDegToRad(rotY))));

		ofDrawLine(cameraPosition,
			       vec3(cameraPosition.x + (screenWidth / 2) * cos(-ofDegToRad(rotY)),
				        0,
				        cameraPosition.z + (screenWidth / 2) * sin(-ofDegToRad(rotY))));
	}

	if (cameraMode) cam.end(); else ecam.end();
	ofDisableDepthTest();
	gui.draw();
	ofDrawBitmapString("fov: " + ofToString(fov), ofGetWidth() / 2, 30);
	ofDrawBitmapString("tracker info" + ofToString(TrackerTransformInfo), ofGetWidth() / 2, 45);

}

void ofApp::oscReciever()
{
	while (reciever.hasWaitingMessages())
	{
		ofxOscMessage msg;
		reciever.getNextMessage(msg);

		if (msg.getAddress() == "/leftHand")
		{
			TrackerTransformInfo.x = msg.getArgAsFloat(0) * 1000;
			TrackerTransformInfo.y = msg.getArgAsFloat(1) * 1000;
			TrackerTransformInfo.z = msg.getArgAsFloat(2) * -1000;
			TrackerTransformInfo.w = -msg.getArgAsFloat(3);
		}

		//oscDump(msg);
	}
}

void ofApp::oscDump(ofxOscMessage m)
{
	string msg_string;
	msg_string = m.getAddress();
	for (int i = 0; i < m.getNumArgs(); i++) {
		msg_string += " ";
		if (m.getArgType(i) == OFXOSC_TYPE_INT32)
			msg_string += ofToString(m.getArgAsInt32(i));
		else if (m.getArgType(i) == OFXOSC_TYPE_FLOAT)
			msg_string += ofToString(m.getArgAsFloat(i));
		else if (m.getArgType(i) == OFXOSC_TYPE_STRING)
			msg_string += m.getArgAsString(i);
	}
	cout << msg_string << endl;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
