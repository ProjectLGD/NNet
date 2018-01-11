// NeuralNetTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int main()
{
	//srand(time(0));
	srand(time(0));
	float test;
	test = rand() % 32767;
	cout << test << endl;
	float result;
	result = test / 32767 + 1;
	cout << result << endl;



	NNet *neuralNet = new NNet();
	neuralNet->createNet(1, 8, 8, 1);
	int totalWeights = 8 * 8 + 8 * 1 + 8 + 1;

	Neuron *n = new Neuron();

	Coordinator *c = new Coordinator();
	Genome *genome;

	for (int i = 0; i < 20; i++)
	{
		std::cout << "start genome" << std::endl;
		srand(time(0));
		genome = new Genome();
		genome->ID = 0;
		genome->fitness = 0.0f;
		genome->weights = new std::vector<float>();
		for (int i = 0; i < totalWeights; i++)
		{
			float weight = n->randomClamped();
			genome->weights->push_back(weight);
		}

		neuralNet->fromGenome(genome, 8, 8, 1);


		bool result = false;
		int runs = 0;
		c->attach(neuralNet);
		c->setCoords(0, 0, 100, 100);
		while (runs < 100 && result == false)
		{
			runs++;
			std::cout <<"current Index: " <<i << " Current runs: " << runs << " current dist: " << c->getDist() << std::endl;
			result = c->update();
		}

		//if (result == true)
			//break;
		std::cout << runs << std::endl;
		

	}
	

	std::cout << "done" << std::endl;


    return 0;
}

