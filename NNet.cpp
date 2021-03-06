#include "stdafx.h"
#include "NNet.h"


///Initialise Neural networks
NNet::NNet()
{
	inputs = new std::vector<float>();
	outputs = new std::vector<float>();
	inputLayer = new NLayer();
	outputLayer = new NLayer();
	hiddenLayers = new std::vector<NLayer*>();
}

///Pulls input values through all the hidden layers, then generates output layer
void NNet::refresh()
{
	outputs->clear();

	for (int i = 0; i < hiddenLayers->size(); i++) {
		if (i > 0) {
			inputs = outputs;
		}
		hiddenLayers->at(i)->evaluate(*inputs,*outputs);

	}
	inputs = outputs;
	
	outputLayer->evaluate(*inputs, *outputs);
}

void NNet::SetInputLayer(std::vector<float> *input)
{
	inputs = input;
}
///Get output from output layer
float NNet::getOutput(int ID)
{
	if (ID >= outputAmount)
		return 0.0f;
	return outputs->at(ID);
}

int NNet::getTotalOutputs()
{
	return outputAmount;
}

///Sets up Neural network structure based on parameters
void NNet::createNet(int numOfHIddenLayers, int numOfInputs, int NeuronsPerHidden, int numOfOutputs)
{
	inputAmount = numOfInputs;
	outputAmount = numOfOutputs;
	
	for (int i = 0; i<numOfHIddenLayers; i++) {
		NLayer *layer = new NLayer();
		layer->populateLayer(NeuronsPerHidden, numOfInputs);
		hiddenLayers->push_back(layer);
	}

	outputLayer = new NLayer();
	outputLayer->populateLayer(numOfOutputs, NeuronsPerHidden);
	std::cout << "net created" << std::endl;
}

///Clears neural network structure
void NNet::releaseNet()
{

	if (inputLayer != nullptr) {
		delete(inputLayer);
		inputLayer = new NLayer();
	}
	if (outputLayer != nullptr) {
		delete(inputLayer);
		outputLayer = new NLayer();
	}
	//for (int i = 0; i<hiddenLayers->size(); i++) {
	//	//if (hiddenLayers->at(i) !=nullptr) {
	//		delete(hiddenLayers[i]);
	//	//}
	//}
	
	delete(hiddenLayers);
	hiddenLayers = new std::vector<NLayer*>();
}

int NNet::getNumOfHiddenLayers()
{
	return hiddenLayers->size();
}


///Not used, converts Neural network structure back to genome of weights
Genome NNet::toGenome()
{
	Genome genome;

	for (int i = 0; i<this->hiddenLayers->size(); i++) {
		std::vector<float> *weights = new std::vector<float>();
		hiddenLayers->at(i)->getWeights(*weights);
		for (int j = 0; j<weights->size(); j++) {
			genome.weights->push_back(weights->at(j));
		}
	}

	std::vector<float> *outweights = new std::vector<float>();
	outputLayer->getWeights(*outweights);
	for (int i = 0; i<outweights->size(); i++) {
		genome.weights->push_back(outweights->at(i));
	}

	return genome;
}


///Fills neural network structure with the weights supplied by the genome.
void NNet::fromGenome(Genome *genome, int numofInputs, int neuronsPerHidden, int numOfOutputs)
{
	releaseNet();

	outputAmount = numOfOutputs;
	inputAmount = numofInputs;

	int weightsForHidden = numofInputs * neuronsPerHidden;
	NLayer *hidden = new NLayer();

	std::vector<Neuron*> *neurons = new std::vector<Neuron*>();
	

	for (int i = 0; i<neuronsPerHidden; i++) {
		//init
		Neuron *n = new Neuron();
		neurons->push_back(n);
		std::vector<float> *weights = new std::vector<float>();
		
		
		for (int j = 0; j<numofInputs + 1; j++) {
			weights->push_back(0.0f);
			weights->at(j) = genome->weights->at(i*neuronsPerHidden + j);
		}
		neurons->at(i)->weights = new std::vector<float>();
		neurons->at(i)->initialise(weights, numofInputs);
		
	}
	hidden->loadLayer(neurons);

	this->hiddenLayers->push_back(hidden);

	///Clear weights and reasign the weights to the output
	int weightsForOutput = neuronsPerHidden * numOfOutputs;
	std::vector<Neuron*> *outNeurons = new std::vector<Neuron*>();


	for (int i = 0; i < numOfOutputs; i++) {
		Neuron *n = new Neuron();
		outNeurons->push_back(n);

		std::vector<float> *weights = new std::vector<float>();

		for (int j = 0; j < neuronsPerHidden + 1; j++) {
			weights->push_back(0.0f);
			weights->at(j) = genome->weights->at(i*neuronsPerHidden + j);
		}
		outNeurons->at(i)->weights = new std::vector<float>();
		outNeurons->at(i)->initialise(weights, neuronsPerHidden);
		
		
	}
	this->outputLayer = new NLayer();
	this->outputLayer->loadLayer(outNeurons);

}



NNet::~NNet()
{
	delete(inputs);
	delete(outputs);
	delete(inputLayer);
	delete(outputLayer);
	delete(hiddenLayers);
}
