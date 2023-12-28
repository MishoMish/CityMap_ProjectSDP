//
// Created by Mihail Dobroslavski on 27.12.23.
//

#include "GraphvizController.h"

void GraphvizController::generateDotFile(GraphContainer *graphContainer, Graph *current,
                                         std::unordered_set<Graph *> closed) {
    std::ofstream dotFile("graph.dot");
    if (!dotFile.is_open()) {
        std::cerr << "Error opening DOT file for writing." << std::endl;
        return;
    }

    dotFile << "digraph G {\n";
    dotFile << "  graph [rankdir=LR];\n";
    dotFile << "  node [shape=\"box\", color = \"black\", style=\"filled\"];\n";
    for (const auto &graphPair: graphContainer->getGraphs()) {
        Graph *graph = graphPair.second;
        bool graphtIsClosed = (closed.find(graph) != closed.end());

        dotFile << "  \"" << graph << "\" [label=\"" << graph->getName() << "\", fillcolor=\""
                << (current == graph ? "orange" : (graphtIsClosed ? "red" : "green")) << "\"];\n";

        for (const auto &neighborPair: graph->getAdjacencyList()) {
            Graph *neighbor = neighborPair.first;
            double weight = neighborPair.second;
            bool neighbourIsClosed = (closed.find(neighbor) != closed.end());

            dotFile << "  \"" << graph << "\" -> \"" << neighbor << "\" [label=\"" << weight << "\", color=\""
                    << (graphtIsClosed || neighbourIsClosed ? "red" : "green") << "\"];\n";
        }
    }
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

    dotFile.close();
}

void GraphvizController::runGraphvizAndOpenImage() {
    try {
        std::string graphvizCommand = "dot -Tpng -o graph.png graph.dot";
        int commandResult = std::system(graphvizCommand.c_str());

        if (commandResult == 0) {
            std::string openCommand = "open graph.png 2>/dev/null";
            // >/dev/null because it produces a XPC eror that is not important when opening the image (it works... just produces an error)
            int openResult = std::system(openCommand.c_str());

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