#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../include/poc.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

std::vector<Point> points;

const double epsilon = 0.5;  // Distance maximale pour qu'un point soit considéré comme voisin
const int minPoints = 3;  // Nombre minimum de points pour constituer un groupe

void readInputFile(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    std::string line;

    while (getline(inputFile, line)) {
        std::istringstream lineStream(line);
        Point point;
        double distance;
        while (lineStream >> distance) {
            point.distances.push_back(distance);
        }
        points.push_back(point);
    }
}

void expandCluster(Point& point, int group) {
    point.group = group;

    // Parcourir les points voisins
    for (size_t i = 0; i < points.size(); ++i) {
        double distance = point.distances[i];

        // Si le point est un voisin et n'appartient à aucun groupe
        if (distance <= epsilon && points[i].group == 0) {
            points[i].group = group;

            // Étendre le cluster aux voisins s'ils sont des points centraux
            if (points[i].type == PointType::CORE) {
                expandCluster(points[i], group);
            }
        }
    }
}

int determineCoreAndGroup() {
    int groupCounter = 0;

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

void visualizePoints() {
    std::cout << "Visualisation des points...\n";
    int image_width = 1350;
    int image_height = 1000;

    cv::Mat graph(image_height, image_width, CV_8UC3, cv::Scalar(255, 255, 255));
    int origin_x = 50;
    int origin_y = image_height - 50;
    cv::line(graph, cv::Point(origin_x, origin_y), cv::Point(image_width - origin_x, origin_y), cv::Scalar(0, 0, 0), 2);
    cv::line(graph, cv::Point(origin_x, origin_y), cv::Point(origin_x, 50), cv::Scalar(0, 0, 0), 2);
    cv::putText(graph, "x", cv::Point(image_width - 30, origin_y + 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
    cv::putText(graph, "y", cv::Point(origin_x - 30, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
    cv::putText(graph, "Representation visuelle - Algorithme DBSCAN", cv::Point(image_width / 2 - 100, 30), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(0, 0, 0), 2);
    cv::imshow("Representation visuelle - Algorithme DBSCAN", graph);

    int x = 200;
    int y = 800;
    cv::circle(graph, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), -1);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

bool findIntersectionPoint(std::vector<Point>& points, int targetIndex, double incertitude) {
    if (targetIndex < 0 || targetIndex >= points.size()) {
        return false;
    }

    Point& targetPoint = points[targetIndex];

    if (targetIndex == 0) {
        // Le point cible est le premier point, il n'y a pas d'intersection
        return true;
    } else if (targetIndex == 1) {
        // Le point cible est le deuxième point, on place le point sur le cercle du premier point
        targetPoint.x = points[0].x + points[0].distances[1];
        targetPoint.y = points[0].y;
        return true;
    }
    else if (targetIndex == 2) {
        double a = points[0].x; // Coordonnée x du premier point
        double b = points[0].y; // Coordonnée y du premier point
        double c = points[0].distances[2]; // Rayon du cercle du premier point
        double d = points[1].x; // Coordonnée x du deuxième point
        double e = points[1].y; // Coordonnée y du deuxième point
        double f = points[1].distances[2]; // Rayon du cercle du deuxième point

        double centerDist = std::sqrt((d - a) * (d - a) + (e - b) * (e - b));

        // Check if the circles are separate or contained within each other
        if (centerDist >= c + f || centerDist <= std::abs(c - f)) {
            return false;
        }

        double dx = d - a;
        double dy = e - b;
        double distance = std::sqrt(dx * dx + dy * dy);

        double xDiff = (distance * distance + c * c - f * f) / (2.0 * distance);
        double yDiff = std::sqrt(c * c - xDiff * xDiff);

        // Premier point d'intersection
        targetPoint.x = a + (dx * xDiff + dy * yDiff) / distance;
        targetPoint.y = b + (dy * xDiff - dx * yDiff) / distance;

        // double x2 = a + (dx * xDiff - dy * yDiff) / distance;
        // double y2 = b + (dy * xDiff + dx * yDiff) / distance;
    } else {
        // trouver l'intersection des trois précédents cercles des trois points précédents

        double x1 = points[targetIndex - 3].x;
        double y1 = points[targetIndex - 3].y;
        double r1 = points[targetIndex - 3].distances[targetIndex];
        double x2 = points[targetIndex - 2].x;
        double y2 = points[targetIndex - 2].y;
        double r2 = points[targetIndex - 2].distances[targetIndex];
        double x3 = points[targetIndex - 1].x;
        double y3 = points[targetIndex - 1].y;
        double r3 = points[targetIndex - 1].distances[targetIndex];

        // @TODO Calculer les coordonnées du point d'intersection des trois cercles
        double A = 2 * (x2 - x1);
        double B = 2 * (y2 - y1);
        double C = r1 * r1 - r2 * r2 - x1 * x1 + x2 * x2 - y1 * y1 + y2 * y2;
        double D = 2 * (x3 - x2);
        double E = 2 * (y3 - y2);
        double F = r2 * r2 - r3 * r3 - x2 * x2 + x3 * x3 - y2 * y2 + y3 * y3;

        // Calcul de l'intesection
        double x = (C * E - F * B) / (E * A - B * D);
        double y = (C * D - A * F) / (B * D - A * E);

        // Vérifier si la distance entre le point d'intersection et les points existants est bien respectée
        /*double distanceToFirstPoint = std::sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
        double distanceToSecondPoint = std::sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        double distanceToThirdPoint = std::sqrt((x - x3) * (x - x3) + (y - y3) * (y - y3));

        if (std::abs(distanceToFirstPoint - r1) > incertitude ||
            std::abs(distanceToSecondPoint - r2) > incertitude ||
            std::abs(distanceToThirdPoint - r3) > incertitude) {
            std::cout << "Les distances ne sont pas respectées avec une précision suffisante pour le point " << targetIndex << std::endl;
            return false;
        }*/

        targetPoint.x = x;
        targetPoint.y = y;
    }
}

int main() {
    readInputFile("resources/input_data.txt");
    int groupCounter = determineCoreAndGroup();
    determineBorderAndOutlier();
    // printResults(groupCounter);
    // visualizePoints();

    double incertitude = 1e-6; // Valeur d'écart tolérée lors de la comparaison des distances

    for (int i = 0; i < points.size(); ++i) {
        if (!findIntersectionPoint(points, i, incertitude)) {
            std::cout << "Impossible de trouver les coordonnées du point " << i << std::endl;
        }
    }

    for (int i = 0; i < points.size(); ++i) {
        std::cout << "Coordonnées du point " << i << " : (" << points[i].x << ", " << points[i].y << ")" << std::endl;
    }
    return 0;
}