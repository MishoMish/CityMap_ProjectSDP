//
// Created by Mihail Dobroslavski on 24.12.23.
//

#ifndef CITYMAP_GRAPHCONTAINER_H
#define CITYMAP_GRAPHCONTAINER_H

#include "Graph.h"
#include <unordered_map>
#include <fstream>
#include <sstream>

class GraphContainer {
public:
    ~GraphContainer();
    void parseFile(const std::string&);
    bool containsKey(const std::string&);
    void addGraph(const std::string&);
    Graph* getGraph(const std::string&);
    void addRoad(const std::string&, const std::string&, double);
    void print();

    std::unordered_map<std::string, Graph*> graphs;
};

#endif //CITYMAP_GRAPHCONTAINER_H
