#include "EpsilonCalculator.h"
#include <algorithm>

double findBestEpsilon(const std::vector<Point>& points) {
    std::cout << "Calculating best epsilon..." << std::endl;
    std::vector<std::vector<double>> distanceArray;
    for (const Point& point : points) {
        distanceArray.push_back(point.distances);
    }

    std::vector<double> maxDiffs;
    for (const std::vector<double>& distances : distanceArray) {
        std::vector<double> sortedDistances = distances;
        std::sort(sortedDistances.begin(), sortedDistances.end());

        double maxDiff = 0.0;
        for (size_t i = 1; i < sortedDistances.size(); ++i) {
            double diff = sortedDistances[i] - sortedDistances[i - 1];
            if (diff > maxDiff) {
                maxDiff = diff;
            }
        }

        maxDiffs.push_back(maxDiff);
    }

    double totalMaxDiff = 0.0;
    for (double diff : maxDiffs) {
        totalMaxDiff += diff;
    }

    return totalMaxDiff / maxDiffs.size();
}
