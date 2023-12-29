#include "Structure/Graph.h"
#include "Structure/GraphContainer.h"
#include "Interfaces/TerminalProgram.h"

int main(int argc, char *argv[]) {
    try {
        if (argc < 4 || std::string(argv[1]) != "-i") {
            std::cerr << "Usage: " << argv[0] << " -i map_file.txt starting_junction" << std::endl;
            return 1;
        }

        std::string mapFile = argv[2];
        std::string startingJunction = argv[3];

        auto *map = new GraphContainer();
        map->parseFile(mapFile);

        auto it = map->getGraphs().find(startingJunction);
        if (it == map->getGraphs().end()) {
            std::cerr << "Starting junction not found: " << startingJunction << std::endl;
            return 1;
        }

        Graph *start = it->second;

        auto *tp = new TerminalProgram(map, map->getGraphs().at(startingJunction));
        tp->run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


