﻿﻿﻿﻿﻿﻿﻿<h1  align="center"> phyDBSCAN <p align='center'> 
        [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) 
        [![Contributions](https://img.shields.io/badge/contributions-welcome-blue.svg)](https://devdocs.io/cpp/)
        ![GitHub release](https://img.shields.io/github/v/release/tahiri-lab/phyDBSCAN?include_prereleases&label=pre-release&logo=github) 
        </p>


<h2  align="center">Building alternative phylogenetic trees using DBSCAN</h2>



<details open>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About the project</a>
    </li>
    <li>
      <a href="#Installation">Installation</a>
    </li>
    <li>
      <a href="#Examples">Examples</a>
    </li>
    <li>
      <a href="#contact">Contact</a>
    </li>
  </ol>
</details>



# About the project

This project aims to perform tree classification using the DBSCAN algorithm. Instead of using traditional coordinates, 
distances between points are employed for the classification.

If you would like to find out more about the project, the ideas for improvement, the difficulties encountered and 
the changes to be made, please read the "phyDBSCAN_Project_Report.pdf" in attachment.

# Installation

Insert your dataset matrix in the "resources/input_data.txt" file, then use one of the two compilation methods.

### Using Makefile:

Use the provided Makefile to install the project:

```
make
```

To run the project, execute:

```
./phyDBSCAN input.txt output.csv
```

To clean the project, execute:

```
make clean
```

### Using CMakeLists:

Alternatively, if you are using Clion IDE, you can use CMake for building the project. Here are the steps:

1. Run Clion IDE & Open the project
2. Go to Run -> Edit Configurations
3. Click on the "+" button and select "CMake"
4. In the "Name" field, enter "phyDBSCAN" and fill information like in the following image:
   ![CMakeLists.png](https://github.com/tahiri-lab/phyDBSCAN/blob/main/img/CMakeLists.png)
5. Click on "Apply" and "OK" and run the project

# Examples of use

To test, we took a matrix from the "resources/input_simulation_dataset.txt" file

Input Data Set used in this example (distance matrix) we put in the file "resources/input_data.txt":

```
0	0.4	0.4	0.4	0.4	1	1	1	1	1	0.8	1	1	1	1	0.8	0.8	0.6	0.8	0.8
0.4	0	0.4	0.8	0.8	0.8	0.8	0.8	0.8	0.8	1	0.8	1	1	0.8	0.8	0.8	0.8	0.8	0.8
0.4	0.4	0	0.8	0.8	1	1	1	1	1	1	1	0.8	0.8	1	0.8	0.8	0.8	0.8	0.8
0.4	0.8	0.8	0	0.6	1	1	1	1	1	0.8	1	1	1	1	0.6	0.6	0.4	0.6	0.6
0.4	0.8	0.8	0.6	0	1	1	1	1	1	0.6	0.8	0.8	0.8	0.8	1	1	0.8	1	1
1	0.8	1	1	1	0	0.4	0.4	0.4	0.4	1	0.8	1	1	0.8	1	1	0.8	1	1
1	0.8	1	1	1	0.4	0	0.6	0.4	0.6	1	0.6	1	1	0.6	1	1	0.8	1	1
1	0.8	1	1	1	0.4	0.6	0	0.6	0.6	1	0.8	1	1	0.8	1	1	0.8	1	1
1	0.8	1	1	1	0.4	0.4	0.6	0	0.6	1	0.8	1	1	0.8	1	1	0.8	1	1
1	0.8	1	1	1	0.4	0.6	0.6	0.6	0	1	0.8	1	1	0.8	1	1	0.8	1	1
0.8	1	1	0.8	0.6	1	1	1	1	1	0	0.4	0.4	0.4	0.4	1	1	0.8	1	1
1	0.8	1	1	0.8	0.8	0.6	0.8	0.8	0.8	0.4	0	0.4	0.4	0	1	1	1	1	1
1	1	0.8	1	0.8	1	1	1	1	1	0.4	0.4	0	0	0.4	1	1	1	1	1
1	1	0.8	1	0.8	1	1	1	1	1	0.4	0.4	0	0	0.4	1	1	1	1	1
1	0.8	1	1	0.8	0.8	0.6	0.8	0.8	0.8	0.4	0	0.4	0.4	0	1	1	1	1	1
0.8	0.8	0.8	0.6	1	1	1	1	1	1	1	1	1	1	1	0	0.4	0.4	0.4	0.4
0.8	0.8	0.8	0.6	1	1	1	1	1	1	1	1	1	1	1	0.4	0	0.4	0.6	0.6
0.6	0.8	0.8	0.4	0.8	0.8	0.8	0.8	0.8	0.8	0.8	1	1	1	1	0.4	0.4	0	0.6	0.6
0.8	0.8	0.8	0.6	1	1	1	1	1	1	1	1	1	1	1	0.4	0.6	0.6	0	0.6
0.8	0.8	0.8	0.6	1	1	1	1	1	1	1	1	1	1	1	0.4	0.6	0.6	0.6	0
```

In the "input_simulated_data.txt" file, the first line of this dataset is the following:
20	8	4	0	50

The first number (20) is the number of points in the dataset, the third number (4) is the number of clusters expected, it is used to calculate the ARI (Adjusted Rand Index).

The output of the program will be stored in the output.csv file as follows :
```
DBSCAN;0.490000;3;20;8;4;50;1.000000;(1<>1<>1<>1<>1<>2<>2<>2<>2<>2<>3<>3<>3<>3<>3<>4<>4<>4<>4<>4);462
```
DBSCAN : method used for the clustering

0.490000 : value of epsilon

3 : number of minimum points

20 : number of trees in the matrix

8 : number of leaves in each trees

4 : number of cluster we expect to find

50 : noise (differences between the trees within a cluster)

1.00000 : ARI

(<><><>) : partition

462 : time it took the program to calculate the clusters and ARI for the matrix

# Contact
Please email us at : <Nadia.Tahiri@USherbrooke.ca> or <Thibaut.Leval@USherbrooke.ca> for any question or feedback.
