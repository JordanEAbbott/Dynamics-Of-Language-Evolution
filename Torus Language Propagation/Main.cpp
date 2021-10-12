#include "Language.h"
#include "ProcessController.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<double>> generateValues(double temperature) {

    double step = temperature / 10;
    std::vector<std::vector<double>> values(10);
    for (int i = 0; i < 10; i++) {
        double p_i = i * step;
        double p_e = temperature - p_i;
        values[i] = { p_i, p_e };
    }

    return values;
}

int main()
{

    int realisations = 5;
    ProcessController* PC = new ProcessController(100);

    std::vector<std::vector<double>> v = generateValues(0.1);
    std::vector<double> fSigma(10);
    std::vector<double> fFreq(10);
    for (int j = 0; j < 10; j++) {
        PC->getFeatures()[0]->setRates(v[j][0], v[j][1], 0, 0, 0.5);
        for (int i = 0; i < realisations; i++) {
            PC->runProcess(10000000);
            std::cout << "Finished Process " << j*5 + i << std::endl;
        }
        fSigma[j] = averageVector(PC->getSigma()).back();
        fFreq[j] = PC->getFrequency().back();
        std::cout << averageVector(PC->getSigma()).back() << std::endl;
        std::cout << PC->getFrequency().back() << std::endl;
    }

    outputVector({ fSigma, fFreq, PC->getTemperature() }, "isogloss");
    /*
    // Output sigma graphs
    std::vector<double> averagedSigma = averageVector(PC->getSigma());

    outputVector({ averagedSigma }, "averageSigma");

    outputVector({ PC->getSigmaAt(0) }, "sampleSigma1");
    outputVector({ PC->getSigmaAt(1) }, "sampleSigma2");
    outputVector({ PC->getSigmaAt(2) }, "sampleSigma3");
    outputVector({ PC->getSigmaAt(3) }, "sampleSigma4");
    outputVector({ PC->getSigmaAt(4) }, "sampleSigma5");

    // Output isogloss graphs

    outputVector({ PC->getFinalSigma(), PC->getFrequency(), PC->getTemperature() }, "isogloss");
    */
}