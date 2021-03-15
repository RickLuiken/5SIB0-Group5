#pragma once

// ------ Includes and Namespaces ------ //

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
using namespace std;


// ------ functions ------ //

/*
* Testdummie function
*/
void testMe();
/**
* Prints a vector of type int
*
* @param vector: vector<int> that should be printed
*/
void printVector(vector<int> vector);
/**
* Returns the largest power of the given base that fits in the input
*
* @param base: Base of the power
* @param input: Number in which the power should fit
* @return The largest possible power
*/
int getLargestPower(int input, int base);
/**
* Returns a vector of consecetive powers of the base up-til-and-including the max exponent
*
* @param[in] max outcome of the base to the pow power of the base
* @param[in] base of which the powers are taken
* @return list of powers in vector<int> form
*/
vector<int> getPowerVector(int max, int power);


// ------ Structs and Constants ------ //

struct LoopInfo
{
	int unrollFactor;
	int loopBound;
	float criticalPathLatency;
	LoopInfo* childLoop;
};


// ------ Small utility functions ------ //

template <typename T>
vector<size_t> sort_indexes(const vector<T>& v)
{
	vector<size_t> idx(v.size());
	iota(idx.begin(), idx.end(), 0);
	stable_sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) { return v[i1] < v[i2]; });
	return idx;
}
