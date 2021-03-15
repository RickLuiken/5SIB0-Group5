#pragma once

// Include libraries and namespaces
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Define functions
// Debugging the latency function
float estimateLoopLatency(int* loopBound, int* loopUnrollFactor, float* criticalPathLatency, int numLoopLevels);
void tryLoopUnrollFactors();
void findListCombinations(vector<int>* potentialUnrollFactor, vector<int> currentCombination, vector<vector<int>>* combinations, int loopLevel);

