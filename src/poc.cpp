#include "Clustering.h"
#include "FileIO.h"
#include <iostream>

int main() {
    std::vector<Point> points;
    const double epsilon = 0.5;
    const int minPoints = 3;

    std::cout << "==== DBSCAN Clustering Algorithm ====" << std::endl;
    readInputFile("resources/input_data.txt", points);
    determineCoreAndGroup(points, epsilon, minPoints);
    determineBorderAndOutlier(points, epsilon);
    printResults(points);

    return 0;
}