//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "TerminalProgram.h"
#include "../TaskFunctions/RouteChecker.h"
#include "GraphvizController.h"

#include <unordered_set>

TerminalProgram::TerminalProgram(GraphContainer* _map, Graph* _start) {
    map = _map;
    current = _start;
}

TerminalProgram::~TerminalProgram(){
    delete map;
}

void TerminalProgram::printHelpCommand(const std::string& path){
    std::ifstream inputFile(path);
    if (inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            std::cout << line << std::endl;
        }
        inputFile.close();
    } else {
        std::cerr << "Can't open help file! Check program setup!" << path << std::endl;
    }
}

void TerminalProgram::run() {
    printHelpCommand("intro.txt");

    map->parseFile("input.txt");
    std::unordered_set<Graph*> closedJunctions;

    while (true) {
        std::cout << "Enter command: ";
        std::string input;
        std::getline(std::cin, input);

        std::stringstream ss(input);
        std::string command;
        ss >> command;

        if (command == "location") {
            std::cout << "Current location: " << current->name << std::endl;
        } else if (command == "change") {
            std::string newLocation;
            ss >> newLocation;
            if (map->graphs.find(newLocation) != map->graphs.end()) {
                current = map->graphs[newLocation];
                std::cout << "Location changed to: " << current->name << std::endl;
            } else {
                std::cout << "Invalid location: " << newLocation << std::endl;
            }
        } else if (command == "neighbours") {
            std::cout << "Neighbours of " << current->name << ": ";
            for (std::pair<Graph *const, double> neighbor : current->adjacencyList) {
                std::cout << neighbor.first->name << " ";
            }
            std::cout << std::endl;
        } else if (command == "move") {
            std::string destination;
            ss >> destination;

            Graph* end = map->graphs[destination];

            std::vector<Path> paths = RouteChecker::getPaths(current, end, closedJunctions);
            if(paths.size() == 0){
                std::cout << "No route available. Can't apply move command!" << std::endl;
            } else {
                paths[0].print();
                current = end;
                std::cout << "Success!" << std::endl;
            }


        } else if (command == "close") {
            std::string closedLocation;
            ss >> closedLocation;
            if (map->graphs.find(closedLocation) != map->graphs.end()) {
                closedJunctions.insert(map->graphs[closedLocation]);
                std::cout << "Closed location: " << closedLocation << std::endl;
            } else {
                std::cout << "Invalid location: " << closedLocation << std::endl;
            }
        } else if (command == "open") {
            std::string openLocation;
            ss >> openLocation;
            if (map->graphs.find(openLocation) != map->graphs.end()) {
                closedJunctions.erase(map->graphs[openLocation]);
                std::cout << "Opened location: " << openLocation << std::endl;
            } else {
                std::cout << "Invalid location: " << openLocation << std::endl;
            }
        } else if (command == "closed") {
            std::cout << "Closed locations: ";
            for (Graph* closed : closedJunctions) {
                std::cout << closed->name << " ";
            }
            std::cout << std::endl;
        } else if (command == "tour") {
            Path* tourPath = RouteChecker::hasHamiltonianPath(map);
            std::cout << "An example tour (Hamiltonian road): ";
            tourPath->print();

            if(tourPath != nullptr)
                delete tourPath;
        } else if (command == "exists") {
            // doesn't look for closed roads
            std::string start, end;
            ss >> start >> end;
            Graph* startGraph = map->graphs[start];
            Graph* endGraph = map->graphs[end];

            bool pathExists = RouteChecker::exists(startGraph, endGraph);
            std::cout << "Path exists between " << start << " and " << end << ": " << (pathExists ? "Yes" : "No") << std::endl;
        } else if (command == "paths") {
            std::string start, end;
            ss >> start >> end;

            Graph* startGraph = map->graphs[start];
            Graph* endGraph = map->graphs[end];

            std::vector<Path> paths = RouteChecker::getPaths(startGraph, endGraph, closedJunctions);
            if(paths.size() == 0){
                if(RouteChecker::exists(startGraph, endGraph)){
                    std::cout << "Something is closed ;( ";
                }
                std::cout << "No paths found!" << std::endl;
            }
            for(Path path : paths){
                path.print();
            }
        } else if (command == "canReturnTo") {
            if(RouteChecker::canReturnToStart(current)){
                std::cout << "We can return to start after exiting \"" << current->name << "\".\n";
            } else {
                std::cout << "Once out, we can't return to \"" << current->name << "\".\n";
            }
        } else if (command == "hamiltonianPath") {
            Path* tourPath = RouteChecker::hasHamiltonianPath(map);
            std::cout << "An example tour (Hamiltonian road): ";
            tourPath->print();

            if(tourPath != nullptr)
                delete tourPath;
        } else if (command == "canReachAllNodes") {
            if(RouteChecker::canReachAllNodes(map, current)){
                std::cout << "Can reach them all from \"" << current->name << "\".\n";
            } else {
                std::cout << "Can't reach them all from \"" << current->name << "\".\n";
            }
        } else if (command == "deadEnds") {
            std::vector<std::pair<Graph*, Graph*>> deadEnds = RouteChecker::findAllDeadEnded(map);
            if(deadEnds.size() == 0){
                std::cout << "No dead ends found!\n";
            } else {
                std::cout << "Dead ends are:\n";
                for(std::pair<Graph*, Graph*> deadEnd : deadEnds){
                    std::cout << deadEnd.first << "->" << deadEnd.second << "\n";
                }
            }
        } else if (command == "visual") {
            GraphvizController::generateDotFile(map, current, closedJunctions);
            GraphvizController::runGraphvizAndOpenImage();
        } else if (command == "help") {
            printHelpCommand("commandHelp.txt");
        } else if (command == "help2") {
            printHelpCommand("commandHelp2.txt");
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command." << std::endl;
        }
        std::cout << "===========================================================================================================\n";
    }

}
