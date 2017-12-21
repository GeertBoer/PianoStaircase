#pragma once
#include "ofMain.h"

class FallingBall
{
private:
	float radius;
	float startPosY;

	float posX;
	float posY;

	float veloX;
	float veloY;

	float accelY;
	float accelMod;
public:
	FallingBall();

	ofColor ballColor;

	void setup();
	void draw();
	void update();

	void goToRandStartPos();
	void reset();
};
