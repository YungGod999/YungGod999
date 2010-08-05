#include "StdAfx.h"
#include "Neuron.h"
#include "HyperbolicTangent.h"
#include "BackPropagation.h"
#include "Tools.h"
#include "WeightInitializer.h"

namespace NeuralBasic
{
	Neuron::Neuron(void)
	{
	}

	Neuron::Neuron(const size_t inputsCount)
		: m_weights(inputsCount)
	{
		std::generate(m_weights.begin(), m_weights.end(), 
			[]()
		{
			return WeightInitializer::Generate();
		}
		);
	}

	Neuron::~Neuron(void)
	{
	}

	double Neuron::Work(const Doubles& m_inputs) const
	{
		const double innerProduct = std::inner_product(m_weights.begin(), m_weights.end(), 
			m_inputs.begin(), 0.0);
		const double result = HyperbolicTangent::Output(innerProduct);
		return result;
	}

	void Neuron::Train(const Doubles& inputs, const double output, const double backPropError, Doubles& layerError)
	{
		const double learningError =  backPropError * HyperbolicTangent::Derivative(output);
		CalculateError(learningError, layerError);
		BackPropagation::Train(learningError, inputs, m_weights);
	}

	void Neuron::TrainFirstLayer(const Doubles& inputs, const double output, const double backPropError)
	{
		const double learningError =  backPropError * HyperbolicTangent::Derivative(output);
		BackPropagation::Train(learningError, inputs, m_weights);
	}

	void Neuron::CalculateError(const double learningError, Doubles& error) const
	{
		assert(m_weights.size() == error.size()+BIAS_INPUT);

		//accumulate error from previous layer
		//error(n)=error(n)+m_learningError*m_weights(n)
		ForEach2It(error.begin(), error.end()
			, m_weights.begin()
			,[learningError](double& error, const double weight)
		{
			error = error + weight*learningError;
		}
		);
	}

	size_t Neuron::GetInputsCount() const
	{
		return m_weights.size();
	}

}