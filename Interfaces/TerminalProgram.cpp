//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "TerminalProgram.h"
#include "../TaskFunctions/RouteChecker.h"
#include <unordered_set>

TerminalProgram::TerminalProgram(GraphContainer* _map, Graph* _start) {
    map = _map;
    current = _start;
}

TerminalProgram::~TerminalProgram(){
    delete map;
}

void TerminalProgram::run() {
    map->parseFile("input.txt");
    std::unordered_set<Graph*> closedJunctions;

    while (true) {
        std::string command;
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == "location") {
            std::cout << "Current location: " << current->name << std::endl;
        } else if (command == "change") {
            std::string newLocation;
            std::cin >> newLocation;
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
            std::cin >> destination;

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
            std::cin >> closedLocation;
            if (map->graphs.find(closedLocation) != map->graphs.end()) {
                closedJunctions.insert(map->graphs[closedLocation]);
                std::cout << "Closed location: " << closedLocation << std::endl;
            } else {
                std::cout << "Invalid location: " << closedLocation << std::endl;
            }
        } else if (command == "open") {
            std::string openLocation;
            std::cin >> openLocation;
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
            // TODO Implement logic for the tour
            // RouteChecker::hasHamiltonianPath(map); // Need better implementation of hasHamiltonianPath
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command." << std::endl;
        }
    }

}
