cmake_minimum_required(VERSION 3.22)
project(PoC)

set(CMAKE_CXX_STANDARD 14)

# Copie du fichier input_data.txt dans le répertoire de construction
configure_file(resources/input_data.txt ${CMAKE_CURRENT_BINARY_DIR}/input_data.txt COPYONLY)

add_executable(PoC src/poc.cpp)
