#include "StdAfx.h"
#include "HyperbolicTangent.h"

double HyperbolicTangent::Output(const double netValue)
{
	const double output=tanh(netValue);

	return output;
}

double HyperbolicTangent::Derivative(const double neuronOutput)
{
	const double derivative = 1.0 - neuronOutput * neuronOutput;

	return derivative;
}

