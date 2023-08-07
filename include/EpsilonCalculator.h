#ifndef EPSILONCALCULATOR_H
#define EPSILONCALCULATOR_H

#include <vector>
#include <iostream>
#include "Point.h"

/**
 * @brief Calculates the best epsilon value for DBSCAN clustering algorithm
 *
 * This function calculates the best epsilon value for the DBSCAN clustering algorithm
 * using the provided distances between points. It measures the average maximum difference between
 * sorted distances for each point. The calculated epsilon can be used as a parameter
 * for DBSCAN algorithm to define the maximum distance between points in the same cluster.
 *
 * @param points A vector of Point objects representing the data points.
 * @return The calculated best epsilon value.
 */
double findBestEpsilon(const std::vector<Point>& points);

#endif // EPSILONCALCULATOR_H
