//
// Created by Mihail Dobroslavski on 24.12.23.
//

#ifndef CITYMAP_GRAPH_H
#define CITYMAP_GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>

class Graph
{
public:
    explicit Graph(std::string);
    void print();
    void addEdge(Graph*, double);
    std::string name;
    std::unordered_map<Graph*, double> adjacencyList;
};

#endif //CITYMAP_GRAPH_H
