//
// Created by Mihail Dobroslavski on 24.12.23.
//

#ifndef CITYMAP_TERMINALPROGRAM_H
#define CITYMAP_TERMINALPROGRAM_H


#include "../Structure/GraphContainer.h"
#include "../TaskFunctions/RouteChecker.h"
#include "GraphvizController.h"
#include "unordered_set"

class TerminalProgram {
    GraphContainer *map;
    Graph *current;
    std::unordered_set<Graph *> closedJunctions;

public:
    TerminalProgram(GraphContainer *map, Graph *start);

    ~TerminalProgram();

    void printIntroduction();

    void printHelp();

    void printHelp2();

    void handleLocationCommand();

    void handleChangeCommand(std::stringstream &ss);

    void handleNeighboursCommand();

    void handleMoveCommand(std::stringstream &ss);

    void handleCloseCommand(std::stringstream &ss);

    void handleOpenCommand(std::stringstream &ss);

    void handleClosedCommand();

    void handleTourCommand();

    void handleExistsCommand(std::stringstream &ss);

    void handlePathsCommand(std::stringstream &ss);

    void handleCanReturnToCommand();

    void handleHamiltonianPathCommand();

    void handleCanReachAllNodesCommand();

    void handleDeadEndsCommand();

    void handleVisualCommand();


    void run();

    GraphContainer *getMap();

    Graph *getCurrent();

    std::unordered_set<Graph *> getClosedJunctions();

    void printHelpCommand(const std::string &filePath);
};


#endif //CITYMAP_TERMINALPROGRAM_H
