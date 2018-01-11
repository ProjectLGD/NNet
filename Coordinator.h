#pragma once
class Coordinator
{

private:
	int currentX;
	int currentY;
	int targetX;
	int targetY;
	bool up, down, left, right;
	NNet *neuralNet;
	int rotation;
	int maxDist;
	int dist;
	std::vector<float> *inputs;

public:
	Coordinator();
	void setCoords(int currentX, int currentY, int targetX, int targetY);
	void resetDir();
	void calculateDir();
	void start();
	bool update();
	void attach(NNet *net);
	void clearFailure();
	int getDist();
	~Coordinator();
};

