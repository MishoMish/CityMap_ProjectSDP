//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "TerminalProgram.h"

// Constructor for TerminalProgram
TerminalProgram::TerminalProgram(GraphContainer *_map, Graph *_start) {
    map = _map;
    current = _start;
}

// Destructor for TerminalProgram
TerminalProgram::~TerminalProgram() {
    delete map;
}

// Function to print the contents of a help file
void TerminalProgram::printHelpCommand(const std::string &path) {
    std::ifstream inputFile(path);
    if (inputFile.is_open()) {
        std::string line;
        // Print each line of the help file
        while (getline(inputFile, line)) {
            std::cout << line << std::endl;
        }
        inputFile.close();
    } else {
        throw std::invalid_argument("Can't open help file! Check program setup!");
    }
}

// Function to print the introduction using a help file
void TerminalProgram::printIntroduction() {
    printHelpCommand("InLineDatabase/intro.txt");
}

// Function to print general help using a help file
void TerminalProgram::printHelp() {
    printHelpCommand("InLineDatabase/commandHelp.txt");
}

// Function to print additional help using a second help file
void TerminalProgram::printHelp2() {
    printHelpCommand("InLineDatabase/commandHelp2.txt");
}

// Function to handle the "location" command
void TerminalProgram::handleLocationCommand() {
    std::cout << "Current location: " << current->getName() << std::endl;
}

// Function to handle the "change" command
void TerminalProgram::handleChangeCommand(std::stringstream &ss) {
    std::string newLocation;
    ss >> newLocation;
    // Change location if valid, otherwise print an error message
    if (map->containsKey(newLocation)) {
        current = map->getGraph(newLocation);
        std::cout << "Location changed to: " << current->getName() << std::endl;
    } else {
        std::cout << "Invalid location: " << newLocation << std::endl;
    }
}

// Function to handle the "neighbours" command
void TerminalProgram::handleNeighboursCommand() {
    std::cout << "Neighbours of " << current->getName() << ": ";
    // Print the names of neighboring graphs
    for (std::pair<Graph *const, double> neighbor: current->getAdjacencyList()) {
        std::cout << neighbor.first->getName() << " ";
    }
    std::cout << std::endl;
}

// Function to handle the "move" command
void TerminalProgram::handleMoveCommand(std::stringstream &ss) {
    std::string destination;
    ss >> destination;

    if (!map->containsKey(destination)) {
        std::cout << "Not a valid destination!!!" << std::endl;
        return;
    }

    Graph *end = map->getGraph(destination);

    std::vector<Path> paths = RouteChecker::getPaths(current, end, closedJunctions);
    if (paths.size() == 0) {
        std::cout << "No route available. Can't apply move command!" << std::endl;
    } else {
        paths[0].print();
        current = end;
        std::cout << "Success!" << std::endl;
    }
}

// Function to handle the "close" command
void TerminalProgram::handleCloseCommand(std::stringstream &ss) {
    while (!ss.eof() && ss.peek() != EOF) {
        std::string closedLocation;
        ss >> closedLocation;
        // Close the specified location if valid, otherwise print an error message
        if (map->containsKey(closedLocation)) {
            closedJunctions.insert(map->getGraph(closedLocation));
            std::cout << "Closed location: " << closedLocation << std::endl;
        } else {
            std::cout << "Invalid location: " << closedLocation << std::endl;
        }
    }
}

// Function to handle the "open" command
void TerminalProgram::handleOpenCommand(std::stringstream &ss) {
    while (!ss.eof() && ss.peek() != EOF) {
        std::string openLocation;
        ss >> openLocation;
        // Open the specified location if valid, otherwise print an error message
        if (map->containsKey(openLocation)) {
            closedJunctions.erase(map->getGraph(openLocation));
            std::cout << "Opened location: " << openLocation << std::endl;
        } else {
            std::cout << "Invalid location: " << openLocation << std::endl;
        }
    }
}

// Function to handle the "closed" command
void TerminalProgram::handleClosedCommand() {
    std::cout << "Closed locations: ";
    // Print the names of closed locations
    for (Graph *closed: closedJunctions) {
        std::cout << closed->getName() << " ";
    }
    std::cout << std::endl;
}

// Function to handle the "tour" command
void TerminalProgram::handleTourCommand() {
    Path *tourPath = RouteChecker::findEulerPath(map);
    std::cout << "An example tour (Euler path): ";
    tourPath->print();

    if (tourPath != nullptr)
        delete tourPath;
}

