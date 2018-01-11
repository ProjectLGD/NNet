#pragma once
class NNet
{
private:
	int inputAmount;
	int outputAmount;
	std::vector<float>* inputs;
	//Input layer, Hidden layers, loutput layers
	NLayer *inputLayer;

	std::vector<NLayer> *hiddenLayers;
	NLayer *outputLayer;

	std::vector<float>* outputs;
public:
	NNet();
	void refresh();
	void SetInputLayer(std::vector<float>* input);
	float getOutput(int ID);
	//void getOutputLayer(std::vector<float> &output);
	int getTotalOutputs();
	void createNet(int numOfHiddenLayers, int numOfInputs, int NeuronsPerHidden, int numOfOutputs);
	void releaseNet();
	int getNumOfHiddenLayers();

	//GENOME STUFF, GENETIC ALGORITHM
	Genome toGenome();
	void fromGenome(Genome *genome, int numofInputs, int neuronsPerHidden, int numOfOutputs);

	~NNet();
};

