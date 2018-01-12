#include "stdafx.h"
#include "Coordinator.h"


Coordinator::Coordinator()
{
	this->currentX = 0;
	this->currentY = 0;
	this->targetX = 0;
	this->targetY = 0;
	inputs = new std::vector<float>();
	resetDir();

}

void Coordinator::setCoords(int currentX, int currentY, int targetX, int targetY)
{
	this->currentX = currentX;
	this->currentY = currentY;
	this->targetX = targetX;
	this->targetY = targetY;

	maxDist = sqrt(pow(abs(targetX - currentX),2) + pow(abs(targetY - currentY),2));
	
	calculateDir();
}

void Coordinator::calculateDir()
{
	if (currentX < targetX)
		right = true;
	else
		left = true;

	if (currentY < targetY)
		up = true;
	else
		down = true;

	if (currentX < targetY)
	{
		right = true;
	}
	else
		left = true;

	if (currentY < targetY)
		right = false;
	else
		left = true;

}

void Coordinator::resetDir()
{
	this->up = false;
	this->down = false;
	this->left = false;
	this->right = false;
}

void Coordinator::start()
{
	neuralNet = new NNet();
	neuralNet->createNet(1, 8, 8, 1);

	rotation = 0;
}

bool Coordinator::update()
{
	inputs->clear();

	inputs->push_back(currentX);
	inputs->push_back(currentY);
	inputs->push_back(targetX);
	inputs->push_back(targetY);

	inputs->push_back(up);
	inputs->push_back(down);
	inputs->push_back(left);
	inputs->push_back(right);

	std::cout << "---------" << std::endl;
	std::cout << currentX << std::endl;
	std::cout << currentY << std::endl;
	std::cout << targetX << std::endl;
	std::cout << targetY << std::endl;

	std::cout << up << std::endl;
	std::cout << down << std::endl;
	std::cout << left << std::endl;
	std::cout << right << std::endl;

	neuralNet->SetInputLayer(inputs);
	neuralNet->refresh();

	rotation = neuralNet->getOutput(0);
	std::cout << "rotation: " <<rotation << std::endl;
	
	currentX += cos((rotation*360) * M_PI / 180.0f);
	currentY += sin((rotation*360) * M_PI / 180.0f);
	std::cout << "currentX: " << currentX << " currentY: " << currentY << std::endl;

	//dist = maxDist - sqrt(pow(abs(targetX - currentX), 2) + pow(abs(targetY - currentY), 2));

	if (currentX > targetX - 5 && currentX < targetX + 5)
	{
		if (currentY > targetY - 5 && currentY < targetY + 5)
		{
			return true;
		}
	}		
	

	return false;

}

void Coordinator::attach(NNet *net)
{
	neuralNet = net;
}

void Coordinator::clearFailure()
{
	dist = 0;
}

int Coordinator::getDist()
{
	return dist;
}


Coordinator::~Coordinator()
{
}
