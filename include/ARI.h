#ifndef PHYDBSCAN_ARI_H
#define PHYDBSCAN_ARI_H

bool canCalculateARI(std::vector<Point> vector);

bool isARIRequired();

double calculateARI(std::vector<Point> points, int userDefinedGroupCount, int foundGroupCount, int pointCount);

#endif //PHYDBSCAN_ARI_H