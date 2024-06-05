#include "Point.h"
#include "ARI.h"
#include <iostream>

int userDefinedGroupCountInput() {
    int userDefinedGroupCount;
    do {
        std::cout << "Please enter the number of groups expected in the dataset: " << std::endl;
        std::cin >> userDefinedGroupCount;
    } while (userDefinedGroupCount <= 0);
    return userDefinedGroupCount;
}

bool canCalculateARI(std::vector<Point> points) {
    for (int i = 0; i < points.size(); i++) {
        if (points[i].group == -1) {
            //std::cout << "\nWarning: detection of an \"outlier\" point, so ARI cannot be calculated." << std::endl;
            return false;
        }
    }
    //std::cout << "\nAll points have been assigned to a group (no Outliers), so ARI can be calculated." << std::endl;
    return true;
}

bool isARIRequired() {
    std::string answer;
    do {
        std::cout << "Do you want to calculate the ARI to evaluate the clustering algorithm? (y/n)" << std::endl;
        std::cin >> answer;
    } while (answer != "y" && answer != "n");
    return answer == "y";
}

double calculateARI(std::vector<Point> points, int userDefinedGroupCount, int pointCount) {
    std::cout << "Calculating ARI..." << std::endl;

    std::vector<int> findGroupArray;
    std::vector<int> datasetGroupArray;

    for (int i = 0; i < pointCount; i++) {
        findGroupArray.push_back(points[i].group);
    }

    int groupIndex = 1;
    int groupSize = pointCount / userDefinedGroupCount;

    for (int i = 0; i < pointCount; i++) {
        datasetGroupArray.push_back(groupIndex);
        if ((i + 1) % groupSize == 0 && groupIndex < userDefinedGroupCount) {
            groupIndex++;
        }
    }

    // DEBUG : display the two arrays to compare the distribution
    // of group numbers (datasetGroupArray) expected and found (findGroupArray)
    /* std::cout << "DEBUG | Array with reference group numbers (expected numbers) datasetGroupArray: " << std::endl;
    for (int i = 0; i < datasetGroupArray.size(); i++) {
        std::cout << datasetGroupArray[i] << " ";
    }
    std::cout << "\nDEBUG | Array with found group numbers findGroupArray: " << std::endl;
    for (int i = 0; i < findGroupArray.size(); i++) {
        std::cout << findGroupArray[i] << " ";
    } */

    // Calculate ARI
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double d = 0.0;
    double comb = 1.0;

    for (int i = pointCount; i >= (pointCount - 2 + 1); i--) {
        comb *= i;
    }
    comb /= 2.0;

    for (int i = 0; i < pointCount - 1; i++) {
        for (int j = i + 1; j < pointCount; j++) {
            if (datasetGroupArray[i] != datasetGroupArray[j]) {
                if (findGroupArray[i] != findGroupArray[j]) {
                    d++;
                } else {
                    c++;
                }
            } else {
                if (findGroupArray[i] == findGroupArray[j]) {
                    a++;
                } else {
                    b++;
                }
            }
        }
    }

    double ARI;

    if (a * 2.0 == ((b + a) + (c + a))) {
        ARI = 1.0;
    } else {
        ARI = a - ((b + a) * (c + a)) / (comb * 1.0);
        ARI = ARI / ((((b + a) + (c + a)) / 2.0) - (((b + a) * (c + a)) / (comb * 1.0)));
    }
    //printf("hello %f", ARI);

    return ARI;
}