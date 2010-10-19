// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

NeuralBasic::Network CreateNetwork()
{
	std::vector<size_t> networkSize;
	networkSize.push_back(2);//inputs count
	networkSize.push_back(2);//neurons count in layer 1
	networkSize.push_back(1);//neurons count in layer 2 and and outputs count
	NeuralBasic::Network network(networkSize);
	return network;
}

class Data
{
public:
	Data(const std::vector<double>& input, const std::vector<double>& desired)
		: m_input(input)
		, m_desired(desired)
	{
	}

	const std::vector<double>& GetInput() const
	{
		return m_input;
	}

	const std::vector<double>& GetDesired() const
	{
		return m_desired;
	}

	bool IsRecognized(const std::vector<double>& networkOutput) const
	{
		std::vector<double> errors;
		return std::equal(m_desired.begin(), m_desired.end()
			, networkOutput.begin()
			, 
			[](double desired, double output)->bool
		{
			//IsErrorSmallerThen
			if(abs(desired-output)<0.3)
				return true;
			return false;
		}
		);
	}
private:
	std::vector<double> m_input;
	std::vector<double> m_desired;
};

const double inputs[][5]={
	  {0.0, 0.0, 1.0}
	, {1.0, 0.0, 1.0}
	, {0.0, 1.0, 1.0}
	, {1.0, 1.0, 1.0}
};

const double desireds[][4]={
	  {0.0}
	, {1.0}
	, {1.0}
	, {0.0}
};


Data CreateData(const size_t index)
{
	Data data(std::vector<double>(inputs[index], inputs[index]+3)
		, std::vector<double>(desireds[index], desireds[index]+1));
	return data;
}

std::vector<Data> GetTestData()
{
	std::vector<Data> data;
	for(size_t idx=0; idx<4; ++idx)
		data.push_back(CreateData(idx));

	return data;
}

std::vector<Data> GetTrainData()
{
	std::vector<Data> data;
	for(size_t idx=0; idx<4; ++idx)
		data.push_back(CreateData(idx));

	return data;
}

double GetMaxAbs(const std::vector<double>& errors)
{
	double result = 0;
	std::for_each(errors.begin(), errors.end()
		, [&result](const double error)
	{
		result = std::max(result, abs(error));
	}
	);
	return result;
}

void TrainNetwork(NeuralBasic::Network& network)
{
	std::cout << "Training neural network..." << std::endl;
	const std::vector<Data>& trainData = GetTrainData();

	const size_t trainRoundCount = 10000;
	for(size_t idx=0; idx<trainRoundCount; ++idx)
	{
		double roundError = 0;
		std::for_each(trainData.begin(), trainData.end() 
			, [&network, &roundError](const Data& data)
		{
			const std::vector<double>& input = data.GetInput();
			const std::vector<double>& desired = data.GetDesired();
			const std::vector<double>& output = network.Work(input);
			std::vector<double> error;
			//error = desired-output
			std::transform(desired.begin(), desired.end()
				, output.begin()
				, std::back_inserter(error)
				, std::minus<double>());
			network.Train(input, error);
			roundError = std::max(roundError, GetMaxAbs(error));
		}
		);
		if(idx%10==0)
			std::cout << "Round error("<<idx<< ": "<< roundError << std::endl;
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

	std::cout << "Press <Enter> key to continue...";
	std::cin.ignore();
	return 0;
}

