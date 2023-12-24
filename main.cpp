#include "Structure/Graph.h"
#include "Structure/GraphContainer.h"
#include "TaskFunctions/RouteChecker.h"
#include "Interfaces/TerminalProgram.h"

    //map.print();


    /*
     Graph* Popa = map->getGraph("Попа");
    Graph* NDK =map->getGraph("НДК");
    Graph* Kusheta =map->getGraph("5Кьошета");
    Graph* BSFS = map->getGraph("БСФС");

    //std::cout << RouteChecker::exists(Popa, Kusheta);

    //std::unordered_set<Graph*> temp;
    //temp.insert(Kusheta);
    //temp.insert(BSFS);

    for(auto item : RouteChecker::getPaths(Popa, NDK)){
        item.print();
    }
    std::cout << RouteChecker::canReturnToStart(NDK);

    RouteChecker::hasHamiltonianPath(map, Popa);
    std::cout << RouteChecker::canReachAllNodes(map, NDK);

     for(auto item : RouteChecker::findAllDeadEnded(map)){
        std::cout << item.first->name << " " << item.second->name << std::endl;
    }
*/
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


