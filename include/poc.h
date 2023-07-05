//
// Created by thiba on 22/06/2023.
//

#ifndef POC_POC_H
#define POC_POC_H

#ifndef POC3_H
#define POC3_H

#include <string>
#include <vector>

/**
 * Enumération représentant les types de points possibles dans l'algorithme DBSCAN.
 */
enum class PointType {
    UNDEFINED, /**< Type de point indéfini */
    CORE, /**< Point central */
    BORDER, /**< Point de bordure */
    OUTLIER /**< Point aberrant */
};

/**
 * Structure représentant un point.
 */
struct Point {
    std::vector<double> distances; /**< Les distances à tous les autres points */
    PointType type = PointType::UNDEFINED; /**< Le type du point (UNDEFINED, Core, Border ou Outlier) */
    int group = 0; /**< Le groupe auquel le point appartient */
};

/**
 * Fonction pour lire le fichier d'entrée et initialiser les points.
 *
 * @param fileName Le nom du fichier d'entrée.
 */
void readInputFile(const std::string& fileName);

/**
 * Fonction pour étendre un cluster à partir d'un point central.
 *
 * @param point Le point central à partir duquel étendre le cluster.
 * @param group Le groupe auquel le point central appartient.
 */
void expandCluster(Point& point, int group);

/**
 * Fonction pour déterminer les points Core et leur groupe.
 *
 * @return Le nombre de groupes formés.
 */
int determineCoreAndGroup();

/**
 * Fonction pour déterminer les points de type Border et Outlier.
 */
void determineBorderAndOutlier();

/**
 * Fonction pour afficher les résultats de l'algorithme DBSCAN.
 *
 * @param groupCounter Le nombre total de groupes formés.
 */
void printResults(int groupCounter);

/**
 * Fonction pour générer le fichier csv pour visualiser le nuage de points à partir des distances.
 *
 * @param string
 */
void generateOutputFile(const char *string);

#endif // POC3_H
#endif //POC_POC_H
