#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */

std::vector<double> averageVector(std::vector<std::vector<double>> vector) {

    int length = vector[0].size();
    int realisations = vector.size();

    std::vector<double> averagedVector(length);
    for (int i = 0; i < length; i++) { // Can't think of a nice name for i
        double averageVector = 0;
        for (int process = 0; process < realisations; process++) {
            averageVector = averageVector + vector[process][i];
        }
        averagedVector[i] = (averageVector / realisations);
    }

    return averagedVector;
}

void outputVector(std::vector<double> vector, std::string fileName) {

    int length = vector.size();
    std::ofstream sigmaFilestream;

    sigmaFilestream.open(fileName + ".csv");
    for (int i = 0; i < length; i++) {
        sigmaFilestream << i << "," << vector[i] << std::endl;
    }
    sigmaFilestream.close();
}

double ellipticalIntegralFirstKind(std::vector<double> z, double u, double v) {

    return 1 / (2 * M_PI) * 1 / (1 - (z[0] / 2) * (cos(u) + cos(v)));
}

double integrateSimpsons2D(double f(std::vector<double> p, double u, double v), double a, double b, double c, double d, std::vector<double> p) {

    double sum = 16 * f(p, (a + b) / 2, (c + d) / 2) + 4 * f(p, (a + b) / 2, d) + 4 * f(p, (a + b) / 2, c) + 4 * f(p, b, (c + d) / 2) + f(p, b, d) + f(p, b, c) + 4 * f(p, a, (c + d) / 2) + f(p, a, d) + f(p, a, c);
    return sum * ((b - a) * (d - c)) / 36;
}