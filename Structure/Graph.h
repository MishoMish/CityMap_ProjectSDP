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
    std::string getName();
    bool getIsClosed();
    void close();
    void open();

    std::unordered_map<Graph*, double> adjacencyList;
private:
    std::string name;
    bool closed = false;
};

#endif //CITYMAP_GRAPH_H