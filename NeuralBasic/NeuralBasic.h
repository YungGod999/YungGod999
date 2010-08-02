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

// This class is exported from the NeuralBasic.dll
class NEURALBASIC_API CNeuralBasic {
public:
	CNeuralBasic(void);
	// TODO: add your methods here.
};

extern NEURALBASIC_API int nNeuralBasic;

NEURALBASIC_API int fnNeuralBasic(void);
