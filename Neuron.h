#pragma once
class Neuron
{
private:
	int numInputs;
	
public:
	std::vector<float> *weights;

	Neuron();
	float randomFloat();
	float randomClamped();
	float clamp(float val, float min, float max); //could just be round();
	void  populate(int num);
	void  initialise(std::vector<float> *weightsInput, int num);

	int getNumInputs();
	void setNumInputs(int num);

	/*std::vector<float>* getWeights();
	void setWeights(std::vector<float>* weights);*/
	~Neuron();
};

