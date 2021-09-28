#pragma once
#include <vector>

struct Language {
	bool feature;
	std::vector<Language*> neighbours;
	int id;

	int neighbourDifferences();
};

inline int Language::neighbourDifferences() {

    int count = 0;
    for (int neighbour = 0; neighbour < 4; neighbour++) {
        if (feature != neighbours[neighbour]->feature) {
            count++;
        }
    }
    return count;
}