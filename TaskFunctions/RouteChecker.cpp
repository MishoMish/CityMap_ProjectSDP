//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "RouteChecker.h"

// Checks if there is a path from startingGraph to endGraph
bool RouteChecker::exists(Graph *startingGraph, Graph *endGraph) {
    if (startingGraph == endGraph) {
        return true;
    }

    auto &adjacencyList = startingGraph->getAdjacencyList();
    if (startingGraph == nullptr || endGraph == nullptr || adjacencyList.empty()) {
        return false;
    }

    std::unordered_set<Graph *> alreadyChecked;
    return existsHelper(startingGraph, endGraph, alreadyChecked);
}

// Helper function for exists
bool RouteChecker::existsHelper(Graph *current, Graph *end, std::unordered_set<Graph *> &checked) {
    checked.insert(current);

    if (current == end) {
        return true;
    }

    bool foundSolution = false;
    auto &adjacencyList = current->getAdjacencyList(); // Access the adjacency list once

    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it) {
        if (auto search = checked.find(it->first); search == checked.end()) {
            foundSolution = foundSolution || existsHelper(it->first, end, checked);
        }
    }

    return foundSolution;
}

// Gets up to three shortest paths from start to end, considering closed junctions
std::vector<Path> RouteChecker::getPaths(Graph *start, Graph *end, const std::unordered_set<Graph *> &closed) {
    std::vector<Path> paths;
    std::vector<Path> shortestPaths;

    paths.push_back({0.0, {start}});

    while (!paths.empty() && shortestPaths.size() < 3) {
        std::sort(paths.begin(), paths.end(), [](const Path &a, const Path &b) {
            return a.cost > b.cost;
        });

        Path currentPath = paths.back();
        paths.pop_back();

        const Graph *current = currentPath.nodes.back();

        if (current == end) {
            shortestPaths.push_back(currentPath);
            continue;
        }

        for (const auto &neighbor: current->getAdjacencyList()) {
            Graph *next = neighbor.first;
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

// Gets up to three shortest paths from start to end
std::vector<Path> RouteChecker::getPaths(Graph *start, Graph *end) {
    std::unordered_set<Graph *> emptySet;
    return getPaths(start, end, emptySet);
}

// Checks if there is a path from a node back to itself
bool RouteChecker::canReturnToStart(Graph *start) {
    std::unordered_set<Graph *> visited;
    return canReturnToStartHelper(start, start, visited);
}

// Helper function for canReturnToStart
bool RouteChecker::canReturnToStartHelper(Graph *current, Graph *start, std::unordered_set<Graph *> &visited) {
    visited.insert(current);

    for (const auto &neighbor: current->getAdjacencyList()) {
        Graph *next = neighbor.first;
        if (next == start)
            return true;

        if (!visited.contains(next))
            if (canReturnToStartHelper(next, start, visited))
                return true;
    }

    return false;
}

// Finds a Hamiltonian path in the given container, starting from any graph
Path *RouteChecker::hasHamiltonianPath(GraphContainer *container) {
    Path *returnPath = nullptr;
    for (auto temp: container->getGraphs()) {
        returnPath = hasHamiltonianPath(container, temp.second);
        if (returnPath != nullptr)
            break;
    }
    return returnPath;
}

// Finds a Hamiltonian path starting from the specified graph
Path *RouteChecker::hasHamiltonianPath(GraphContainer *container, Graph *start) {
    Path *path = new Path();
    std::set < std::pair<Graph *, Graph *> > visitedEdges;
    bool found = false;
    hamiltonianPathUtil(container, start, start, path, visitedEdges, found);

    if (found) {
        return path;
    } else {
        delete path;
        return nullptr;
    }
}

// Helper function for finding Hamiltonian path
void RouteChecker::hamiltonianPathUtil(GraphContainer *container, Graph *current, Graph *start, Path *path,
                                       std::set<std::pair<Graph *, Graph *> > &visitedEdges, bool &found) {
    path->nodes.push_back(current);
    if (std::all_of(container->getGraphs().begin(), container->getGraphs().end(), [&path](const auto &nodePair) {
        return std::find(path->nodes.begin(), path->nodes.end(), nodePair.second) != path->nodes.end();
    })) {
        // if we need to end on start
        /*for(auto next : current->adjacencyList){
            if(next.first == start){
                found = true;
                return;
            }
        }*/

        // if we just need to cover all nodes
        found = true;
        return;
    }

    for (const auto &neighbor: current->getAdjacencyList()) {
        Graph *next = neighbor.first;
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

// Checks if it is possible to reach all nodes from a given start node
bool RouteChecker::canReachAllNodes(GraphContainer *container, Graph *start) {
    std::unordered_set<Graph *> visited;
    std::stack<Graph *> stack;

    stack.push(start);

    while (!stack.empty()) {
        Graph *current = stack.top();
        stack.pop();

        visited.insert(current);

        for (std::pair<Graph *const, double> neighbor: current->getAdjacencyList()) {
            if (visited.find(neighbor.first) == visited.end()) {
                stack.push(neighbor.first);
            }
        }
    }

    return visited.size() == container->getGraphs().size();
}

// Finds all dead-ended nodes in the container
std::vector<std::pair<Graph *, Graph *>> RouteChecker::findAllDeadEnded(GraphContainer *container) {
    std::vector<std::pair<Graph *, Graph *>> vectorDeadEnds;

    for (const auto &graphPair: container->getGraphs()) {
        Graph *currentGraph = graphPair.second;
        for (const auto &neighborPair: currentGraph->getAdjacencyList()) {
            Graph *neighborGraph = neighborPair.first;
            if (neighborGraph->getAdjacencyList().empty()) {
                vectorDeadEnds.push_back({currentGraph, neighborGraph});
            }
        }
    }

    return vectorDeadEnds;
}
