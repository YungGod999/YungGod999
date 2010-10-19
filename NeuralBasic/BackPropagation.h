#pragma once

namespace NeuralBasic
{
	class  BackPropagation
	{
	public:
		void Train(const double learningError, const std::vector<double>& inputs, std::vector<double>& weights);
		void init(size_t size);
	private:
		std::vector<double> deltas;
	};
}

