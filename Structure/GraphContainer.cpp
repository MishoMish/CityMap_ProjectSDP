//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "GraphContainer.h"

// Destructor to free allocated memory for graphs
GraphContainer::~GraphContainer() {
    for (auto it = graphs.begin(); it != graphs.end(); it++) {
        delete it->second;
    }
}

// Method to parse a file containing graph information
void GraphContainer::parseFile(const std::string &filePath) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Error opening file: " + filePath);
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        while (line[0] == ' ')
            line = line.substr(1);

        if (line.empty() || line.substr(0, 2) == "//")
            continue;

        std::stringstream ss(line);
        std::vector<std::string> elements;

        std::string element;
        while (ss >> element) {
            elements.push_back(element);
        }

        addGraph(elements[0]);
        for (std::size_t i = 1; i < elements.size(); i += 2) {
            addRoad(elements[0], elements[i], std::stod(elements[i + 1]));
        }
    }

    inputFile.close();
}

// Check if the graph container contains a graph with the given name
bool GraphContainer::containsKey(const std::string &graphName) {
    return graphs.find(graphName) != graphs.end();
}

// Add a graph to the container
void GraphContainer::addGraph(const std::string &graphName) {
    if (!containsKey(graphName)) {
        auto *temp = new Graph(graphName);
        graphs[graphName] = temp;
    }
}

// Add a road (edge) between two graphs with the given distance
void GraphContainer::addRoad(const std::string &graph1, const std::string &graph2, double distance) {
    addGraph(graph1);
    addGraph(graph2);

    graphs[graph1]->addEdge(graphs[graph2], distance);
}

// Print method to display information about all graphs in the container
void GraphContainer::print() {
    std::cout << "--- --- --- --- ---\n";
    for (const auto &it: graphs) {
        std::cout << it.first << " " << it.second << " : " << std::endl;
        it.second->print();
        std::cout << " --- \n";
    }
}

// Get a graph from the container by name
Graph *GraphContainer::getGraph(const std::string &name) const {
    auto it = graphs.find(name);
    return it != graphs.end() ? it->second : nullptr;
}

// Getter method to retrieve all graphs in the container
const std::unordered_map<std::string, Graph *> &GraphContainer::getGraphs() const {
    return graphs;
}
