#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetFullscreen(true);
	ofSetVerticalSync(false);

	ofSetBackgroundColor(0);

	//GUI init
	{
		gui.setup();

		cameraMode.set("camera mode", true);
		screenWidth.set("screen width", 1000, 0, 3000);
		objectPosition.set("camera position", vec3(0, 500, 0), vec3(-10000, 0, -10000), vec3(10000, 2000, 10000));
		roll.set("camera roll", 0, -180, 180);
		radius.set("radius", 10, -1000, 1000);
		rotationY.set("rot Y", 0, 0, 360);
		roomScale.set("room scale", 24, 0, 30);
		enableRecieving.set("enable recieving", false);
		fov.set("fov", 60, 0, 180);
		userMode.set("user selection", false);
		markerVisible.set("marker visible", true);
		channel.set("channel", 0, 0, 10);
		gridVisible.set("grid visible", true);
		roomVisible.set("room visible", true);

		communicationSettings.setName("communication settings");
		communicationSettings.add(userMode);
		communicationSettings.add(enableRecieving);

		cameraSettings.setName("camera settings");
		cameraSettings.add(cameraMode);
		cameraSettings.add(markerVisible);
		cameraSettings.add(radius);
		cameraSettings.add(fov);
		cameraSettings.add(roll);
		cameraSettings.add(objectPosition);
		cameraSettings.add(rotationY);
		
		drawingSettings.setName("drawing settings");
		drawingSettings.add(gridVisible);
		drawingSettings.add(roomVisible);
		drawingSettings.add(channel);
		//drawingSettings.add(roomScale);
		
	
		gui.add(communicationSettings);
		gui.add(cameraSettings);
		gui.add(drawingSettings);

		guiVisible = true;
		
	}
	
	//Load Room
	model.loadModel("/scaniverse-20210909-113953.obj");

	//OSC setup
	om.setup();

	//Drawing Patterns Setup
	drawPatterns.setup();

	
}

//--------------------------------------------------------------
void ofApp::update(){
	//osc update
	{
		if (enableRecieving) om.update();
		int id = (userMode) ? 0 : 1;
		TrackerTransformInfo = om.getTransformInfo(id); //0: trackerA, 1: trackerB, 2:marker
		MarkerTransformInfo = om.getTransformInfo(2);
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

		cam.setFov(fov);
	}
	
	//draw patterns update
	{
		drawPatterns.update(channel);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	if (cameraMode) cam.begin(); else ecam.begin();

	//単位は㎜ 1000＝1ｍ
	if(gridVisible) grid.draw(15, 1000);			 //指標グリッド
	drawPatterns.draw(channel, userMode); //描画パターン

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
		if(roomVisible) model.drawWireframe();
		//model.drawFaces();
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

	//Marker
	if (markerVisible)
	{
		ofPushMatrix();
		ofPushStyle();

		ofTranslate(MarkerTransformInfo.x, MarkerTransformInfo.y, MarkerTransformInfo.z);
		ofRotateX(90);
		ofFill();
		ofSetColor(255);
		ofDrawCircle(0, 0, 30);

		ofNoFill();
		ofSetLineWidth(10);
		ofSetColor(255, 0, 0);
		ofDrawCircle(0, 0, 40);

		ofPopStyle();
		ofPopMatrix();
	}
	if (cameraMode) cam.end(); else ecam.end();
	ofDisableDepthTest();

	//GUI
	{
		if (guiVisible)
		{
			ofPushStyle();
			ofFill();
			gui.draw();
			if (om.isRecieving) ofSetColor(0, 255, 0); else ofSetColor(255, 0, 0);
			ofDrawRectangle(ofGetWidth() / 2, 20, 10, 10);
			ofSetColor(255);
			ofDrawBitmapString("recieving status", ofGetWidth() / 2 + 20, 30);
			ofDrawBitmapString("tracker info: " + ofToString(TrackerTransformInfo), ofGetWidth() / 2, 45);
			ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), ofGetWidth() / 2, 60);
			ofPopStyle();
		}
		
	}
	
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') guiVisible = !guiVisible;
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
