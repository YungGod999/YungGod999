// NeuralBasic.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NeuralBasic.h"


// This is an example of an exported variable
NEURALBASIC_API int nNeuralBasic=0;

// This is an example of an exported function.
NEURALBASIC_API int fnNeuralBasic(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see NeuralBasic.h for the class definition
CNeuralBasic::CNeuralBasic()
{
	return;
}
