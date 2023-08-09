#include "Clustering.h"
#include "FileIO.h"
#include "HyperparametersCalculator.h"
#include <iostream>

int main() {
    std::vector<Point> points;

    std::cout << "\n==== DBSCAN Clustering Algorithm ====\n" << std::endl;
    readInputFile("resources/input_data.txt", points);

    double bestEpsilon = findBestEpsilon(points);
    std::cout << "Best epsilon: " << bestEpsilon << std::endl;

    int bestMinPoints = findBestMinPoints(points, bestEpsilon);
    std::cout << "Best minPoints: " << bestMinPoints << std::endl;

    determineCoreAndGroup(points, bestEpsilon, bestMinPoints);
    determineBorderAndOutlier(points, bestEpsilon);
    printResults(points);
    return 0;
}
