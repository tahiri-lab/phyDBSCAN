#ifndef PHYDBSCAN_ARI_H
#define PHYDBSCAN_ARI_H

/**
 * @brief Get the number of groups expected in the dataset
 *
 * This function prompts the user to input the number of groups they expect
 *
 * @return The user-defined group count
 */
int userDefinedGroupCountInput();

/**
 * @brief Check if ARI calculation is possible
 *
 * This function checks if ARI calculation is possible by examining whether any points in the dataset are marked as outliers (group = -1)
 *
 * @param points Vector of Point objects representing the dataset
 * @return True if ARI calculation is possible, false otherwise
 */
bool canCalculateARI(std::vector<Point> points);

/**
 * @brief Check if ARI calculation is required by the user
 *
 * This function asks the user if they want to calculate the ARI
 *
 * @return True if ARI calculation is required, false otherwise
 */
bool isARIRequired();

/**
 * @brief Calculate Adjusted Rand Index (ARI).
 *
 * This function calculates the Adjusted Rand Index (ARI) based on the provided parameters.
 * ARI permits to evaluate the quality of a clustering algorithm by comparing the groups found by the algorithm.
 * If the ARI is close to 1, the groups found by the algorithm are similar to the expected groups, it means the algorithm is good.
 * If the ARI is close to 0, the groups found by the algorithm are not similar to the expected groups.
 *
 * @param points Vector of Point objects representing the dataset.
 * @param userDefinedGroupCount Number of groups expected in the dataset.
 * @param foundGroupCount Number of groups found by the clustering algorithm.
 * @param pointCount Total number of points in the dataset, defined by the user.
 * @return The calculated ARI score.
 */
double calculateARI(std::vector<Point> points, int userDefinedGroupCount, int pointCount);

#endif //PHYDBSCAN_ARI_H