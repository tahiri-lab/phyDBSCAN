#include "Clustering.h"
#include "FileIO.h"
#include "HyperparametersCalculator.h"
#include "ARI.h"
#include <iostream>
#include <map>
#include <string>

//using namespace std;

int main(int nargc, char **argv) {
    std::vector<Point> points;
    std::map <std::string, int> infoCSV;
    std::string fileName = argv[1];
    FILE * out = fopen(argv[nargc-1],"w");
    std::ifstream inputFile(fileName);
    std::string line;
    std::string partition;
    //char * partition = (char*)malloc(1000*sizeof(char));
    int x = 0;


    std::cout << "\n==== DBSCAN Clustering Algorithm ====\n" << std::endl;
    //readInputFile("resources/input_data.txt", points, infoCSV);
    std::cout << "Reading input data..." << std::endl;
    int i = 0;

    while (getline(inputFile, line)) {
        if(line[0] == 49 || line[0] == 48)
        {
            std::istringstream lineStream(line);
            Point point;
            double distance;

            while (lineStream >> distance) {
                point.distances.push_back(distance);
            }

            points.push_back(point);
        }
        
        else if (line[0] >= 49 && line[1]>=48)
        {
            std::istringstream lineStream(line);
            int data;

            while (lineStream >> data) {

                if(i == 0){ infoCSV["#Trees"] = data; }
                else if (i == 1){ infoCSV["#Leaves"] = data; }
                else if (i == 2){ infoCSV["#Clusters"] = data; }
                else if (i == 4){ infoCSV["Noise"] = data; }
                i++;
            }
            i = 0;
        }

        else if (line[0] == 0) {

            double bestEpsilon = findBestEpsilon(points);
            std::cout << "> Best epsilon: " << bestEpsilon << std::endl;
            int bestMinPoints = findBestMinPoints(points, bestEpsilon);
            std::cout << "> Best minPoints: " << bestMinPoints << std::endl;

            infoCSV["best_Epsilon"] = bestEpsilon;
            infoCSV["best_MinPoints"] = bestMinPoints;

            determineCoreAndGroup(points, bestEpsilon, bestMinPoints);
            determineBorderAndOutlier(points, bestEpsilon);
            printResults(points, partition);

            if (canCalculateARI(points)) {
                int fileDefinedGroupCount = infoCSV["#Clusters"];
                double ARI = calculateARI(points, fileDefinedGroupCount, infoCSV["#Trees"]);
                std::cout << "\n> Calculated ARI score (Adjusted Rand Index, better if close to 1) = " << ARI << std::endl;
            }
            fprintf(out,"DBSCAN;%f;%d;%d;%d;%d;%d;%s\n", bestEpsilon, bestMinPoints, infoCSV["#Trees"], infoCSV["#Leaves"], infoCSV["#Clusters"], infoCSV["Noise"], partition.c_str());
            points.clear();
            partition = "";
        }

    }
    printf("\n");

    double bestEpsilon = findBestEpsilon(points);
    std::cout << "> Best epsilon: " << bestEpsilon << std::endl;

    int bestMinPoints = findBestMinPoints(points, bestEpsilon);
    std::cout << "> Best minPoints: " << bestMinPoints << std::endl;

    infoCSV["best_Epsilon"] = bestEpsilon;
    infoCSV["best_MinPoints"] = bestMinPoints;

    determineCoreAndGroup(points, bestEpsilon, bestMinPoints);
    determineBorderAndOutlier(points, bestEpsilon);

    printResults(points, partition);
    //printf("\n nyokay %d", infoCSV["#Clusters"]);

    if (canCalculateARI(points)) {
       // if (isARIRequired()) {
            //int userDefinedGroupCount = userDefinedGroupCountInput();
            int fileDefinedGroupCount = infoCSV["#Clusters"];
            double ARI = calculateARI(points, fileDefinedGroupCount, infoCSV["#Trees"]);
            std::cout << "\n> Calculated ARI score (Adjusted Rand Index, better if close to 1) = " << ARI << std::endl;
        //}
    }
    fprintf(out,"DBSCAN;%f;%d;%d;%d;%d;%s\n", bestEpsilon, bestMinPoints, infoCSV["#Trees"], infoCSV["#Leaves"], infoCSV["#Clusters"], partition.c_str());
    fclose(out);
    points.clear();
    return 0;
}
