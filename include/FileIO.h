#ifndef PHYDBSCAN_FILEIO_H
#define PHYDBSCAN_FILEIO_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Point.h"

/**
 * Reads the input file containing the data matrix and initializes the points
 *
 * @param fileName The name of the input file
 * @param points The vector of points to be initialized
 */
void readInputFile(const std::string& fileName, std::vector<Point>& points);

#endif //PHYDBSCAN_FILEIO_H