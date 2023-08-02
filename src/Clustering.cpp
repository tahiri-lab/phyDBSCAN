#include "Clustering.h"
#include <iostream>

void expandCluster(Point& point, int group, std::vector<Point>& points, double epsilon) {
    point.group = group;

    // Explore neighboring points
    for (size_t i = 0; i < points.size(); ++i) {
        double distance = point.distances[i];
        // If the point is a neighbor and not part of any group
        if (distance <= epsilon && points[i].group == 0) {
            points[i].group = group;
            // Expand the cluster to neighbors if they are core points
            if (points[i].type == PointType::CORE) {
                expandCluster(points[i], group, points, epsilon);
            }
        }
    }
}

void determineCoreAndGroup(std::vector<Point>& points, double epsilon, int minPoints) {
    int groupCounter = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        int nbNeighbours = 0;
        for (size_t j = 0; j < points.size(); ++j) {
            if (i == j) {
                continue;
            }
            double distance = points[i].distances[j];
            // Increment neighbor count if distance is less than or equal to epsilon
            if (distance <= epsilon) {
                ++nbNeighbours;
            }
        }
        // If neighbor count is greater than minPoints, the point is a core point
        if (nbNeighbours >= minPoints) {
            points[i].type = PointType::CORE;

            // If the point is not part of any group, expand the cluster
            if (points[i].group == 0) {
                ++groupCounter;
                expandCluster(points[i], groupCounter, points, epsilon);
            }
        }
    }
}

void determineBorderAndOutlier(std::vector<Point>& points, double epsilon) {
    for (size_t i = 0; i < points.size(); ++i) {
        if (points[i].type != PointType::CORE) {
            for (size_t j = 0; j < points.size(); ++j) {
                if (points[i].distances[j] <= epsilon && points[j].type == PointType::CORE) {
                    points[i].type = PointType::BORDER;
                    points[i].group = points[j].group;
                    break;
                }
            }
            if (points[i].type != PointType::BORDER) {
                points[i].type = PointType::OUTLIER;
                points[i].group = -1;
            }
        }
    }
}

void printResults(const std::vector<Point>& points) {
    std::cout << "Number of groups: " << points[points.size() - 1].group << '\n';
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << "Point " << i + 1 << ": Group " << (points[i].group == -1 ? "N/A" : std::to_string(points[i].group));
        switch (points[i].type) {
            case PointType::CORE:
                std::cout << ", Core";
                break;
            case PointType::BORDER:
                std::cout << ", Border";
                break;
            case PointType::OUTLIER:
                std::cout << ", Outlier";
                break;
        }
        std::cout << '\n';
    }
}