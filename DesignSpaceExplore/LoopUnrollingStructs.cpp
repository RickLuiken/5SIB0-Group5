#include "LoopUnrollingStructs.h"

float estimateLoopLatency(LoopInfo* loop)
{
	float innerLoopImpact;
	float outerLoopUnrollFactor = loop->unrollFactor;
	float outerLoopcriticalPathLatency = loop->criticalPathLatency;
	cout << outerLoopUnrollFactor << ", ";
	LoopInfo* innerLoop = loop->innerLoop;
	if (innerLoop != nullptr)
	{
		float innerLoopLatency = estimateLoopLatency(innerLoop);
		float innerLoopBound = innerLoop->bound;
		float innerLoopUnrollFactor = innerLoop->unrollFactor;

		innerLoopImpact = innerLoopLatency * (innerLoopBound / innerLoopUnrollFactor);
	}
	else
	{
		innerLoopImpact = 0;

		cout << endl;

	}
	return innerLoopImpact * outerLoopUnrollFactor + outerLoopcriticalPathLatency;
}


void getEstimatedLatencies(LoopInfo* topLoop, LoopInfo* loop)
{
	vector<int> unrollOptions = loop->unrollOptions;
	for (int aUnrollFactor : unrollOptions) {
		loop->unrollFactor = aUnrollFactor;
		if (loop->innerLoop == nullptr)
		{

			cout << "UF: ";

			float latency = estimateLoopLatency(topLoop);

			cout << "LL: " << latency << endl;

		}
		else
		{
			getEstimatedLatencies(topLoop, loop->innerLoop);
		}
	}
}

void setLoopUnrollOptions(LoopInfo* loop)
{
	LoopInfo* activeLoop = loop;

	while (activeLoop != nullptr)
	{
		activeLoop->unrollOptions = getPowerVector(activeLoop->bound, 2);
		activeLoop = activeLoop->innerLoop;
	}
}


void tryLoopUnrollFactors(LoopInfo* outerLoop) {

	setLoopUnrollOptions(outerLoop);
	getEstimatedLatencies(outerLoop, outerLoop);
}


void testLoopUnrollingStructs() {

	LoopInfo outerLoop = {
		10,
		vector<int>{},
		1,
		0.234,
		nullptr
	};
	LoopInfo midLoop = {
		10,
		vector<int>{},
		1,
		0.359,
		nullptr
	};
	outerLoop.innerLoop = &midLoop;
	LoopInfo bottomLoop = {
		10,
		vector<int>{},
		1,
		0.190,
		nullptr
	};
	midLoop.innerLoop = &bottomLoop;
	tryLoopUnrollFactors(&outerLoop);
}