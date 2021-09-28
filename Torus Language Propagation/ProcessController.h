#pragma once
#include "Language.h"
#include <vector>

class ProcessController {

public:
	ProcessController(int size);

	void runProcess(int iterations);
	double calculateSigma();
	std::vector<std::vector<double>> getSigma();
	std::vector<double> getSigmaAt(int position);

private:
	~ProcessController();

	std::vector<std::vector<Language>> staticLanguages;
	std::vector<std::vector<Language>> languages;
	std::vector<std::vector<double>> sigma;

	int size;
};