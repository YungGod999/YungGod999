#include "StdAfx.h"
#include "SaveLoad.h"

#define BOOST_ALL_DYN_LINK
#define BOOST_LIB_DIAGNOSTIC
//boost serialization
#pragma warning( push, 3 )
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#pragma warning( pop )
#include <fstream>

#include "Network.h"

namespace NeuralBasic
{
	void Save(const Network& network, const wchar_t* fileName)
	{
		std::ofstream ofs(fileName);
		if(ofs.good())
		{
			boost::archive::xml_oarchive oa(ofs);

			oa << BOOST_SERIALIZATION_NVP(network);
		}
		else
			throw std::logic_error("NeuralBasic::Save");

	}

	void Load(Network& network, const wchar_t* fileName)
	{
		std::ifstream ifs(fileName);
		if(ifs.good())
		{
			boost::archive::xml_iarchive ia(ifs);

			ia >> BOOST_SERIALIZATION_NVP(network);
		}
		else
			throw std::logic_error("NeuralBasic::Save");
	}
}
