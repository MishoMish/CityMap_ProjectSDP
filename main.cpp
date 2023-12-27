#include "Structure/Graph.h"
#include "Structure/GraphContainer.h"
#include "TaskFunctions/RouteChecker.h"
#include "Interfaces/TerminalProgram.h"

int main(int argc, char* argv[]) {

    if (argc < 4 || std::string(argv[1]) != "-i") {
        std::cerr << "Usage: " << argv[0] << " -i map_file.txt starting_junction" << std::endl;
        return 1;
    }

    std::string mapFile = argv[2];
    std::string startingJunction = argv[3];

    auto* map = new GraphContainer();
    map->parseFile(mapFile);

    if (map->graphs.find(startingJunction) == map->graphs.end()) {
        std::cerr << "Starting junction not found: " << startingJunction << std::endl;
        return 1;
    }

    Graph* start = map->graphs[startingJunction];

    auto* tp = new TerminalProgram(map, map->graphs[startingJunction]);
    tp->run();

    return 0;
}


