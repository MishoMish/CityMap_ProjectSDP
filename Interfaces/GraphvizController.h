//
// Created by Mihail Dobroslavski on 27.12.23.
//

#ifndef CITYMAP_GRAPHVIZCONTROLLER_H
#define CITYMAP_GRAPHVIZCONTROLLER_H

#include "../Structure/GraphContainer.h";

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_set>


class GraphvizController {
public:
    static void generateDotFile(GraphContainer *graphContainer, Graph *current, std::unordered_set<Graph *> closed);

    static void runGraphvizAndOpenImage();
};

#endif //CITYMAP_GRAPHVIZCONTROLLER_H
