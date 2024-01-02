//
// Created by Mihail Dobroslavski on 30.12.23.
//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "../Interfaces/GraphvizController.h"

TEST_CASE("GraphvizController Test") {
    SUBCASE("Generate Dot File Test") {
        GraphContainer container;

        container.addGraph("1");
        container.addGraph("2");
        container.addGraph("3");
        container.addGraph("4");

        container.addRoad("1", "2", 10.0);
        container.addRoad("1", "3", 20.0);
        container.addRoad("2", "3", 5.0);
        container.addRoad("2", "4", 15.0);

        Graph *currentGraph = container.getGraph("1");
        std::unordered_set<Graph *> closedNodes = {container.getGraph("3")};

        GraphvizController::generateDotFile(&container, currentGraph, closedNodes);

        std::ifstream dotFile("graph.dot");
        REQUIRE(dotFile.is_open());
        dotFile.close();
    }

    SUBCASE("Run Graphviz and Open Image Test") {
        GraphvizController::runGraphvizAndOpenImage();
        std::ifstream imageFile("graph.png");
        REQUIRE(imageFile.is_open());
        imageFile.close();
    }
}

int main(int argc, char *argv[]) {
    doctest::Context context(argc, argv);
    return context.run();
}
