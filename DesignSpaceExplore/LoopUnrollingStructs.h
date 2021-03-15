#pragma once

// Include libraries and namespaces
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "Utils.h"
using namespace std;

// ------ Structs and Constants ------ //

struct LoopInfo
{
	int bound;
	vector<int> unrollOptions;
	int unrollFactor;
	float criticalPathLatency;
	LoopInfo* innerLoop;
};

// Define functions
float estimateLoopLatency(LoopInfo* loop);
void getEstimatedLatencies(LoopInfo* topLoop, LoopInfo* loop);
void setLoopUnrollOptions(LoopInfo* loop);
void tryLoopUnrollFactors(LoopInfo* outerLoop);
void testLoopUnrollingStructs();