// NeuralNetTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int main()
{
	///TEST STUFF, IGNORE
	//srand(time(0));
	srand(time(0));
	float test;
	test = rand() % 32767;
	cout << test << endl;
	float result;
	result = test / 32767 + 1;
	cout << result << endl;


	///Creating neural network here, create net sets up the layers of the neural network (in this case 1 hidden layer, 8 input neurons, 
	///8 neuron per hidden layer, 1 output neuron 
	NNet *neuralNet = new NNet();
	neuralNet->createNet(1, 8, 8, 1);
	int totalWeights = 8 * 8 + 8 * 1 + 8 + 1;

	///Just there to access mathmatical functions
	Neuron *n = new Neuron();

	///Coordinator which will run each Neural network
	Coordinator *c = new Coordinator();
	///Genome to be used by Neural network
	Genome *genome;
	
	///For loop that makes 20 neural networks with random genomes to run.
	for (int i = 0; i < 20; i++)
	{
		std::cout << "start genome" << std::endl;
		srand(time(0));

		///Generate new genome
		genome = new Genome();
		genome->ID = 0;
		genome->fitness = 0.0f;
		genome->weights = new std::vector<float>();
		srand(time(0));
		///The genome is filled with random weights
		for (int i = 0; i < totalWeights; i++)
		{
			float weight = n->randomClamped();
			genome->weights->push_back(weight);
		}

		///The genome is given to the neural network, the neural network fills its structure with the given weights
		neuralNet->fromGenome(genome, 8, 8, 1);

		bool result = false;
		int runs = 0;
		///Give the coordinator the neural network to run
		c->attach(neuralNet);		
		///Set begin and end conditions
		c->setCoords(0, 0, 100, 100);
		while (runs < 100 && result == false)
		{
			runs++;
			std::cout <<"current Index: " <<i << " Current runs: " << runs << " current dist: " << c->getDist() << std::endl;
			///Updates the neural network, this updates the input values and enters them into the neural network again
			///Result returns true if destination is reached, thus ending the run
			result = c->update();
			
		}

		//if (result == true)
			//break;
		std::cout << runs << std::endl;
		

	}
	

	std::cout << "done" << std::endl;


    return 0;
}

