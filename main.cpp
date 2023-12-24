#include "Structure/Graph.h"
#include "Structure/GraphContainer.h"
#include "TaskFunctions/RouteChecker.h"

int main() {
    GraphContainer map;
    map.parseFile("input.txt");
    //map.print();

    Graph* Popa = map.getGraph("Попа");
    Graph* NDK =map.getGraph("НДК");
    Graph* Kusheta =map.getGraph("5Кьошета");

    //std::cout << RouteChecker::exists(Popa, Kusheta);

    for(auto item : RouteChecker::getPaths(true, Popa, NDK)){
        item.print();
    }

    return 0;
}

