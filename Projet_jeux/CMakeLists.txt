# Spécifie la version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(JeuC++)

# Spécifie la version du langage C++
set(CMAKE_CXX_STANDARD 14)

# Liste des fichiers source à compiler
set(SOURCES
    random.cpp
    inventaire.cpp
    personnage.cpp
    combat.cpp
    catalogue.cpp
    main.cpp 
    # Ajoute tous les fichiers source ici
)
include_directories(${CMAKE_SOURCE_DIR})
# Crée l'exécutable à partir des fichiers source
add_executable(jeu ${SOURCES})
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
