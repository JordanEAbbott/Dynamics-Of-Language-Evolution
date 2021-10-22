#include "Language.h"
#include "ProcessController.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

std::vector<std::vector<double>> generateValues(double temperature) {

    double step = temperature / 10;
    std::vector<std::vector<double>> values(10);
    for (int i = 1; i <= 10; i++) {
        double p_i = i * step;
        double p_e = temperature - p_i;
        values[i - 1] = { p_i, p_e };
    }

    return values;
}

int main()
{
    // 0.5756

    int realisations = 5;
    ProcessController* PC = new ProcessController(50, 2);

    std::vector<std::vector<double>> v = generateValues(0.1);
    PC->getFeatures()[0]->setRates(v[5][0], v[5][1], 0, 0, 0.5);
    PC->runProcess(1000000);
    std::cout << "Finished Process" << std::endl;
    std::cout << PC->getFrequency().back();
    PC->outputFeatures();
    PC->clearVectors();

    // Output sigma graphs
    /*
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