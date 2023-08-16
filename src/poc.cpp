#include "Clustering.h"
#include "FileIO.h"
#include "HyperparametersCalculator.h"
#include "ARI.h"
#include <iostream>

int main() {
    std::vector<Point> points;
    int userDefinedGroupCount = 4; // @TODO à faire en input si l'utilisateur veut calculer l'ARI

    std::cout << "\n==== DBSCAN Clustering Algorithm ====\n" << std::endl;
    readInputFile("resources/input_data.txt", points);

    double bestEpsilon = findBestEpsilon(points);
    std::cout << "Best epsilon: " << bestEpsilon << std::endl;

    int bestMinPoints = findBestMinPoints(points, bestEpsilon);
    std::cout << "Best minPoints: " << bestMinPoints << std::endl;

    determineCoreAndGroup(points, bestEpsilon, bestMinPoints);
    determineBorderAndOutlier(points, bestEpsilon);

    printResults(points);

    if (canCalculateARI(points)) {
        if (isARIRequired()) {
            double ARI = calculateARI(points, userDefinedGroupCount,points[points.size() - 1].group, points.size());
            std::cout << "\nCalculate ARI: " << ARI << std::endl;
        }
    }

    return 0;
}
