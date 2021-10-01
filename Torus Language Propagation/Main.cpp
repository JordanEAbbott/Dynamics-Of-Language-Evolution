#include "Language.h"
#include "ProcessController.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{

    int realisations = 100;
    ProcessController* PC = new ProcessController(100);

    for (int i = 0; i < realisations; i++) {
        PC->runProcess(1000000);
        std::cout << "Finished Process " << i << std::endl;
    }

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
}