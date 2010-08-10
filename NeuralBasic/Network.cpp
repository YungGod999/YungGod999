#include "StdAfx.h"
#include "Network.h"
#include "Tools.h"

namespace NeuralBasic
{
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
	assert(input.size() == GetInputCount());
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

//back propagate from ouput to input layer
void Network::Train(const Doubles& input, const Doubles& error)
{
	assert(!m_layers.empty());
	if(m_layers.size()>2)
	{
		m_layers.back().Train((m_layers.end()-2)->GetOutput(), error);
		//back propagate from ouput to input layer
		ForEachTrio(m_layers.rbegin(), m_layers.rend()
			, [](Layer& first, Layer& second, Layer& third)
		{
			second.Train(third.GetOutput(), first.GetError());
		}
		);
		m_layers.front().TrainFirstLayer(input, (m_layers.begin()+1)->GetError());
	}
	else if(m_layers.size()==2)
	{
		m_layers.back().Train(m_layers.front().GetOutput(), error);
		m_layers.front().TrainFirstLayer(input, m_layers.back().GetError());
	}
	else if(m_layers.size()==1)
	{
		//first layer do not propagate error to prev layer
		//first layer is learnt without error calculation - optimization
		//first layer input == network input
		m_layers.front().TrainFirstLayer(input, error);
	}
}

size_t Network::GetInputCount() const
{
	if(!m_layers.empty())
		return m_layers.front().GetInputCount();
	return 0;
}

}
