//
// Created by Mihail Dobroslavski on 24.12.23.
//

#include "GraphContainer.h"

GraphContainer::~GraphContainer()
{
    std::unordered_map<std::string, Graph *>::iterator it;
    for (it = graphs.begin(); it != graphs.end(); it++)
    {
        // std::cout << "Deleted " << it->first << std::endl;
        delete it->second;
    }
}

void GraphContainer::parseFile(const std::string& filePath){
    // TODO :: Can be sent in outside function
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::vector<std::string> elements;

        std::string element;
        while (ss >> element) {
            elements.push_back(element);
        }

        addGraph(elements[0]);
        for (std::size_t i = 1; i < elements.size(); i += 2) {
            addRoad(elements[0], elements[i], std::stod(elements[i+1]));
        }
    }

    inputFile.close();
}

bool GraphContainer::containsKey(const std::string& graphName)
{
    if (graphs.find(graphName) == graphs.end())
        return false;
    return true;
}

void GraphContainer::addGraph(const std::string& graphName)
{
    if (!containsKey(graphName))
    {
        auto *temp = new Graph(graphName);
        graphs[graphName] = temp;
    }
}

void GraphContainer::addRoad(const std::string& graph1, const std::string& graph2, double distance)
{
    if (!containsKey(graph1))
    {
        auto *temp = new Graph(graph1);
        graphs[graph1] = temp;
    }

    if (!containsKey(graph2))
    {
        auto *temp = new Graph(graph2);
        graphs[graph2] = temp;
    }

    graphs[graph1]->addEdge(graphs[graph2], distance);
}

void GraphContainer::print()
{
    std::unordered_map<std::string, Graph *>::iterator it;
    std::cout << "--- --- --- --- ---\n";
    for (it = graphs.begin(); it != graphs.end(); it++)
    {
        std::cout << it->first << " " << it->second << " : " << std::endl;
        it->second->print();
        std::cout << " --- \n";
    }
}

Graph *GraphContainer::getGraph(const std::string& name) {
    return graphs[name];
}
