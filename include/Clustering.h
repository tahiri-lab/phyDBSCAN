#ifndef PHYDBSCAN_CLUSTERING_H
#define PHYDBSCAN_CLUSTERING_H

#include <vector>
#include <iostream>
#include "Point.h"

/**
 * Expands a cluster from a core point
 *
 * @param point The core point from which to expand the cluster
 * @param group The group to which the core point belongs
 */
void expandCluster(Point& point, int group, std::vector<Point>& points, double epsilon);

/**
 * Traverses the points to find "Core" points and determine their groups
 *
 * @param points The vector of points to be traversed
 * @param epsilon The maximum distance between two points for one to be considered as in the neighborhood of the other
 * @param minPoints The minimum number of points to form a region with a core point
 *
 */
void determineCoreAndGroup(std::vector<Point>& points, double epsilon, int minPoints);

/**
 * Determines the Border and Outlier point types
 *
 * @param points The vector of points to be traversed
 * @param epsilon The maximum distance between two points for one to be considered as in the neighborhood of the other
 */
void determineBorderAndOutlier(std::vector<Point>& points, double epsilon);

/**
 * Displays the groups and point types after
 *
 * @param points The vector of points to be displayed
 */
void printResults(const std::vector<Point>& points);

#endif //PHYDBSCAN_CLUSTERING_H