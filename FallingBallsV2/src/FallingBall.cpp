#include "FallingBall.h"

FallingBall::FallingBall()
{
	ballColor = ofColor(ofRandom(0, 220), 0, ofRandom(0, 220));// , ofRandom(0, 100));
	reset();
	veloX = 0;
}

void FallingBall::reset()
{
	radius = 30;
	posX = 0;
	posY = 0;
	startPosY = 0;

	veloX = 8;
	veloY = 0;

	accelY = 0;
	accelMod = 0;

	goToRandStartPos();

	float varAccel = ofRandomf() / 500;
	accelMod = varAccel + 0.07;
	accelY = accelMod;
}

void FallingBall::goToRandStartPos()
{
	if (startPosY == 0)
	{
		float startRange = ofGetHeight() / 3;
		startPosY = ofRandom(2 * startRange, ofGetHeight());
	}
	posY = startPosY;
	posX = radius / -2;
}

void FallingBall::setup()
{
	reset();
}

void FallingBall::update()
{
	if (posY < (0 - (radius / 2)))
	{
		reset();
	}

	posX += veloX;

	accelY = accelY + accelMod;
	veloY = veloY + accelY;
	posY = startPosY - veloY;
}

void FallingBall::draw()
{
	ofCircle(posX, posY, radius);
}