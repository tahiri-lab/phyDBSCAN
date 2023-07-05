#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../include/poc.h"

std::vector<Point> points;

void generateOutputFile(const char *string);

const double epsilon = 0.5;  // Distance maximale pour qu'un point soit considéré comme voisin
const int minPoints = 3;  // Nombre minimum de points pour constituer un groupe

void readInputFile(const std::string& fileName) {
    std::ifstream inputFile(fileName);  // Ouvrir le fichier en lecture
    std::string line;

    // Lire chaque ligne du fichier
    while (getline(inputFile, line)) {
        std::istringstream lineStream(line);
        Point point;
        double distance;

        // Pour chaque distance dans la ligne, ajouter à la liste des distances du point
        while (lineStream >> distance) {
            point.distances.push_back(distance);
        }

        // Ajouter le point à la liste des points
        points.push_back(point);
    }
}

void expandCluster(Point& point, int group) {
    point.group = group;  // Assigner le groupe au point

    // Parcourir les points voisins
    for (size_t i = 0; i < points.size(); ++i) {
        double distance = point.distances[i];

        // Si le point est un voisin et n'appartient à aucun groupe
        if (distance <= epsilon && points[i].group == 0) {
            points[i].group = group;  // Assigner le groupe aux voisins

            // Étendre le cluster aux voisins s'ils sont des points centraux
            if (points[i].type == PointType::CORE) {
                expandCluster(points[i], group);
            }
        }
    }
}

int determineCoreAndGroup() {
    int groupCounter = 0;  // Compteur pour les groupes

    // Pour chaque point
    for (size_t i = 0; i < points.size(); ++i) {
        int nbElements = 0;  // Compteur du nombre de voisins

        // Pour chaque autre point
        for (size_t j = 0; j < points.size(); ++j) {
            if (i == j) {
                continue;
            }

            double distance = points[i].distances[j];

            // Si la distance est inférieure ou égale à epsilon, incrémenter le compteur de voisins
            if (distance <= epsilon) {
                ++nbElements;
            }
        }

        // Si le nombre de voisins est supérieur à minPoints, alors le point est un point Core
        if (nbElements >= minPoints) {
            points[i].type = PointType::CORE;

            // Si le point n'appartient à aucun groupe, étendre le cluster
            if (points[i].group == 0) {
                ++groupCounter;
                expandCluster(points[i], groupCounter);
            }
        }
    }
    return groupCounter;
}

void determineBorderAndOutlier() {
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

void printResults(int groupCounter) {
    std::cout << "Nombre de groupes: " << groupCounter << '\n';
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << "Point " << i + 1 << ": groupe " << (points[i].group == -1 ? "N/A" : std::to_string(points[i].group));
        switch (points[i].type) {
            case PointType::CORE:
                std::cout << ", core";
                break;
            case PointType::BORDER:
                std::cout << ", border";
                break;
            case PointType::OUTLIER:
                std::cout << ", outlier";
                break;
        }
        std::cout << '\n';
    }
}

void generateOutputFile(const char *string) {
    std::ofstream outputFile(string);

    outputFile << "Point,";
    for (size_t i = 0; i < points.size(); ++i) {
        outputFile << "Point " << i + 1 << ',';
    }
    outputFile << '\n';

    for (size_t i = 0; i < points.size(); ++i) {
        outputFile << "Point " << i + 1;
        for (size_t j = 0; j < points.size(); ++j) {
            outputFile << ',' << points[i].distances[j];
        }
        outputFile << '\n';
    }

}

int main() {
    readInputFile("resources/input_data.txt");
    int groupCounter = determineCoreAndGroup();
    determineBorderAndOutlier();
    printResults(groupCounter);
    generateOutputFile("resources/output_data.csv");
    return 0;
}