// Function to handle the "exists" command
void TerminalProgram::handleExistsCommand(std::stringstream &ss) {
    // doesn't look for closed roads
    std::string start, end;
    ss >> start >> end;
    Graph *startGraph = map->getGraph(start);
    Graph *endGraph = map->getGraph(end);

    bool pathExists = RouteChecker::exists(startGraph, endGraph);
    std::cout << "Path exists between " << start << " and " << end << ": " << (pathExists ? "Yes" : "No")
              << std::endl;
}

// Function to handle the "paths" command
void TerminalProgram::handlePathsCommand(std::stringstream &ss) {
    std::string start, end;
    ss >> start >> end;

    Graph *startGraph = map->getGraph(start);
    Graph *endGraph = map->getGraph(end);

    std::vector<Path> paths = RouteChecker::getPaths(startGraph, endGraph, closedJunctions);
    if (paths.size() == 0) {
        if (RouteChecker::exists(startGraph, endGraph)) {
            std::cout << "Something is closed ;( ";
        }
        std::cout << "No paths found!" << std::endl;
    }
    for (Path path: paths) {
        path.print();
    }
}

// Function to handle the "canReturnTo" command
void TerminalProgram::handleCanReturnToCommand() {
    if (RouteChecker::canReturnToStart(current)) {
        std::cout << "We can return to start after exiting \"" << current->getName() << "\".\n";
    } else {
        std::cout << "Once out, we can't return to \"" << current->getName() << "\".\n";
    }
}

// Function to handle the "hamiltonianPath" command
void TerminalProgram::handleHamiltonianPathCommand() {
    Path *tourPath = RouteChecker::hasPathAllGraph(map, current);
    std::cout << "An example tour (Hamiltonian road): ";
    tourPath->print();

    if (tourPath != nullptr)
        delete tourPath;
}

// Function to handle the "canReachAllNodes" command
void TerminalProgram::handleCanReachAllNodesCommand() {
    if (RouteChecker::canReachAllNodes(map, current)) {
        std::cout << "Can reach them all from \"" << current->getName() << "\".\n";
    } else {
        std::cout << "Can't reach them all from \"" << current->getName() << "\".\n";
    }
}

// Function to handle the "deadEnds" command
void TerminalProgram::handleDeadEndsCommand() {
    std::vector<std::pair<Graph *, Graph *>> deadEnds = RouteChecker::findAllDeadEnded(map);
    if (deadEnds.size() == 0) {
        std::cout << "No dead ends found!\n";
    } else {
        std::cout << "Dead ends are:\n";
        for (std::pair<Graph *, Graph *> deadEnd: deadEnds) {
            std::cout << deadEnd.first->getName() << "->" << deadEnd.second->getName() << "\n";
        }
    }
}

// Function to handle the "visual" command
void TerminalProgram::handleVisualCommand() {
    GraphvizController::generateDotFile(map, current, closedJunctions);
    GraphvizController::runGraphvizAndOpenImage();
}

// Main function to run the TerminalProgram
void TerminalProgram::run() {
    printIntroduction();

    while (true) {
        std::cout << "Enter command: ";
        std::string input;
        std::getline(std::cin, input);

        std::stringstream ss(input);
        std::string command;
        ss >> command;

        // Command handling logic
        if (command == "location") {
            handleLocationCommand();
        } else if (command == "change") {
            handleChangeCommand(ss);
        } else if (command == "neighbours") {
            handleNeighboursCommand();
        } else if (command == "move") {
            handleMoveCommand(ss);
        } else if (command == "close") {
            handleCloseCommand(ss);
        } else if (command == "open") {
            handleOpenCommand(ss);
        } else if (command == "closed") {
            handleClosedCommand();
        } else if (command == "tour") {
            handleTourCommand();
        } else if (command == "exists") {
            handleExistsCommand(ss);
        } else if (command == "paths") {
            handlePathsCommand(ss);
        } else if (command == "canReturnTo") {
            handleCanReturnToCommand();
        } else if (command == "hamiltonianPath") {
            handleHamiltonianPathCommand();
        } else if (command == "canReachAllNodes") {
            handleCanReachAllNodesCommand();
        } else if (command == "deadEnds") {
            handleDeadEndsCommand();
        } else if (command == "visual") {
            handleVisualCommand();
        } else if (command == "help") {
            printHelp();
        } else if (command == "help2") {
            printHelp2();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command." << std::endl;
        }

        // Divider for better readability
        std::cout
                << "===========================================================================================================\n";
    }
}

// Getter for map
GraphContainer *TerminalProgram::getMap() {
    return map;
}

// Getter for current
Graph *TerminalProgram::getCurrent() {
    return current;
}

// Getter for closedJunctions
std::unordered_set<Graph *> TerminalProgram::getClosedJunctions() {
    return closedJunctions;
}
