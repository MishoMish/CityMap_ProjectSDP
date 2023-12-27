//
// Created by Mihail Dobroslavski on 24.12.23.
//

#ifndef CITYMAP_TERMINALPROGRAM_H
#define CITYMAP_TERMINALPROGRAM_H


#include "../Structure/GraphContainer.h"

class TerminalProgram {
    GraphContainer* map;
    Graph* current;

    void printHelpCommand(const std::string& filePath);
    public:
    TerminalProgram(GraphContainer* map, Graph* start);
    ~TerminalProgram();

    void run();
};


#endif //CITYMAP_TERMINALPROGRAM_H
