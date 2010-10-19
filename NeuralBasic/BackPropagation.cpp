#include "StdAfx.h"
#include "BackPropagation.h"
#include "Tools.h"

namespace NeuralBasic
{
	void BackPropagation::Train(const double learningError, const Doubles& inputs, Doubles& weights)
	{
		assert(inputs.size() == weights.size());
		ForEach3It(inputs.begin(), inputs.end()
			, weights.begin()
			, deltas.begin()
			, [=](const double input, double& delta, double& weight)
		{
			const double learningRate = 0.001;
			const double gradient = input * learningError;
			const double newDeltaWeight = gradient * learningRate + delta*0.6;

			weight += newDeltaWeight;
			delta = newDeltaWeight;
		}
		);
	}

	void BackPropagation::init(size_t size)
	{
		deltas.resize(size);
	}

}