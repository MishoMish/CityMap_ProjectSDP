//
// Created by Mihail Dobroslavski on 24.12.23.
//

#ifndef CITYMAP_PATH_H
#define CITYMAP_PATH_H

#include <iostream>
#include <vector>
#include "Graph.h"

class Path {
public:
    double cost = 0.0;
    std::vector<Graph *> nodes;

    void print();
};


#endif //CITYMAP_PATH_H
