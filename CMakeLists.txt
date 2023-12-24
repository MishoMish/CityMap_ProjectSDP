cmake_minimum_required(VERSION 3.27)
project(CityMap)

set(CMAKE_CXX_STANDARD 20)

add_executable(CityMap main.cpp
        Structure/Graph.cpp
        Structure/Graph.h
        Structure/GraphContainer.cpp
        Structure/GraphContainer.h
        TaskFunctions/RouteChecker.cpp
        TaskFunctions/RouteChecker.h
        Structure/Path.cpp
        Structure/Path.h
        Interfaces/TerminalProgram.cpp
        Interfaces/TerminalProgram.h)
