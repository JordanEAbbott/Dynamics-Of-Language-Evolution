#pragma once
#include <vector>

struct Language {
	bool feature;
	std::vector<Language*> neighbours;

    double verticalIngress = 0.5;
    double verticalEgress = 0.5;

    double horizontalIngress = 0.5;
    double horizontalEgress = 0.5;

    double relativeRate = 0.5;

	int id;

    Language(bool feature, std::vector<Language*> neighbours, int id);
	int neighbourDifferences();
    void setRates(double vIngress, double vEgress, double hIngress, double hEgress, double rRate);
};

inline Language::Language(bool f, std::vector<Language*> neighbourPointers, int i) {
    feature = f;
    neighbours = neighbourPointers;
    id = i;
}

inline int Language::neighbourDifferences() {

    int count = 0;
    for (int neighbour = 0; neighbour < 4; neighbour++) {
        if (feature != neighbours[neighbour]->feature) {
            count++;
        }
    }
    return count;
}

inline void Language::setRates(double vIngress, double vEgress, double hIngress, double hEgress, double rRate) {

    verticalIngress = vIngress;
    verticalEgress = vEgress;

    horizontalIngress = hIngress;
    horizontalEgress = hEgress;

    relativeRate = rRate;
}