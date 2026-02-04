cmake_minimum_required(VERSION 3.10)
project(ProyectoGrafos)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Rutas de cabeceras (Aquí es donde CMake encuentra tu Controlador.hpp)
include_directories(include)
include_directories(.) 

# 2. Escaneo automático de archivos .cpp
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# 3. Filtro para evitar conflictos con la carpeta build
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/build/.*")

# 4. Crear el ejecutable
add_executable(juego_grafos ${SOURCES})