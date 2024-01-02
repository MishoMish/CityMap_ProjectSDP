//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "Graph.h"

// Constructor
Graph::Graph(std::string _name) : name(std::move(_name)) {}

// Print method to display the adjacency list of the graph
void Graph::print() {
    std::unordered_map<Graph *, double>::iterator it;
    for (it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
        std::cout << it->first->name << " -> " << it->second << std::endl;
    }
}

// Method to add an edge to the graph
void Graph::addEdge(Graph *toGraph, double distance) {
    adjacencyList[toGraph] = distance;
}

// Getter method to retrieve the adjacency list of the graph
const std::unordered_map<Graph *, double> &Graph::getAdjacencyList() const {
    return adjacencyList;
}

// Getter method to retrieve the name of the graph
const std::string &Graph::getName() const {
    return name;
}
