#include "Clustering.h"
#include "FileIO.h"
#include "HyperparametersCalculator.h"
#include "ARI.h"
#include <iostream>
#include <map>
#include <string>
#include <chrono>

using namespace std;


void timeToInt(long& temps, auto time)
{
    auto micros_time = std::chrono::time_point_cast<std::chrono::microseconds>(time);
    auto epoch_time = micros_time.time_since_epoch();
    auto value_time = std::chrono::duration_cast<std::chrono::microseconds>(epoch_time);
    temps = value_time.count();
}

void computation(std::vector<Point>& points, std::string& Partition,  std::map <std::string, int>& clusterParam, double& ARI, double& bestEpsilon, int& bestMinPoints)
{
    bestEpsilon = findBestEpsilon(points);
    bestMinPoints = findBestMinPoints(points, bestEpsilon);
    printf("\n Best epsilon found : %f \t Best min points found : %d\n", bestEpsilon, bestMinPoints);

    determineCoreAndGroup(points, bestEpsilon, bestMinPoints);
    determineBorderAndOutlier(points, bestEpsilon);
    printResults(points, Partition);

    //if (canCalculateARI(points)) {
        int fileDefinedGroupCount = clusterParam["#Clusters"];
        ARI = calculateARI(points, fileDefinedGroupCount, clusterParam["#Trees"]);
   // }
    //else { printf("\nNo ARI calculated due to the presence of an outlier.\n"); }
}


int main(int nargc, char **argv) {
    using std::chrono::system_clock;

    if(nargc < 3) {
        printf("\nWrong command format. Format must be :\n\t > ./phyDBSCAN input_file.txt output_file.csv \n");
        exit(1);
        }
    
    std::vector<Point> points;
    std::map <std::string, int> infoCSV;
    std::string fileName = argv[1];
    FILE * out = fopen(argv[nargc-1],"w");
    std::ifstream inputFile(fileName);
    std::string line;
    std::string partition;
    double best_Epsilon;
    int best_MinPoints;
    long start;
    long end;
    auto starting = std::chrono::system_clock::now();

    std::cout << "\n==== DBSCAN Clustering Algorithm ====\n" << std::endl;
    std::cout << "Reading input data..." << std::endl;
    int i = 0;

    while (getline(inputFile, line)) {
        int find_decimal = line.find(".");

        if(find_decimal >= 0)
        {
            std::istringstream lineStream(line);
            Point point;
            double distance;
            while (lineStream >> distance) {
                point.distances.push_back(distance);
            }

            points.push_back(point);
        }
        else if (find_decimal = -1)
        {
            if (line[0] == 47 || line[0] == 48)
            {
                std::istringstream lineStream(line);
                Point point;
                double distance;
                while (lineStream >> distance) {
                    point.distances.push_back(distance);
                }

                points.push_back(point);
            }
            else if (line[0] >=49 && line[1]>=48)
            {   i=0;
                // Initialize the starting time here
                // Here that we start parsing and retrieving the necessary data.
                starting = std::chrono::system_clock::now();
                std::istringstream lineStream(line);
                int data;

                while (lineStream >> data)
                {
                    if(i == 0){ infoCSV["#Trees"] = data; }
                    else if (i == 1){ infoCSV["#Leaves"] = data; }
                    else if (i == 2){ infoCSV["#Clusters"] = data; }
                    else if (i == 4){ infoCSV["Noise"] = data; }
                    i++;
                }
                i = 0;
            }

            else if (line[0] == 0)
            {
                partition += "(";
                double ARI = 0;
                computation(points, partition, infoCSV, ARI, best_Epsilon, best_MinPoints);
                auto ending = std::chrono::system_clock::now();
                timeToInt(start, starting);
                timeToInt(end, ending);

            // Initialize the end time here
            // Retrieve time after every caculation is done
            // After, compute difference between start and end.
                fprintf(out,"DBSCAN;%f;%d;%d;%d;%d;%d;%f;%s;%ld\n",best_Epsilon, best_MinPoints, infoCSV["#Trees"], infoCSV["#Leaves"], infoCSV["#Clusters"], infoCSV["Noise"], ARI, partition.c_str(), end-start);
                points.clear();
                partition = "";
            }
        }

    }
    printf("\n");
    double ARI = 0;
    partition += "(";

    computation(points, partition, infoCSV, ARI, best_Epsilon, best_MinPoints);
    auto ending = std::chrono::system_clock::now();
    timeToInt(start, starting);
    timeToInt(end, ending);
    fprintf(out,"DBSCAN;%f;%d;%d;%d;%d;%d;%f;%s;%ld\n", best_Epsilon, best_MinPoints, infoCSV["#Trees"], infoCSV["#Leaves"], infoCSV["#Clusters"], infoCSV["Noise"], ARI, partition.c_str(), end-start);
    fclose(out);
    points.clear();

    return 0;
}
