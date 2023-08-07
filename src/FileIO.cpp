#include "FileIO.h"

void readInputFile(const std::string& fileName, std::vector<Point>& points) {
    std::cout << "Reading input data..." << std::endl;
    std::ifstream inputFile(fileName);
    std::string line;

    while (getline(inputFile, line)) {
        std::istringstream lineStream(line);
        Point point;
        double distance;

        while (lineStream >> distance) {
            point.distances.push_back(distance);
        }

        points.push_back(point);
    }
}