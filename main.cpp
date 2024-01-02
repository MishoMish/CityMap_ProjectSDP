#include "Structure/Graph.h"
#include "Structure/GraphContainer.h"
#include "Interfaces/TerminalProgram.h"

int main(int argc, char *argv[]) {
    try {
        // Check for the correct number of command-line arguments
        if (argc < 4 || std::string(argv[1]) != "-i") {
            std::cerr << "Usage: " << argv[0] << " -i map_file.txt starting_junction" << std::endl;
            return 1;
        }

        // Extract input parameters from command-line arguments
        std::string mapFile = argv[2];
        std::string startingJunction = argv[3];

        // Create a new GraphContainer to represent the map
        auto *map = new GraphContainer();

        // Parse the map file and populate the GraphContainer
        map->parseFile(mapFile);

        // Find the starting junction in the map
        auto it = map->getGraphs().find(startingJunction);
        if (it == map->getGraphs().end()) {
            std::cerr << "Starting junction not found: " << startingJunction << std::endl;
            return 1;
        }

        // Get the Graph pointer for the starting junction
        Graph *start = it->second;

        // Create a TerminalProgram instance with the map and starting junction
        auto *tp = new TerminalProgram(map, start);

        // Run the terminal program
        tp->run();
    } catch (const std::exception &e) {
        // Handle and print exceptions
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
