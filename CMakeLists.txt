cmake_minimum_required(VERSION 3.27)
project(da2324_project1)

set(CMAKE_CXX_STANDARD 17)

add_executable(da2324_project1
        src/main.cpp
        src/Edge.cpp
        src/Vertex.cpp
        src/Vertex.h
        src/Edge.h
        src/Graph.h
        src/Manager.h
        src/Manager.cpp
        src/Graph.cpp
        src/City.cpp
        src/City.h
        src/Reservoir.cpp
        src/Reservoir.h
        src/Station.cpp
        src/Station.h)
