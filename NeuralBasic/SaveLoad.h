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
namespace NeuralBasic
{
	class Network;
	NEURALBASIC_API void Save(const Network& network, const wchar_t* fileName);
	NEURALBASIC_API void Load(Network& network, const wchar_t* fileName);
}