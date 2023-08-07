#include "Clustering.h"
#include "FileIO.h"
#include "EpsilonCalculator.h"
#include <iostream>

int main() {
    std::vector<Point> points;
    // Default values for epsilon and minPoints
    const double epsilon = 0.5;
    const int minPoints = 3;

    std::cout << "\n==== DBSCAN Clustering Algorithm ====\n" << std::endl;
    readInputFile("resources/input_data.txt", points);
    double bestEpsilon = findBestEpsilon(points);
    std::cout << "Best epsilon: " << bestEpsilon << std::endl;
    determineCoreAndGroup(points, bestEpsilon, minPoints);
    determineBorderAndOutlier(points, bestEpsilon);
    printResults(points);
    return 0;
}
