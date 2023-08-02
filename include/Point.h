#ifndef PHYDBSCAN_POINT_H
#define PHYDBSCAN_POINT_H

#include <vector>

/**
 * Enumeration representing the possible point types in the DBSCAN algorithm
 */
enum class PointType {
    UNDEFINED, /** Undefined point type */
    CORE, /** Core point */
    BORDER, /** Border point */
    OUTLIER /** Outlier point */
};

/**
 * Structure representing a point.
 */
struct Point {
    std::vector<double> distances; /** Distances to all other points */
    double x;
    double y;
    PointType type = PointType::UNDEFINED; /** Point type (UNDEFINED, CORE, BORDER, or OUTLIER) */
    int group = 0; /** Group to which the point belongs */
};

#endif // PHYDBSCAN_POINT_H