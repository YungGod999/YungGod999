#include "StdAfx.h"
#include "WeightInitializer.h"

namespace NeuralBasic
{
	double WeightInitializer::Generate()
	{
		static std::ranlux64_base_01 gen(static_cast<unsigned int>(time(0))); 
		static std::uniform_real<> range(-1, 1);     
		static std::variate_generator<std::ranlux64_base_01&, std::uniform_real<> >
			generator(gen, range);             

		const double value = generator(); 
		return value;
	}
}