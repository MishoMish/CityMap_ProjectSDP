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

std::vector<Path> RouteChecker::getPaths(Graph* start, Graph* end, const std::unordered_set<Graph*>& closed) {
    std::vector<Path> paths;
    std::vector<Path> shortestPaths;

    paths.push_back({0.0, {start}});

    while (!paths.empty() && shortestPaths.size() < 3) {
        std::sort(paths.begin(), paths.end(), [](const Path& a, const Path& b) {
            return a.cost > b.cost;
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
            if (closed.contains(next))
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

std::vector<Path> RouteChecker::getPaths(Graph* start, Graph* end) {
    std::unordered_set<Graph*> emptySet;
    return getPaths(start, end, emptySet);
}

bool RouteChecker::canReturnToStart(Graph* start) {
    std::unordered_set<Graph*> visited;
    return canReturnToStartHelper(start, start, visited);
}

bool RouteChecker::canReturnToStartHelper(Graph* current, Graph* start, std::unordered_set<Graph*>& visited) {
    visited.insert(current);

    for (const auto& neighbor : current->adjacencyList) {
        Graph* next = neighbor.first;
        if (next == start)
            return true;

        if (!visited.contains(next))
            if (canReturnToStartHelper(next, start, visited))
                return true;
    }

    return false;
}

bool RouteChecker::hasHamiltonianPath(GraphContainer* container, Graph* start) {
    Path* path = new Path();
    path->cost = 0;

    std::set< std::pair<Graph*, Graph*> > visitedEdges;
    bool found = false;

    hamiltonianPathUtil(container, start, start, path, visitedEdges, found);

    if (found) {
        path->print();
    } else {
        std::cout << "No Hamiltonian Path found." << std::endl;
    }

    delete path;
    return found;
}

void RouteChecker::hamiltonianPathUtil(GraphContainer* container, Graph* current, Graph* start, Path* path, std::set<std::pair<Graph*, Graph*> >& visitedEdges, bool& found) {
    path->nodes.push_back(current);

    if (path->nodes.size() == container->graphs.size()) {
        found = true;
        return;
    }

    for (const auto& neighbor : current->adjacencyList) {
        Graph* next = neighbor.first;

        if (!visitedEdges.contains({current, next})) {
            visitedEdges.insert({current, next});
            path->cost += neighbor.second;
            hamiltonianPathUtil(container, next, start, path, visitedEdges, found);

            if (found) {
                return;
            }

            visitedEdges.erase({current, next});
            path->cost -= neighbor.second;
        }
    }
    path->nodes.pop_back();
}

bool RouteChecker::canReachAllNodes(GraphContainer* container, Graph* start) {
    std::unordered_set<Graph*> visited;
    std::stack<Graph*> stack;

    stack.push(start);

    while (!stack.empty()) {
        Graph* current = stack.top();
        stack.pop();

        visited.insert(current);

        for (std::pair<Graph *const, double> neighbor : current->adjacencyList) {
            if (visited.find(neighbor.first) == visited.end()) {
                stack.push(neighbor.first);
            }
        }
    }

    return visited.size() == container->graphs.size();  // Check if all nodes were visited
}

std::vector<std::pair<Graph*, Graph*>> RouteChecker::findAllDeadEnded(GraphContainer* container){
    std::vector<std::pair<Graph*, Graph*>> vectorDeadEnds;

    std::unordered_map<std::string, Graph *>::iterator it;
    for (it = container->graphs.begin(); it != container->graphs.end(); it++)
    {
        for(auto item : it->second->adjacencyList){
            if(item.first->adjacencyList.size() == 0)
                vectorDeadEnds.push_back({it->second, item.first});
        }
    }

    return vectorDeadEnds;
}





