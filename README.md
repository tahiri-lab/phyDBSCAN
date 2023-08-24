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
make run
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

```0	0.4	0.4	0.4	0.4	1	1	1	1	1	0.8	1	1	1	1	0.8	0.8	0.6	0.8	0.8
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

The first number (20) is the number of points in the dataset, the third number (4) is the number of clusters expected.
This third number is used to calculate the ARI (Adjusted Rand Index).

The output of the program is the following (with the number of groups expected in the dataset : 4):

![exampleResult.png](https://github.com/tahiri-lab/phyDBSCAN/blob/main/img/exampleResult.png)

And the output for ARI calculation is the following (*Only if there are no Outliers points*):

![exampleARICalculation.png](https://github.com/tahiri-lab/phyDBSCAN/blob/main/img/exampleARICalculation.png)

# Contact
Please email us at : <Nadia.Tahiri@USherbrooke.ca> or <Thibaut.Leval@USherbrooke.ca> for any question or feedback.