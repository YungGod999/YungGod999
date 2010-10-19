#include "StdAfx.h"
#include "HyperbolicTangent.h"

namespace NeuralBasic
{
	double HyperbolicTangent::Output(const double netValue)
	{
		//const double output=tanh(netValue);
		const double output = 1.0/(1.0 + exp(-netValue));;//sigmoid

		return output;
	}

	double HyperbolicTangent::Derivative(const double neuronOutput)
	{
		//const double derivative = 1.0 - neuronOutput * neuronOutput;
		const double derivative = neuronOutput * (1.0 - neuronOutput) ;//sigmoid

		return derivative;
	}

}