#pragma once

namespace NeuralBasic
{
	class HyperbolicTangent
	{
	public:
		static double Output(const double netValue);
		static double Derivative(const double neuronOutput);
	};


}