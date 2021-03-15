#include "LoopUnrolling.h"
#include "Utils.h"

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

// void testDetermineTestBoundsWithStructs()
// {
//     LoopInfo testLoop1 = {
//         1,
//         10,
//         0.234,
//         nullptr,
//     };
//     LoopInfo testLoop2 = {
//         1,
//         10,
//         0.234,
//         nullptr,
//     };
//     int *potentialUnrollFactors = determineUnrollOptions(testLoop1.loopBound);
//     int numUnrollOptions = getArraySize(potentialUnrollFactors);
//     float latencies[getArraySize(potentialUnrollFactors)];
//     for (size_t i = 0; i < getArraySize(potentialUnrollFactors); i++)
//     {
//         latencies[i] = estimateLoopLatency(&testLoop1.loopBound, &potentialUnrollFactors[i], &testLoop1.criticalPathLatency, 0);
//         cout << latencies[i] << endl;
//     }
// }


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

void tryLoopUnrollFactors()
{
	int numLoopLevels = 3;

	int testLoopsBounds[] = { 10, 10, 10 };
	vector<vector<int>> loopUnrollConfigurations = getPossibleLoopUnrollConfigurations(testLoopsBounds, numLoopLevels);

	float testLoopsCriticalPathLatency[] = { 0.200, 0.359, 0.190 };
	vector<float> latencies = getEstimatedLatencies(testLoopsBounds, loopUnrollConfigurations, testLoopsCriticalPathLatency, numLoopLevels);

	for (int idx : sort_indexes(latencies))
	{
		cout << latencies[idx] << endl;
		printVector(loopUnrollConfigurations[idx]);
	}

}

/**
* Finds all combinations of the input vectors
*
* @param[in] potentialUnrollFactor: this is a pointer to a list of entries that occupy one column in the possible combinations
* @param[in] currentCombination: The recursively changed current combination of list entries. This will be a possible combination at the "bottem" of the recursive function hyrarchie
* @param[in] int listDepth
* @param[out] combinations: this is a pointer to a list containing all the possible combination. New combinations are added at the "bottem" of the recursive function hirarchie.
*/
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
