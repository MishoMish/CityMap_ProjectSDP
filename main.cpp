#include "Structure/Graph.h"
#include "Structure/GraphContainer.h"
#include "TaskFunctions/RouteChecker.h"

int main() {
    GraphContainer* map = new GraphContainer();
    map->parseFile("input.txt");
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




    delete map;
    return 0;
}

