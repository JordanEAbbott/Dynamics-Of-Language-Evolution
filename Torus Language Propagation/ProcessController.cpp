#include "ProcessController.h"
#include "Language.h"

#include <vector>
#include <fstream>

std::vector<Language*> createDummyVector() {
    Language* dummyL = new Language( true, nullptr, {nullptr, nullptr, nullptr, nullptr}, -1 );
    return { dummyL, dummyL, dummyL, dummyL };
}

ProcessController::ProcessController(int size) {

    srand(time(NULL));
    features.push_back(new Feature());
    languages.resize(size);
    this->size = size;
}

ProcessController::~ProcessController() {

}

double ProcessController::calculateSigma() {

    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j = j + 2) {
            count = count + languages[i][j]->neighbourDifferences();
        }
    }

    return (double)count / (2 * size * size);
}

double ProcessController::featureFrequency() {

    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            count = count + languages[i][j]->featureActive;
        }
    }
    
    return (double)count / (size * size);
}

void ProcessController::initialiseGrid() {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Language* l = new Language(((double)rand() / (RAND_MAX)) > 0.5, features[0], createDummyVector(), size * i + j);
            languages[i].push_back(l);
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            languages[i][j]->neighbours[0] = languages[(size + i - 1) % size][j];
            languages[i][j]->neighbours[1] = languages[i][(j + 1) % size];
            languages[i][j]->neighbours[2] = languages[(i + 1) % size][j];
            languages[i][j]->neighbours[3] = languages[i][(size + j - 1) % size];
        }
    }
}

void ProcessController::verticalEvent(Language* language) {
    
    double rnd = (double)rand() / RAND_MAX;
    if (language->featureActive && rnd < language->feature->verticalEgress) {
        language->featureActive ^= 1;
    }
    else if (!language->featureActive && rnd < language->feature->verticalIngress) {
        language->featureActive ^= 1;
    }
}

void ProcessController::horizontalEvent(Language* language) {

    Language* neighbour = language->neighbours[rand() % 4];
    double rnd = (double)rand() / RAND_MAX;

    if (neighbour->featureActive) {
        language->featureActive = (rnd > language->feature->horizontalEgress);
    }
    else {
        language->featureActive = !(rnd > language->feature->horizontalIngress);
    }
}

void ProcessController::runProcess(int iterations) {

    resetGrid();
    std::vector<double> sigmaProcess;
    for (int i = 0; i < iterations; i++) {

        int pointId = rand() % (size * size);
        int col = pointId % size;
        int row = (pointId - col) / size; // (i * size) + j = pointId
        double rnd = (double)rand() / RAND_MAX;

        // Language* chosenLanguage = languages[row][col];

        if (rnd > languages[row][col]->feature->relativeRate) {
            verticalEvent(languages[row][col]);
        }
        else {
            horizontalEvent(languages[row][col]);
        }

        if (i % (size * size) == 0) {
            sigmaProcess.push_back(calculateSigma());
        }
    }

    sigma.push_back(sigmaProcess);
    finalSigma.push_back(sigmaProcess.back());
    fFrequency.push_back(this->featureFrequency());
    fTemperature.push_back(features[0]->temperature);
}

void ProcessController::clearVectors() {
    sigma.clear();
    finalSigma.clear();
    fFrequency.clear();
    fTemperature.clear();
}

std::vector<std::vector<double>> ProcessController::getSigma() {
    return sigma;
}

std::vector<Feature*> ProcessController::getFeatures() {
    return features;
}

std::vector<double> ProcessController::getFrequency() {
    return fFrequency;
}

std::vector<double> ProcessController::getTemperature() {
    return fTemperature;
}

std::vector<double> ProcessController::getFinalSigma() {
    return finalSigma;
}

std::vector<double> ProcessController::getSigmaAt(int position) {
    return sigma[position];
}

void ProcessController::resetGrid() {
    languages.clear();
    languages.resize(size);
    initialiseGrid();
}