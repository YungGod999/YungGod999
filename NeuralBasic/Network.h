#pragma once

#include "Layer.h"

class Network
{
	typedef std::vector<Layer> Layers;
public:
	Network(void);
	~Network(void);

	const std::vector<double>& Work(const Doubles& input);
	void Train(const Doubles& input, const Doubles& error);
private:
	Layers m_layers;
};

