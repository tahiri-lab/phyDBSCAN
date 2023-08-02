cmake_minimum_required(VERSION 3.12)
project(phyDBSCAN)

set(CMAKE_CXX_STANDARD 17)

# Define sources and headers
set(SOURCES
        src/poc.cpp
        src/FileIO.cpp
        src/Clustering.cpp
        )

set(HEADERS
        include/FileIO.h
        include/Clustering.h
        include/Point.h
        )

# Add executable target
add_executable(phyDBSCAN ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(phyDBSCAN PRIVATE include)

# Source Grouping for IDE (optional but helpful)
source_group("Source Files" FILES ${SOURCES})
source_group("Header Files" FILES ${HEADERS})

# Copy resources to build directory
file(COPY resources/input_data.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
