#include "Utils.h"


void testMe()
{
	cout << "I've been tested :o" << endl;
}

void printVector(vector<int> vector)
{
	cout << "Vector: ";
	for (int entrie : vector)
	{
		cout << entrie << ", ";
	}
	cout << endl;
}

int getLargestPower(int input, int base)
{
	return floor(log(input) / log(base));
}

vector<int> getPowerVector(int max, int base)
{
	// this can also be done with lookup tables. Unroll factors wont be that high
	int maxExponent = getLargestPower(max, base);
	int exponent = 0;
	vector<int> powerVector;
	while (exponent <= maxExponent) {
		powerVector.push_back(pow(base, exponent));
		exponent++;
	}
	return powerVector;
}