#include "stdafx.h"
#include "Neuron.h"


Neuron::Neuron()
{
	weights = new std::vector<float>();
}

float Neuron::randomFloat()
{
	float test = rand() % 32767;

	float result = test / 32767 + 1;

	return result;
}

float Neuron::randomClamped()
{
	
	float random1 = randomFloat();
	float random2 = randomFloat();
	float clamped = random1 - random2;
	return clamped;
}

float Neuron::clamp(float val, float min, float max)
{
	if (val < min)
		return min;
	else if (val > max)
		return max;
}
///Fills neuron with randomly generated weights
void Neuron::populate(int num)
{
	this->numInputs = num;

	//Initilise the weights
	for (int i = 0; i < num; i++) {
		weights->push_back(randomClamped());
	}

	weights->push_back(randomClamped());
}

void Neuron::initialise(std::vector<float> *weightsIn, int num)
{
	this->numInputs = num;
	this->weights = weightsIn;
}

int Neuron::getNumInputs()
{
	return numInputs;
}
void Neuron::setNumInputs(int num)
{
	numInputs = num;
}

//std::vector<float>* Neuron::getWeights()
//{
//	return weights;
//}


Neuron::~Neuron()
{
	delete(weights);
}
