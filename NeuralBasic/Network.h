#pragma once
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the NEURALBASIC_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// NEURALBASIC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef NEURALBASIC_EXPORTS
#define NEURALBASIC_API __declspec(dllexport)
#else
#define NEURALBASIC_API __declspec(dllimport)
#endif

#include "Layer.h"


namespace NeuralBasic
{
	class NEURALBASIC_API Network
	{
	public:
		explicit Network(const std::vector<size_t>& networkSize);
		Network(void);
		~Network(void);

		const std::vector<double>& Work(const Doubles& input);
		void Train(const Doubles& input, const Doubles& error);
		size_t GetInputCount() const;
	private:

#pragma warning( push )
#pragma warning( disable : 4251 )
		typedef std::vector<Layer> Layers;
		Layers m_layers;
#pragma warning( pop )
	};

}