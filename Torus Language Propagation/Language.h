#pragma once
#include <vector>

struct Feature {

    double verticalIngress = 0.5;
    double verticalEgress = 0.5;

    double horizontalIngress = 0.5;
    double horizontalEgress = 0.5;

    double relativeRate = 0.5;

    void setRates(double vIngress, double vEgress, double hIngress, double hEgress, double rRate);
};

struct Language {

	bool featureActive;
    Feature* feature;
	std::vector<Language*> neighbours;

	int id;

    Language(bool featureActive, Feature* feature, std::vector<Language*> neighbours, int id);
	int neighbourDifferences();
};

inline Language::Language(bool fActive, Feature* f, std::vector<Language*> neighbourPointers, int i) {
    featureActive = fActive;
    feature = f;
    neighbours = neighbourPointers;
    id = i;
}

inline int Language::neighbourDifferences() {

    int count = 0;
    for (int neighbour = 0; neighbour < 4; neighbour++) {
        if (featureActive != neighbours[neighbour]->featureActive) {
            count++;
        }
    }
    return count;
}

inline void Feature::setRates(double vIngress, double vEgress, double hIngress, double hEgress, double rRate) {

    verticalIngress = vIngress;
    verticalEgress = vEgress;

    horizontalIngress = hIngress;
    horizontalEgress = hEgress;

    relativeRate = rRate;
}