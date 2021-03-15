#include "LoopUnrolling.h"


float estimateLoopLatency(int* loopBound, int* loopUnrollFactor, float* criticalPathLatency, int currentLoopLevel)
{
	float childLoopLatency, childLoopBound, childLoopUnrollFactor, childLoopImpact;
	float  currentLoopUnrollFactor, currentLoopcriticalPathLatency;

	if (currentLoopLevel > 0)
	{
		childLoopLatency = estimateLoopLatency(loopBound + 1, loopUnrollFactor + 1, criticalPathLatency + 1, currentLoopLevel - 1);
		childLoopBound = *(loopBound + 1);
		childLoopUnrollFactor = *(loopUnrollFactor + 1);
		childLoopImpact = childLoopLatency * (childLoopBound / childLoopUnrollFactor);
	}
	else
	{
		childLoopImpact = 0;
	}
	currentLoopUnrollFactor = *loopUnrollFactor;
	currentLoopcriticalPathLatency = *criticalPathLatency;

	return childLoopImpact * currentLoopUnrollFactor + currentLoopcriticalPathLatency;
}

vector<vector<int>> getPossibleLoopUnrollConfigurations(int* loopBounds, int numLoopLevels)
{
	vector<int>* unrollFactors = new vector<int>[numLoopLevels];
	vector<int> currentCombination;
	vector<vector<int>>* allLoopUnrollCombinations = new vector<vector<int>>;

	for (size_t i = 0; i < numLoopLevels; i++)
		unrollFactors[i] = (getPowerVector(loopBounds[i], 2));

	findListCombinations(unrollFactors, currentCombination, allLoopUnrollCombinations, 3);
	allLoopUnrollCombinations->shrink_to_fit();

	return *allLoopUnrollCombinations;
}

vector<float> getEstimatedLatencies(int* loopBounds, vector<vector<int>> unrollFactorsConfigurations, float* criticalPathLatency, int numLoopLevels)
{
	vector<float> latencies;
	for (vector<int> entry : unrollFactorsConfigurations)
	{
		int* potentialUnrollFactors = entry.data();
		latencies.push_back(estimateLoopLatency(loopBounds, potentialUnrollFactors, criticalPathLatency, numLoopLevels - 1));
	}
	return latencies;

}

void tryLoopUnrollFactors(int* loopBounds, float* loopsCriticalPathLatency, int numLoopLevels)
{
	vector<vector<int>> loopUnrollConfigurations = getPossibleLoopUnrollConfigurations(loopBounds, numLoopLevels);
	vector<float> latencies = getEstimatedLatencies(loopBounds, loopUnrollConfigurations, loopsCriticalPathLatency, numLoopLevels);
	for (int idx : sort_indexes(latencies))
	{
		cout << "LL: " << latencies[idx] << endl;
		cout << "UF: ";
		printVector(loopUnrollConfigurations[idx]);
	}

}


void findListCombinations(vector<int>* aList, vector<int> currentCombination, vector<vector<int>>* allCombinations, int numListsLeft)
{
	if (numListsLeft == 0)
	{
		currentCombination.shrink_to_fit();
		(*allCombinations).push_back(currentCombination);
	}
	else
	{
		vector<int> unrolOptions = aList[numListsLeft - 1];
		for (size_t k = 0; k < unrolOptions.size(); k++)
		{
			currentCombination.push_back(unrolOptions[k]);
			findListCombinations(aList + 1, currentCombination, allCombinations, numListsLeft - 1);
			currentCombination.pop_back();
		}
	}
}


void testLoopUnrolling() {
	int numLoopLevels = 3;
	int testLoopsBounds[] = { 10, 10, 10 };
	float testLoopsCriticalPathLatency[] = { 0.234, 0.359, 0.190 };

	tryLoopUnrollFactors(testLoopsBounds, testLoopsCriticalPathLatency, numLoopLevels);
}