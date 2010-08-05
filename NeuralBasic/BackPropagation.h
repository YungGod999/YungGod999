#pragma once

namespace NeuralBasic
{
	class  BackPropagation
	{
	public:
		static void Train(const double learningError, const Doubles& inputs, Doubles& weights);
	};
}

