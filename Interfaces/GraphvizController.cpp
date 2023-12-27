//
// Created by Mihail Dobroslavski on 27.12.23.
//

#include "GraphvizController.h"

void GraphvizController::generateDotFile(GraphContainer* graphContainer, Graph* current, std::unordered_set<Graph*> closed) {
    std::ofstream dotFile("graph.dot");
    if (!dotFile.is_open()) {
        std::cerr << "Error opening DOT file for writing." << std::endl;
        return;
    }

    // Write your DOT code to dotFile
    dotFile << "digraph G {\n";
    dotFile << "  graph [rankdir=LR];\n";
    dotFile << "  node [shape=\"box\", style=\"filled\"];\n";
    for (const auto& graphPair : graphContainer->graphs) {
        Graph* graph = graphPair.second;
        bool graphtIsClosed = (closed.find(graph) != closed.end());

        dotFile << "  \"" << graph << "\" [label=\"" << graph->name << "\", color=\""<< (current == graph ?  "blue" : (graphtIsClosed ? "red" : "green" )) << "\"];\n";

        for (const auto& neighborPair : graph->adjacencyList) {
            Graph* neighbor = neighborPair.first;
            double weight = neighborPair.second;
            bool neighbourIsClosed = (closed.find(neighbor) != closed.end());

            dotFile << "  \"" << graph << "\" -> \"" << neighbor << "\" [label=\"" << weight << "\", color=\""
                << (graphtIsClosed || neighbourIsClosed ? "red" : "green" ) << "\"];\n";
        }
    }
    dotFile << "}\n";

    dotFile.close();
}

// Function to run Graphviz and open the image
void GraphvizController::runGraphvizAndOpenImage() {
    // Run Graphviz to generate an image
    std::string graphvizCommand = "dot -Tpng -o graph.png graph.dot";
    if (system(graphvizCommand.c_str()) == 0) {
        // Open the generated image (change the command based on your platform)
        std::string openCommand = "open graph.png";  // Assuming macOS here
        system(openCommand.c_str());
    } else {
        std::cerr << "Error running Graphviz command." << std::endl;
    }
}