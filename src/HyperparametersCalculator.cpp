#include "HyperparametersCalculator.h"
#include <algorithm>

double findBestEpsilon(const std::vector<Point>& points) {
    std::cout << "Calculating best epsilon...\t";
    std::vector<std::vector<double>> distanceArray;
    for (const Point& point : points) {
        distanceArray.push_back(point.distances);
    }

    std::vector<double> numBeforeIncreaseList;
    for (const std::vector<double>& distances : distanceArray) {
        std::vector<double> sortedDistances = distances;
        std::sort(sortedDistances.begin(), sortedDistances.end());

        double maxDiff = 0.0;
        double numBeforeIncrease = 0.0;
        // We start at 2 because we don't want to compare the point with itself (the first element of the array)
        for (size_t i = 2; i < sortedDistances.size(); ++i) {
                double diff = sortedDistances[i] - sortedDistances[i - 1];
                // Check if the difference is larger than the previous maximum and if the previous distance is 0
                // If the previous distance is 0, it means that we use an average to avoid distorting the search for the epsilon
                if (diff > maxDiff && sortedDistances[i - 1] == 0) {
                    maxDiff = diff;
                    numBeforeIncrease = (sortedDistances[i] + sortedDistances[i - 1]) / 2;
                }
                // Check if the difference is larger than the previous maximum and if the previous distance is not 0
                else if (diff > maxDiff) {
                    maxDiff = diff;
                    numBeforeIncrease = sortedDistances[i - 1];
                }
        }
        numBeforeIncreaseList.push_back(numBeforeIncrease);
    }

    double totalNumBeforeIncrease = 0.0;
    for (double numBeforeIncrease : numBeforeIncreaseList) {
        totalNumBeforeIncrease += numBeforeIncrease;
    }

    return totalNumBeforeIncrease / numBeforeIncreaseList.size();
}

int findBestMinPoints(const std::vector<Point>& points, double epsilon) {
    std::cout << "Calculating best minPoints... \t";
    std::vector<int> minPoints;
    for (const Point& point : points) {
        int count = 0;
        for (double distance : point.distances) {
            if (distance <= epsilon) {
                ++count;
            }
        }
        minPoints.push_back(count);
    }

    int totalMinPoints = 0.0;
    for (int count : minPoints) {
        totalMinPoints += count;
    }

    //printf("\n OKay j'ai besoins d'aide pour les minPoints donc on a %d Total et %ld taille de liste", totalMinPoints, minPoints.size());
    return totalMinPoints / minPoints.size();
}