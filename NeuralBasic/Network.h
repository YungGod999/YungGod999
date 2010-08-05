#pragma once

#include "Layer.h"

namespace NeuralBasic
{
	class Network
	{
	public:
		explicit Network(const std::vector<size_t>& networkSize);
		Network(void);
		~Network(void);

		const std::vector<double>& Work(const Doubles& input);
		void Train(const Doubles& input, const Doubles& error);
	private:
		size_t GetInputCount() const;

		typedef std::vector<Layer> Layers;
		Layers m_layers;
	};

}