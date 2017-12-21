#include <vector>
#include "FallingBallContainer.h"
#include "FallingBall.h"

FallingBallContainer::FallingBallContainer(int amountOfBalls)
{
	for (int i = 0; i < amountOfBalls; i++)
	{
		FallingBall* ball = new FallingBall();
		balls.push_back(ball);
	}
}

void FallingBallContainer::setup()
{
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->setup();
	}
}

void FallingBallContainer::update()
{
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->update();
	}
}

void FallingBallContainer::draw()
{
	for (int i = 0; i < balls.size(); i++)
	{
		ofSetColor(balls[i]->ballColor);
		balls[i]->draw();
	}
}


FallingBallContainer::~FallingBallContainer()
{
	for (int i = 0; i < balls.size(); i++)
	{
		delete balls[i];
	}
}
