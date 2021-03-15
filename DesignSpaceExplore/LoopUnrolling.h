#pragma once

// Include libraries and namespaces
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "Utils.h"

using namespace std;

// Define functions
float estimateLoopLatency(int* loopBound, int* loopUnrollFactor, float* criticalPathLatency, int currentLoopLevel);
vector<vector<int>> getPossibleLoopUnrollConfigurations(int* loopBounds, int numLoopLevels);
vector<float> getEstimatedLatencies(int* loopBounds, vector<vector<int>> unrollFactorsConfigurations, float* criticalPathLatency, int numLoopLevels);
void tryLoopUnrollFactors(int* loopBounds, float* loopsCriticalPathLatency, int numLoopLevels);
/**
* Finds all combinations of the input vectors
*
* @param[in] potentialUnrollFactor: this is a pointer to a list of entries that occupy one column in the possible combinations
* @param[in] currentCombination: The recursively changed current combination of list entries. This will be a possible combination at the "bottem" of the recursive function hyrarchie
* @param[in] int listDepth
* @param[out] combinations: this is a pointer to a list containing all the possible combination. New combinations are added at the "bottem" of the recursive function hirarchie.
*/
void findListCombinations(vector<int>* aList, vector<int> currentCombination, vector<vector<int>>* allCombinations, int numListsLeft);
void testLoopUnrolling();