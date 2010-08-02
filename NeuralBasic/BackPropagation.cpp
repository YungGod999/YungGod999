#include "StdAfx.h"
#include "BackPropagation.h"
#include "Tools.h"


void BackPropagation::Train(const double learningError, const Doubles& inputs, Doubles& weights)
{
	assert(inputs.size() == weights.size());
	ForEach2It(inputs.begin(), inputs.end()
		, weights.begin()
		, [=](const double input, double& weight)
	{
		const double learningRate = 0.001;
		const double gradient = input * learningError;
		const double newDeltaWeight = gradient * learningRate;

		weight += newDeltaWeight;
	}
	);
}
