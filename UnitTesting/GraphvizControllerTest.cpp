//
// Created by Mihail Dobroslavski on 30.12.23.
//

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "../Interfaces/GraphvizController.h"

TEST_CASE("GraphvizController Test") {
    SUBCASE("Generate Dot File Test") {
        GraphContainer container;

        container.addGraph("CityA");
        container.addGraph("CityB");
        container.addGraph("CityC");
        container.addGraph("CityD");

        container.addRoad("CityA", "CityB", 10.0);
        container.addRoad("CityA", "CityC", 20.0);
        container.addRoad("CityB", "CityC", 5.0);
        container.addRoad("CityB", "CityD", 15.0);

        Graph *currentGraph = container.getGraph("CityA");
        std::unordered_set<Graph *> closedNodes = {container.getGraph("CityC")};

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
