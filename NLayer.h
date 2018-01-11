#pragma once
class NLayer
{
private:
	int totalNeurons;
	int totalInputs;

	std::vector<Neuron> *neurons;
public:
	NLayer();
	float sigmoid(float a, float p);
	float biPolarSigmoid(float a, float p);
	void evaluate(std::vector<float> input, std::vector<float> &output);
	void loadLayer(std::vector<Neuron> *input);
	void populateLayer(int numOfNeurons, int numOfInputs);
	void setWeights(std::vector<float> *weights, int numOfNeurons, int numOfInputs);
	void getWeights(std::vector<float> &output);
	void setNeurons(std::vector<Neuron> *neurons, int numOfNeurons, int numOfInputs);



	~NLayer();
};

