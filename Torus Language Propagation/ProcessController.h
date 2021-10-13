#pragma once
#include "Language.h"
#include <vector>

class ProcessController {

public:
	ProcessController(int size);

	void runProcess(int iterations);
	void clearVectors();
	double calculateSigma();
	std::vector<std::vector<double>> getSigma();
	std::vector<Feature*> getFeatures();
	std::vector<double> getFrequency();
	std::vector<double> getTemperature();
	std::vector<double> getFinalSigma();
	std::vector<double> getSigmaAt(int position);

private:
	~ProcessController();

	void verticalEvent(Language* language);
	void horizontalEvent(Language* language);
	void resetGrid();
	void initialiseGrid();

	double featureFrequency();

	std::vector<std::vector<Language*>> languages;
	std::vector<std::vector<double>> sigma;
	std::vector<Feature*> features;
	std::vector<double> finalSigma;
	std::vector<double> fFrequency;
	std::vector<double> fTemperature;

	int size;
};