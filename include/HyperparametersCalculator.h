#ifndef HYPERPARAMETERSCALCULATOR_H
#define HYPERPARAMETERSCALCULATOR_H

#include <vector>
#include <iostream>
#include "Point.h"

/**
 * @brief Calculates the best epsilon value for DBSCAN clustering algorithm
 *
 * This function calculates the best epsilon value for the DBSCAN clustering algorithm
 * using the provided distances between points. It measures the average maximum difference between
 * sorted distances for each point. The calculated epsilon can be used as a parameter
 * for DBSCAN algorithm to define the maximum distance between points in the same cluster
 *
 * @param points A vector of Point objects representing the data points
 * @return The calculated best epsilon value
 */
double findBestEpsilon(const std::vector<Point>& points);

/**
 * @brief Calculates the best minPoints value for DBSCAN clustering algorithm
 *
 * This function calculates the best minPoints value for the DBSCAN clustering algorithm
 * using the provided distances between points and a pre-calculated epsilon value. It measures the average
 * density of points within epsilon distance for each point. The calculated minPoints can be
 * used as a parameter for the DBSCAN algorithm to define the minimum number of points required
 * to form a dense region
 *
 * @param points A vector of Point objects representing the data points.
 * @param epsilon The epsilon value used to define the maximum distance for points in the same cluster
 * @return The calculated best minPoints value
 */
int findBestMinPoints(const std::vector<Point>& points, double epsilon);

#endif // HYPERPARAMETERSCALCULATOR_H
