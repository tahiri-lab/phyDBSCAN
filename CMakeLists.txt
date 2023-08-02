cmake_minimum_required(VERSION 3.22)
project(phyDBSCAN)

set(CMAKE_CXX_STANDARD 17)

# Copie du fichier input_data.txt dans le répertoire de construction
configure_file(resources/input_data.txt ${CMAKE_CURRENT_BINARY_DIR}/resources/input_data.txt COPYONLY)

# Déclaration de l'exécutable et ajout des fichiers source
add_executable(phyDBSCAN src/poc.cpp)

# TODO A REVOIR POUR UTILISATION opencv
# set(OpenCV_DIR "C:/opencv/build/OpenCVConfig.cmake")
set(OpenCV_DIR "C:/Users/thiba/Documents/sherbrooke/git/opencv")
find_package(OpenCV 4 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
# Lien des bibliothèques OpenCV
target_link_libraries( phyDBSCAN ${OpenCV_LIBS} )

# Inclusion du répertoire "include" pour les fichiers d'en-tête
target_include_directories(phyDBSCAN PRIVATE include)

