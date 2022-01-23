#pragma once
#include "ofMain.h"

class Car
{
public:
	void setup(vector<ofVec2f> mf, int fs, int id);
	void update();
	void draw();

	ofVec2f pos;
	ofVec2f vel;
	ofColor col;
	vector<ofVec2f> mapInfo;
	int fieldSize;

};

