#pragma once

#include "Defines.h"
#include "BackPropagation.h"

#ifdef NEURALBASIC_EXPORTS
#define NEURALBASIC_API __declspec(dllexport)
#else
#define NEURALBASIC_API __declspec(dllimport)
#endif

namespace boost
{
	namespace serialization
	{
		class access;
	}
}
namespace NeuralBasic
{
	class NEURALBASIC_API Neuron
	{
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int /*version*/)
		{
			ar & BOOST_SERIALIZATION_NVP(m_weights);
			backPropagation.init(m_weights.size());
		}
	public:
		Neuron(void);
		explicit Neuron(const size_t inputsCount);
		~Neuron(void);

		double Work(const std::vector<double>& m_inputs) const;
		void Train(const std::vector<double>& inputs, const double output, const double error, std::vector<double>& layerError);
		void TrainFirstLayer(const std::vector<double>& inputs, const double output, const double error);
		size_t GetInputsCount() const;

	private:
		void CalculateError(const double learningError, std::vector<double>& error) const;

#pragma warning( push )
#pragma warning( disable : 4251 )
		std::vector<double> m_weights;
		BackPropagation backPropagation;
#pragma warning( pop )
	};

}