//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "RouteChecker.h"

bool RouteChecker::exists(Graph *startingGraph, Graph *endGraph) {
    std::unordered_set<Graph*> alreadyChecked;
    return existsHelper(startingGraph, endGraph, alreadyChecked);
}

bool RouteChecker::existsHelper(Graph *current, Graph *end, std::unordered_set<Graph *> checked) {
    checked.insert(current);
    if(current == end) {
        return true;
    }

    bool foundSolution = false;
    std::unordered_map<Graph*, double>::iterator it;
    for (it = current->adjacencyList.begin(); it != current->adjacencyList.end(); it++){
        if (auto search = checked.find(it->first); search == checked.end()){
            foundSolution = foundSolution || existsHelper(it->first, end, checked);
        }
    }
    return foundSolution;
}

std::vector<Path> RouteChecker::getPaths(bool closedMatters, Graph* start, Graph* end) {
    std::vector<Path> paths;
    std::vector<Path> shortestPaths;

    paths.push_back({0.0, {start}});

    while (!paths.empty() && shortestPaths.size() < 3) {
        std::sort(paths.begin(), paths.end(), [](const Path& a, const Path& b) {
            return a.cost < b.cost;
        });

        Path currentPath = paths.back();
        paths.pop_back();

        Graph* current = currentPath.nodes.back();

        if (current == end) {
            shortestPaths.push_back(currentPath);
            continue;
        }
        for (const auto& neighbor : current->adjacencyList) {
            Graph* next = neighbor.first;
            if (closedMatters && next->getIsClosed())
                continue;
            if (std::find(currentPath.nodes.begin(), currentPath.nodes.end(), next) != currentPath.nodes.end())
                continue;

            double newCost = currentPath.cost + neighbor.second;
            Path newPath = {newCost, currentPath.nodes};
            newPath.nodes.push_back(next);
            paths.push_back(newPath);
        }
    }
    return shortestPaths;
}


