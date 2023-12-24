//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "Graph.h"

#include <utility>

Graph::Graph(std::string _name) : name(std::move(_name)){}

void Graph::print(){
    std::unordered_map<Graph*, double>::iterator it;
    for (it = adjacencyList.begin(); it != adjacencyList.end(); it++){
        std::cout << it->first->name << " -> " << it->second << std::endl;
    }
}

void Graph::addEdge(Graph* toGraph, double distance){
    adjacencyList[toGraph] = distance;
}

std::string Graph::getName() {
    return this->name;
}

bool Graph::getIsClosed() {
    return closed;
}

void Graph::open() {
    closed = false;
}

void Graph::close() {
    closed = true;
}


