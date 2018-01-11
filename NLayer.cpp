#include "stdafx.h"
#include "NLayer.h"


NLayer::NLayer()
{
	neurons = new std::vector<Neuron>();
}

float NLayer::sigmoid(float a, float p)
{
	float ap = (-a) / p;
	return (1 / (1 + exp(ap)));
}

float NLayer::biPolarSigmoid(float a, float p)
{
	float ap = (-a) / p;
	return (2 / (1 +exp(ap)) - 1);
}

void NLayer::evaluate(std::vector<float> input, std::vector<float> &output)
{
	int inputIndex = 0;
	for (int i = 0; i < totalNeurons; i++)
	{
		float activation = 0.0f;

		for (int j = 0; j < neurons->at(i).getNumInputs() - 1; j++)
		{
			activation += input[inputIndex] * neurons->at(i).weights->at(j);
			inputIndex++;
		}

		activation += neurons->at(i).weights->at(neurons->at(i).getNumInputs()) *(-1.0f); //BIAS

		output.push_back(sigmoid(activation, 1.0f));
		inputIndex = 0;
	}
}

void NLayer::loadLayer(std::vector<Neuron>* input)
{
	totalNeurons = input->size();
	neurons = input;
}

void NLayer::populateLayer(int numOfNeurons, int numOfInputs)
{
	totalInputs = numOfInputs;
	totalNeurons = numOfNeurons;

	if (neurons->size() < numOfNeurons)
	{
		for (int i = 0; i < numOfNeurons; i++)
		{
			neurons->push_back(Neuron());
		}
	}

	for (int i = 0; i < numOfNeurons; i++)
		neurons->at(i).populate(numOfInputs);

}

void NLayer::setWeights(std::vector<float> *weights, int numOfNeurons, int numOfInputs)
{
	int index = 0; 
	totalInputs = numOfInputs;
	totalNeurons = numOfNeurons;

	if (neurons->size() < numOfNeurons)
	{
		for (int i = 0; i < numOfNeurons; i++)
		{
			neurons->push_back(Neuron());
		}
	}

	for (int i = 0; i < numOfNeurons; i++)
	{
		if (neurons->at(i).weights->size() < numOfInputs)
		{
			for (int j = 0; j < numOfInputs - neurons->at(i).weights->size(); j++)
			{
				neurons->at(i).weights->push_back(0.0f);
			}
		}

		for (int j = 0; j<numOfInputs; j++) {
			neurons->at(i).weights->at(j) = weights->at(index);
			index++;
		}
	}
}

void NLayer::getWeights(std::vector<float> &output)
{
	output.clear();

	for (int i = 0; i<this->totalNeurons; i++) {
		for (int j = 0; j<neurons->at(i).weights->size(); j++) {
			output[totalNeurons*i + j] = neurons->at(i).weights->at(j);
		}
	}
}

void NLayer::setNeurons(std::vector<Neuron> *neurons, int numOfNeurons, int numOfInputs)
{
	totalInputs = numOfInputs;
	totalNeurons = numOfNeurons;
	this->neurons = neurons;
}






NLayer::~NLayer()
{
	delete(neurons);
}
