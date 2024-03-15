#include "FileIO.h"

void readInputFile(const std::string& fileName, std::vector<Point>& points, std::map <std::string, int>& info) {
    std::cout << "Reading input data..." << std::endl;
    std::ifstream inputFile(fileName);
    std::string line;
    int i = 0;
    int temoin = 0;

    while (getline(inputFile, line)) {
        if(line[0] == 49 || line[0] == 48)
        {   std::istringstream lineStream(line);
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

                if(i == 0){ info["#Trees"] = data; }
                else if (i == 1){ info["#Leaves"] = data; }
                else if (i == 2){ info["#Clusters"] = data; }
                else if (i == 4){ info["Noise"] = data; }
                i++;
            }
            temoin = 1;
            i = 0;
        }

    }
    printf("\n");
}