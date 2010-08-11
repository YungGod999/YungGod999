#pragma once

#include "Defines.h"

namespace boost
{
	namespace serialization
	{
		class access;
	}
}
namespace NeuralBasic
{
	class Neuron
	{
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /*version*/)
		{
			ar & BOOST_SERIALIZATION_NVP(m_weights);
		}
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

}