// NeuralNetTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int main()
{
	srand(time(0));
	float test;
	test = rand() % 32767;
	cout << test << endl;
	float result;
	result = test / 32767 + 1;
	cout << result << endl;




    return 0;
}

