#pragma once

#include "Defines.h"

class Neuron
{
public:
	Neuron(void);
	explicit Neuron(const size_t inputsCount);
	~Neuron(void);

	double Work(const Doubles& m_inputs) const;
	void Train(const Doubles& inputs, const double output, const double error, Doubles& layerError);
	void TrainFirstLayer(const Doubles& inputs, const double output, const double error);
	size_t GetInputsCount() const;

private:
	void CalculateError(const double learningError, Doubles& error) const;

	Doubles m_weights;
};

