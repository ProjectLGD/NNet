#pragma once
class Genome
{
public:
	float fitness;
	int ID;
	std::vector<float>* weights;
	Genome();
	~Genome();
};

