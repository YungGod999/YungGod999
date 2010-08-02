#include "StdAfx.h"
#include "Network.h"
#include "Tools.h"


Network::Network(void)
{
}

//
//networkSize[0] - inputs count
//networkSize[1] - neurons count in layer 0, each neuron has networkSize[0] weights
//networkSize[2] - neurons count in layer 1, each neuron has networkSize[1] weights
//...
//networkSize.back() - neurons count in last layer, and network outputs count
Network::Network(const std::vector<size_t>& networkSize)
{
	assert(networkSize.size()>1);
	assert(std::find(networkSize.begin(), networkSize.end(), 0)== networkSize.end());
	if(networkSize.size()>1)
	{
		ForEachPair(networkSize.begin(), networkSize.end()
			, [this](const size_t inputsCount, const size_t neuronsCount)
		{
			assert(inputsCount>0 && neuronsCount>0);
			m_layers.push_back(Layer(inputsCount+BIAS_INPUT
				, neuronsCount));
		}
		);
	}
}

Network::~Network(void)
{
}

const Doubles& Network::Work(const Doubles& input)
{
	assert(input.size() == BIAS_INPUT+GetInputCount());
	assert(input.back() == BIAS_VALUE );
	assert(!m_layers.empty());

	m_layers.front().Work(input);

	ForEachPair(m_layers.begin(), m_layers.end()
		, [](const Layer& prev, Layer& next)
	{
		next.Work(prev.GetOutput());
	}
	);
	//output from last layer it is Network output
	return m_layers.back().GetOutput();

}

void Network::Train(const Doubles& input, const Doubles& error)
{
	assert(!m_layers.empty());
	const Layers::reverse_iterator rBegin = m_layers.rbegin();
	//first layer is calculated different way then others
	const Layers::reverse_iterator rEnd = m_layers.rend()-1;

	for(Layers::reverse_iterator it = rBegin; 
		it!=rEnd; ++it)
	{
		const Doubles& layerInput = GetInputR(it);
		const Doubles& layerError = GetError(it, rBegin, error);

		(*it).Train(layerInput, layerError);
	}

	//first layer do not propagate error
	//first layer is learnt without error calculation - optimization
	//first layer input == network input
	m_layers.front().TrainFirstLayer(input, GetError(rEnd, rBegin, error));
}

size_t Network::GetOutputCount() const
{
	if(!m_layers.empty())
		return m_layers.back().GetOutput().size();

	return 0;
}

size_t Network::GetInputCount() const
{
	return m_layers.front().GetInputCount();
}

