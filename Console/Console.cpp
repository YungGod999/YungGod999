// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

NeuralBasic::Network CreateNetwork()
{
	std::vector<size_t> networkSize;
	networkSize.push_back(4);//inputs count
	networkSize.push_back(6);//neurons count in layer 1
	networkSize.push_back(6);//neurons count in layer 2 and and outputs count
	NeuralBasic::Network network(networkSize);
	return network;
}

class Data
{
public:
	Data()
	{
	}

	std::vector<double> GetInput() const
	{
		return m_input;
	}

	std::vector<double> GetDesired() const
	{
		return m_desired;
	}

	bool IsRecognized(const std::vector<double>& /*networkOutput*/) const
	{
		return true;
	}
private:
	std::vector<double> m_input;
	std::vector<double> m_desired;
};

std::vector<Data> GetTrainData()
{
	std::vector<Data> data;

	return data;
}

std::vector<Data> GetTestData()
{
	std::vector<Data> data;

	return data;
}

void TrainNetwork(NeuralBasic::Network& network)
{
	std::cout << "Training neural network..." << std::endl;
	const std::vector<Data>& data = GetTrainData();

	const size_t trainRoundCount = 100;
	for(size_t idx=0; idx<trainRoundCount; ++idx)
	{
		std::for_each(data.begin(), data.end() 
			, [&network](const Data& data)
		{
			const std::vector<double>& output = network.Work(data.GetInput());
			std::vector<double> error;
			//error = desired-output
			std::transform(data.GetDesired().begin(), data.GetDesired().end()
				, output.begin()
				, std::back_inserter(error)
				, std::minus<double>());
			network.Train(data.GetInput(), error);
		}
		);
	}
}

void TestNetwork(NeuralBasic::Network& network)
{
	std::cout << "Testing neural network..." << std::endl;
	const std::vector<Data>& data = GetTestData();
	const size_t recognizedCount = std::count_if(data.begin(), data.end()
		, [&network](const Data& data)->bool
	{
		const std::vector<double>& output = network.Work(data.GetInput());
		return data.IsRecognized(output);
	}
	);
	const double recognitionRatio = recognizedCount/static_cast<double>(data.size())*100.0;
	std::cout << "RecognitionRatio: " << recognitionRatio <<" %" << std::endl;
}

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	NeuralBasic::Network&& network = CreateNetwork();
	TrainNetwork(network);
	TestNetwork(network);

	return 0;
}

