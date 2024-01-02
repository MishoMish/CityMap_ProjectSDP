cmake_minimum_required(VERSION 3.27)
project(CityMapProject)

set(CMAKE_CXX_STANDARD 20)

# Add the path to your project source files
set(PROJECT_SOURCES
        main.cpp
        Structure/Graph.cpp
        Structure/Graph.h
        Structure/GraphContainer.cpp
        Structure/GraphContainer.h
        TaskFunctions/RouteChecker.cpp
        TaskFunctions/RouteChecker.h
        Structure/Path.cpp
        Structure/Path.h
        Interfaces/TerminalProgram.cpp
        Interfaces/TerminalProgram.h
        Interfaces/GraphvizController.cpp
        Interfaces/GraphvizController.h
)

# Create a library for your project
add_library(CityMapLibrary ${PROJECT_SOURCES})

# Create the main executable for your project
add_executable(CityMapProject main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # Ensure debug information is available

# Link the main executable against the project library
target_link_libraries(CityMapProject PRIVATE CityMapLibrary)

# Add the "UnitTesting" folder to the include directories
include_directories(UnitTesting)

# Create a variable to store all test files
file(GLOB TEST_SOURCES UnitTesting/*.cpp)

# Create test executables for each test file
foreach (TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE CityMapLibrary)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach ()

# Enable testing
enable_testing()
