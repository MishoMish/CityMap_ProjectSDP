//
// Created by Mihail Dobroslavski on 27.12.23.
//

#include "GraphvizController.h"

// Function to generate a DOT file for Graphviz visualization
void GraphvizController::generateDotFile(GraphContainer *graphContainer, Graph *current,
                                         std::unordered_set<Graph *> closed) {
    // Open the DOT file for writing
    std::ofstream dotFile("graph.dot");
    if (!dotFile.is_open()) {
        std::cerr << "Error opening DOT file for writing." << std::endl;
        return;
    }

    // Write DOT file header
    dotFile << "digraph G {\n";
    dotFile << "  graph [rankdir=LR];\n";
    dotFile << "  node [shape=\"box\", color = \"black\", style=\"filled\"];\n";

    // Iterate through each graph in the container
    for (const auto &graphPair: graphContainer->getGraphs()) {
        Graph *graph = graphPair.second;
        bool graphtIsClosed = (closed.find(graph) != closed.end());

        // Write DOT node for each graph
        dotFile << "  \"" << graph << "\" [label=\"" << graph->getName() << "\", fillcolor=\""
                << (current == graph ? "orange" : (graphtIsClosed ? "red" : "green")) << "\"];\n";

        // Write DOT edges for each neighbor of the current graph
        for (const auto &neighborPair: graph->getAdjacencyList()) {
            Graph *neighbor = neighborPair.first;
            double weight = neighborPair.second;
            bool neighbourIsClosed = (closed.find(neighbor) != closed.end());

            dotFile << "  \"" << graph << "\" -> \"" << neighbor << "\" [label=\"" << weight << "\", color=\""
                    << (graphtIsClosed || neighbourIsClosed ? "red" : "green") << "\"];\n";
        }
    }

    // Write DOT legend for graph visualization
    dotFile << "  rankdir=LR\n"
               "  node [shape=plaintext]\n"
               "  subgraph cluster_01 { \n"
               "    label = \"Legend\";\n"
               "    key [label=<<table border=\"0\" cellpadding=\"2\" cellspacing=\"0\" cellborder=\"0\">\n"
               "      <tr><td align=\"right\" port=\"i1\">Closed</td></tr>\n"
               "      <tr><td align=\"right\" port=\"i2\">Opened</td></tr>\n"
               "      <tr><td align=\"right\" port=\"i3\">Current</td></tr>\n"
               "      </table>>, color=white]\n"
               "    key2 [label=<<table border=\"0\" cellpadding=\"2\" cellspacing=\"0\" cellborder=\"0\">\n"
               "      <tr><td port=\"i1\">&nbsp;</td></tr>\n"
               "      <tr><td port=\"i2\">&nbsp;</td></tr>\n"
               "      <tr><td port=\"i3\">&nbsp;</td></tr>\n"
               "      </table>>, color=white]\n"
               "    key:i1:e -> key2:i1:w [color=red]\n"
               "    key:i2:e -> key2:i2:w [color=green]\n"
               "    key:i3:e -> key2:i3:w [color=orange]\n"
               "  }\n";
    dotFile << "}\n";

    // Close the DOT file
    dotFile.close();
}

// Function to run Graphviz and open the generated image
void GraphvizController::runGraphvizAndOpenImage() {
    try {
        // Define Graphviz command to generate PNG image from DOT file
        std::string graphvizCommand = "dot -Tpng -o graph.png graph.dot";
        // Execute Graphviz command
        int commandResult = std::system(graphvizCommand.c_str());

        // Check if Graphviz command was successful
        if (commandResult == 0) {
            // Define command to open the generated image
            std::string openCommand = "open graph.png 2>/dev/null";
            // >/dev/null to suppress XPC error (not critical when opening the image)
            int openResult = std::system(openCommand.c_str());

            // Check if image opening command was successful
            if (openResult != 0) {
                std::cerr << "Error opening the generated image." << std::endl;
            }
        } else {
            std::cerr << "Error running Graphviz command." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unexpected error occurred." << std::endl;
    }
}
