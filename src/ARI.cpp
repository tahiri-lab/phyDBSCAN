#include "Point.h"
#include "ARI.h"
#include <iostream>

bool canCalculateARI(std::vector<Point> points) {
    for (int i = 0; i < points.size(); i++) {
        if (points[i].group == -1) {
            std::cout << "Attention : détection de point \"outlier\", l'ARI ne pourra donc pas être calculée." << std::endl;
            return false;
        }
    }
    std::cout << "Tous les points ont été affectés à un groupe (pas d'Outlier), l'ARI peut donc être calculée." << std::endl;
    return true;
}

bool isARIRequired() {
    std::string answer;
    do {
        std::cout << "Do you want to calculate the ARI ? (y/n)" << std::endl;
        std::cin >> answer;
    } while (answer != "y" && answer != "n");
    return answer == "y";
}

double calculateARI(std::vector<Point> points, int userDefinedGroupCount, int foundGroupCount, int pointCount) {
    std::cout << "\nCalculating ARI..." << std::endl;
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

    // DEBUG
    std::cout << "\nTableau avec les numéros des groupes de référence datasetGroupArray: " << std::endl;
    for (int i = 0; i < datasetGroupArray.size(); i++) {
        std::cout << datasetGroupArray[i] << " ";
    }
    std::cout << "\nTableau avec les numéros des groupes trouvés findGroupArray: " << std::endl;
    for (int i = 0; i < findGroupArray.size(); i++) {
        std::cout << findGroupArray[i] << " ";
    }

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

    double ARI = 0.0;

    if (a * 2.0 == ((b + a) + (c + a))) {
        ARI = 1.0;
    } else {
        ARI = a - ((b + a) * (c + a)) / (comb * 1.0);
        ARI = ARI / ((((b + a) + (c + a)) / 2.0) - (((b + a) * (c + a)) / (comb * 1.0)));
    }

    std::cout << "\n\nARI Score (Adjusted Rand Index, better if close to 1): " << ARI << std::endl;

    return ARI;
}