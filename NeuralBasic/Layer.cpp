#include "StdAfx.h"
#include "Layer.h"
#include "Tools.h"

Layer::Layer(void)
{
}

Layer::Layer(const size_t inputsCount, const size_t neuronsCount)
{
	assert(inputsCount>0);
	assert(neuronsCount>0);
	for(size_t idx=0; idx<neuronsCount; ++idx)
		m_neurons.push_back(Neuron(inputsCount));

	Init();
}

void Layer::Init()
{
	m_output.resize(m_neurons.size()+BIAS_INPUT);//+1 bias
	m_output.back() = BIAS_VALUE;//bias value
	m_error.resize(GetInputCount()-BIAS_INPUT);//bias is not back propagated
}

Layer::~Layer(void)
{
}

const Doubles& Layer::GetOutput() const
{
	assert(BIAS_INPUT+m_neurons.size()==m_output.size());
	assert(m_output.back()==BIAS_VALUE);
	return m_output;
}

void Layer::Work(const Doubles& m_inputs)
{
	assert(m_neurons.size()+BIAS_INPUT==m_output.size());
	assert(m_inputs.size() == GetInputCount());
	std::transform(m_neurons.begin(), m_neurons.end(),
		m_output.begin(), 
		[&m_inputs](const Neuron& neuron)
	{
		return neuron.Work(m_inputs);
	}
	);
	assert(m_output.back() == BIAS_VALUE);
}

void Layer::Train(const Doubles& inputs, const Doubles& error)
{
	assert(error.size()==m_neurons.size());
	assert(BIAS_INPUT+m_neurons.size()==m_output.size());
	std::fill(m_error.begin(), m_error.end(), 0.0);

	ForEach3It(m_neurons.begin(), m_neurons.end()
		, m_output.begin()
		, error.begin()
		, [&inputs, this](Neuron& neuron, const double output, const double error)
	{
		neuron.Train(inputs, output, error, m_error);
	}
	);
}

void Layer::TrainFirstLayer(const Doubles& inputs, const Doubles& error)
{
	assert(error.size()==m_neurons.size());
	assert(BIAS_INPUT+m_neurons.size()==m_output.size());

	ForEach3It(m_neurons.begin(), m_neurons.end()
		, m_output.begin()
		, error.begin()
		, [&inputs, this](Neuron& neuron, const double output, const double error)
	{
		neuron.TrainFirstLayer(inputs, output, error);
	}
	);
}

const Doubles& Layer::GetError() const
{
	return m_error;
}

size_t Layer::GetInputCount() const
{
	const size_t inputsCount = m_neurons.front().GetInputsCount();
	return inputsCount;
}


