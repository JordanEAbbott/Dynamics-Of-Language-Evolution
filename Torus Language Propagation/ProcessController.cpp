#include "ProcessController.h"
#include "Language.h"

#include <vector>
#include <fstream>

std::vector<Language*> createDummyVector() {
    Language* dummyL = new Language{ true, {nullptr, nullptr, nullptr, nullptr}, -1 };
    return { dummyL, dummyL, dummyL, dummyL };
}

ProcessController::ProcessController(int size) {

    srand(time(NULL));
    std::vector<std::vector<Language>> languages(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Language* l = new Language{ ((double)rand() / (RAND_MAX)) > 0.5, createDummyVector(), size * i + j };
            languages[i].push_back(*l);
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            languages[i][j].neighbours[0] = &languages[(size + i - 1) % size][j];
            languages[i][j].neighbours[1] = &languages[i][(j + 1) % size];
            languages[i][j].neighbours[2] = &languages[(i + 1) % size][j];
            languages[i][j].neighbours[3] = &languages[i][(size + j - 1) % size];
        }
    }

    this->staticLanguages = languages;
    this->size = size;
}

ProcessController::~ProcessController() {

}

double ProcessController::calculateSigma() {

    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j = j + 2) {
            count = count + languages[i][j].neighbourDifferences();
        }
    }

    return (double)count / (2 * size * size);
}

void ProcessController::runProcess(int iterations) {

    languages = staticLanguages;
    std::vector<double> sigmaProcess;
    for (int i = 0; i < iterations; i++) {
        int pointId = rand() % (size * size);
        int neighbour = rand() % 4;
        int col = pointId % size;
        int row = (pointId - col) / size;  // (i * size) + j = pointid

        languages[row][col].feature = languages[row][col].neighbours[neighbour]->feature;

        if (i % (size * size) == 0) {
            sigmaProcess.push_back(calculateSigma());
        }
    }
    
    sigma.push_back(sigmaProcess);
}

std::vector<std::vector<double>> ProcessController::getSigma() {
    return sigma;
}

std::vector<double> ProcessController::getSigmaAt(int position) {
    return sigma[position];
}