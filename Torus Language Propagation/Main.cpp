#include "Language.h"
#include "ProcessController.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<double> averageSigma(std::vector<std::vector<double>> sigma) {

    int length = sigma[0].size();
    int realisations = sigma.size();

    std::vector<double> averagedSigma(length);
    for (int i = 0; i < length; i++) { // Can't think of a nice name for i
        double averageSigma = 0;
        for (int process = 0; process < realisations; process++) {
            averageSigma = averageSigma + sigma[process][i];
        }
        averagedSigma[i] = (averageSigma / realisations);
    }

    return averagedSigma;
}

void outputSigma(std::vector<double> sigma, std::string name) {

    int length = sigma.size();
    std::ofstream sigmaFilestream;

    sigmaFilestream.open(name + ".csv");
    for (int i = 0; i < length; i++) {
        sigmaFilestream << i << "," << sigma[i] << std::endl;
    }
    sigmaFilestream.close();
}

int main()
{

    int realisations = 100;
    ProcessController* PC = new ProcessController(100);
    
    for (int i = 0; i < realisations; i++) {
        PC->runProcess(1000000);
        std::cout << "Finished Process " << i << std::endl;
    }

    std::vector<double> averagedSigma = averageSigma(PC->getSigma());

    outputSigma(averagedSigma, "averageSigma");

    outputSigma(PC->getSigmaAt(0), "sampleSigma1");
    outputSigma(PC->getSigmaAt(1), "sampleSigma2");
    outputSigma(PC->getSigmaAt(2), "sampleSigma3");
    outputSigma(PC->getSigmaAt(3), "sampleSigma4");
    outputSigma(PC->getSigmaAt(4), "sampleSigma5");
}