#include "stdafx.h"
#include "Genome.h"


Genome::Genome()
{
	weights = new std::vector<float>();
}


Genome::~Genome()
{
	delete(weights);
}
