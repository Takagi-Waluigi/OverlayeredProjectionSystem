#include "Car.h"

void Car::setup(vector<ofVec2f> mf, int fs, int id)
{
	mapInfo = mf;
	fieldSize = fs;

	float rand = ofNoise((id + PI) * (id + PI));

	std::cout << rand << endl;
	col = ofColor(ofRandom(180), ofRandom(180), ofRandom(180));
	if (rand < 0.5)
	{

		float randSelection = ofRandom(mapInfo.size());
	
		for (int i = 0; i < mapInfo.size(); i++)
		{
			if (i - 1 < randSelection && randSelection <= i)
			{
				if (rand < 0.25)
				{
					pos.x = mapInfo[i].x + 25;
					pos.y = fieldSize * 0.5;

					vel.x = 0;
					vel.y = -2 * rand;
				}
				else
				{
					pos.x = mapInfo[i].x + 75;
					pos.y = -fieldSize;

					vel.x = 0;
					vel.y = 2 * rand;
				}

			}
		}
	}
	else
	{
		float randSelection = ofRandom(mapInfo.size());

		for (int i = 0; i < mapInfo.size(); i++)
		{
			if (i - 1 < randSelection && randSelection <= i)
			{
				if (rand < 0.75)
				{
					pos.x = -fieldSize * 0.5;
					pos.y = mapInfo[i].y + 25;

					vel.x = ofRandom(1, 2);
					vel.y = 0.0;
				}
				else
				{
					pos.x = fieldSize * 0.5;
					pos.y = mapInfo[i].y + 75;

					vel.x = -ofRandom(1, 2);
					vel.y = 0.0;
				}

			}
		}
	}

}

void Car::update()
{
	if (abs(pos.x) > fieldSize * 0.5 || abs(pos.y) > fieldSize * 0.5)
	{
		float rand = ofRandom(1);

		if (rand < 0.5)
		{
			float randSelection = mapInfo.size() * ofRandom(1);

			for (int i = 0; i < mapInfo.size(); i++)
			{
				if (i - 1 < randSelection && randSelection <= i)
				{
					if (rand < 0.25)
					{
						pos.x = mapInfo[i].x + 25;
						pos.y = fieldSize * 0.5;

						vel.x = 0;
						vel.y = -ofRandom(1, 2);
					}
					else
					{
						pos.x = mapInfo[i].x + 75;
						pos.y = -fieldSize;

						vel.x = 0;
						vel.y = ofRandom(1, 2);
					}
					
				}
			}
		}
		else
		{

			float randSelection = mapInfo.size() * ofRandom(1);

			for (int i = 0; i < mapInfo.size(); i++)
			{
				if (i - 1 < randSelection && randSelection <= i)
				{
					if (rand < 0.75)
					{
						pos.x = -fieldSize * 0.5;
						pos.y = mapInfo[i].y + 25;

						vel.x = ofRandom(1, 2);
						vel.y = 0.0;
					}
					else
					{
						pos.x = fieldSize * 0.5;
						pos.y = mapInfo[i].y + 75;

						vel.x = -ofRandom(1, 2);
						vel.y = 0.0;
					}

				}
			}
		}
	}

	pos += vel;
}

void Car::draw()
{
	ofDisableDepthTest();
	ofPushStyle();
	ofFill();
	ofSetColor(col);
	ofDrawCircle(pos.x, pos.y, 10, 40);
	
	ofPopStyle();

	ofEnableDepthTest();
}