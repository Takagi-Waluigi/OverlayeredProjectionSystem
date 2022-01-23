#include "DrawPatterns.h"

void DrawPatterns::setup()
{
	init_map();
}

void DrawPatterns::update(int channel)
{
	
	switch (channel)
	{
	case 0:
		break;

	case 1:
		break;

	case 2:
		for (int i = 0; i < car.size(); i++)
		{
			car[i].update();
		}
		break;

	}
	
}

void DrawPatterns::draw(int channel, bool user)
{
	ofPushMatrix();
	ofPushStyle();
	ofRotateX(-90);
	switch (channel)
	{
	case 0:
		break;

	case 1:
		drawWavingGrids(ofGetElapsedTimef(), user);
		break;

	case 2:
		draw_map();
		break;
	}

	ofPopStyle();
	ofPopMatrix();
}

void DrawPatterns::init_map()
{
	roadPos.resize(ROAD_NUM);

	for (int i = 0; i < roadPos.size(); i++)
	{
		ofSeedRandom(i * i);
		roadPos[i].x = i * (SCALE / roadPos.size()) + ofRandom(10, SCALE / roadPos.size()) - SCALE/2;
		roadPos[i].y = i * (SCALE / roadPos.size()) + ofRandom(10, SCALE / roadPos.size()) - SCALE/2;
	}

	for (int i = 0; i < car.size(); i++)
	{
		car[i].setup(roadPos, SCALE, i);
	}
	
}

void DrawPatterns::draw_map()
{
	ofPushStyle();
	ofFill();
	ofSetColor(210);
	for (int i = 0; i < roadPos.size(); i++)
	{
		ofDrawRectangle(roadPos[i].x - 20, -SCALE/2, 120, SCALE);
		ofDrawRectangle(-SCALE / 2, roadPos[i].y - 20 , SCALE, 120);
	}

	ofPopStyle();


	for (int i = 0; i < car.size(); i++)
	{
		car[i].draw();
	}
}

void DrawPatterns::drawWavingGrids(float t, bool userMode)
{
	//ofTranslate(0, 0, 0);
	if (userMode)  ofNoFill(); else  ofFill();
	int n = 40;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			ofVec2f p;
			float noise = ofNoise(x, y);
			p.x = (x - n / 2) + 1500 * sin(t * (PI * noise) - noise * TWO_PI) + 1500 * cos(t - noise * PI);
			p.y = (y - n / 2) + 750 * cos(t * (PI * noise)- noise * TWO_PI) + 2350 * sin(t - noise * PI);

			ofSetColor(255 * noise, 0, 255 - 255 * noise);
			
			if (userMode)  ofDrawCircle(p, 130); else ofDrawCircle(p, 100);
		}
	}
	

}