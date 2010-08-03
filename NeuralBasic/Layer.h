#pragma once

#include "Neuron.h"

class Layer
{
public:
	Layer(void);
	Layer(const size_t inputsCount, const size_t neuronsCount);

	~Layer(void);

	void Work(const Doubles& m_inputs);
	void Train(const Doubles& inputs, const Doubles& error);
	void TrainFirstLayer(const Doubles& inputs, const Doubles& error);

	const Doubles& GetOutput() const;
	const Doubles& GetError() const;
	size_t GetInputCount() const;
private:
	void Init();

	typedef std::vector<Neuron> Neurons;
	Neurons m_neurons;

	Doubles m_output;
	Doubles m_error;

};

