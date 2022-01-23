#pragma once
#include "ofMain.h"

#include "Car.h"

#define SCALE 7000
#define ROAD_NUM 8

class DrawPatterns
{
public:
	void setup();
	void update(int channel);
	void draw(int channel, bool user);

	void init_map();
	void draw_map();
	
	vector<ofVec2f> roadPos;
	array<Car, 500> car;

	void drawWavingGrids(float t, bool userMode);
};

